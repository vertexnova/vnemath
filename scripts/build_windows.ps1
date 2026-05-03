#==============================================================================
# VneMath Windows Build Script (PowerShell)
#==============================================================================
# Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
# Licensed under the Apache License, Version 2.0 (the "License")
#
# Configure, build, test with CMake (Visual Studio generator when available).
#==============================================================================

param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
    [string]$BuildType = "Debug",
    [ValidateSet("shared", "static")]
    [string]$LibType = "shared",
    [ValidateSet("configure", "build", "configure_and_build", "test")]
    [string]$Action = "configure_and_build",
    [switch]$Clean,
    [int]$Jobs = 10
)

$ErrorActionPreference = "Stop"

$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Split-Path -Parent $ScriptDir

$GeneratorArgs = @()
$vsWhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (Test-Path $vsWhere) {
    $installVer = & $vsWhere -latest -property installationVersion 2>$null
    if ($installVer -match '^(\d+)\.') {
        $major = [int]$Matches[1]
        switch ($major) {
            17 { $GeneratorArgs = @("-G", "Visual Studio 17 2022", "-A", "x64") }
            16 { $GeneratorArgs = @("-G", "Visual Studio 16 2019", "-A", "x64") }
            default { }
        }
    }
}
if ($GeneratorArgs.Count -eq 0) {
    $GeneratorArgs = @("-G", "Ninja", "-DCMAKE_C_COMPILER=cl.exe", "-DCMAKE_CXX_COMPILER=cl.exe")
}

# build/<LibType>/<BuildType>/build-windows-msvc (matches bash script layout)
$BuildDir = Join-Path $ProjectRoot "build\$LibType\$BuildType\build-windows-msvc"
$ConfigureArgs = @(
    "-B", $BuildDir,
    "-S", $ProjectRoot,
    "-DCMAKE_BUILD_TYPE=$BuildType",
    "-DVNE_MATH_LIB_TYPE=$LibType",
    "-DBUILD_TESTS=ON",
    "-DVNE_MATH_TESTS=ON"
) + $GeneratorArgs
$BuildArgs = @("--build", $BuildDir, "--config", $BuildType, "--parallel", "$Jobs")
$TestArgs = @("--test-dir", $BuildDir, "--output-on-failure", "-C", $BuildType)

function Invoke-NativeChecked {
    param(
        [Parameter(Mandatory = $true)][string]$Exe,
        [Parameter(Mandatory = $true)][array]$ArgumentList
    )
    & $Exe @ArgumentList
    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
}

function Clean-Build {
    if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
    New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null
}

function Ensure-BuildDir {
    if (-not (Test-Path $BuildDir)) { New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null }
}

Write-Host "Windows :: MSVC ($BuildType, $LibType)"
Write-Host ""

Set-Location $ProjectRoot
switch ($Action) {
    "configure" {
        if ($Clean) { Clean-Build }; Ensure-BuildDir | Out-Null
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $ConfigureArgs
    }
    "build" {
        if ($Clean) { Clean-Build }; Ensure-BuildDir | Out-Null
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $ConfigureArgs
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $BuildArgs
    }
    "configure_and_build" {
        if ($Clean) { Clean-Build }; Ensure-BuildDir | Out-Null
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $ConfigureArgs
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $BuildArgs
    }
    "test" {
        if ($Clean) { Clean-Build }; Ensure-BuildDir | Out-Null
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $ConfigureArgs
        Invoke-NativeChecked -Exe "cmake" -ArgumentList $BuildArgs
        Invoke-NativeChecked -Exe "ctest" -ArgumentList $TestArgs
    }
    default {
        Write-Host "Usage: .\build_windows.ps1 [-BuildType Debug|Release|...] [-LibType shared|static] [-Action configure|build|configure_and_build|test] [-Clean] [-Jobs N]"
        exit 1
    }
}

Write-Host ""
Write-Host "=== Build completed successfully ==="
Write-Host "Build directory: $BuildDir"
