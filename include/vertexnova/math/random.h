#pragma once
/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   September-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file random.h
 * @brief A wrapper class for C++ standard random library using Mersenne Twister.
 */

// Project includes
#include "vertexnova/common/macros.h"

// Standard library includes
#include <limits>
#include <random>
#include <type_traits>
#include <vector>

namespace vne::math {

template<typename T>
using RandEngine = typename std::conditional<sizeof(T) <= 4, std::mt19937, std::mt19937_64>::type;

template<typename T = float, bool = std::is_integral<std::decay_t<T>>::value>
class Random {};

// Floating point Random
template<typename T>
class Random<T, false> {
   public:
    using DistributorParam = typename std::uniform_real_distribution<T>::param_type;

    Random() noexcept {
        DistributorParam uid(T{0}, T{1});
        uniform_distribution_.param(uid);
    }

    ~Random() noexcept = default;

    explicit Random(uint32_t seed) noexcept {
        random_engine_.seed(seed);
        DistributorParam uid(T{0}, T{1});
        uniform_distribution_.param(uid);
    }

    Random(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    Random(uint32_t seed, T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        random_engine_.seed(seed);
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    Random(const Random<T>& rhs) noexcept { setParam(rhs.getParam()); }

    Random& operator=(const Random<T>& rhs) noexcept {
        if (&rhs == this)
            return *this;
        setParam(rhs.getParam());
        return *this;
    }

    Random(Random<T>&&) = delete;
    Random& operator=(Random<T>&&) = delete;

    [[nodiscard]] T get() noexcept { return uniform_distribution_(random_engine_); }

    [[nodiscard]] std::vector<T> get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = uniform_distribution_(random_engine_);
        }
        return rand_list;
    }

    [[nodiscard]] DistributorParam getParam() const noexcept { return uniform_distribution_.param(); }
    void setParam(const DistributorParam& params) noexcept { uniform_distribution_.param(params); }

    void setMinMax(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    [[nodiscard]] T getMin() const noexcept { return uniform_distribution_.min(); }
    [[nodiscard]] T getMax() const noexcept { return uniform_distribution_.max(); }

   private:
    RandEngine<T> random_engine_{std::random_device()()};
    std::uniform_real_distribution<T> uniform_distribution_;
};

// Integer Random
template<typename T>
class Random<T, true> {
   public:
    using DistributorParam = typename std::uniform_int_distribution<T>::param_type;

    Random() noexcept {
        DistributorParam uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        uniform_distribution_.param(uid);
    }

    ~Random() noexcept = default;

    explicit Random(uint32_t seed) noexcept {
        random_engine_.seed(seed);
        DistributorParam uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        uniform_distribution_.param(uid);
    }

    Random(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    Random(uint32_t seed, T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        random_engine_.seed(seed);
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    Random(const Random<T>& rhs) noexcept { setParam(rhs.getParam()); }

    Random& operator=(const Random<T>& rhs) noexcept {
        if (&rhs == this)
            return *this;
        setParam(rhs.getParam());
        return *this;
    }

    Random(Random<T>&&) = delete;
    Random& operator=(Random<T>&&) = delete;

    [[nodiscard]] T get() noexcept { return uniform_distribution_(random_engine_); }

    [[nodiscard]] std::vector<T> get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = uniform_distribution_(random_engine_);
        }
        return rand_list;
    }

    [[nodiscard]] DistributorParam getParam() const noexcept { return uniform_distribution_.param(); }
    void setParam(const DistributorParam& params) noexcept { uniform_distribution_.param(params); }

    void setMinMax(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    [[nodiscard]] T getMin() const noexcept { return uniform_distribution_.min(); }
    [[nodiscard]] T getMax() const noexcept { return uniform_distribution_.max(); }

   private:
    RandEngine<T> random_engine_{std::random_device()()};
    std::uniform_int_distribution<T> uniform_distribution_;
};

// Legacy type aliases for backward compatibility
template<typename T>
using Random_C = Random<T>;
template<typename T>
using RandEngine_TP = RandEngine<T>;

}  // namespace vne::math

// Legacy namespace aliases
namespace VNE {
namespace Math {
template<typename T>
using Random_C = vne::math::Random<T>;
template<typename T>
using Random = vne::math::Random<T>;
template<typename T>
using RandEngine_TP = vne::math::RandEngine<T>;
}  // namespace Math
}  // namespace VNE
