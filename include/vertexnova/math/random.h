#ifndef VNE_MATH_RANDOM_H
#define VNE_MATH_RANDOM_H
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

namespace VNE {
namespace Math {

template<typename T>
using RandEngine_TP = typename std::conditional<sizeof(T) <= 4, std::mt19937, std::mt19937_64>::type;

template<typename T = float, bool = std::is_integral<std::decay_t<T>>::value>
class Random_C {};

// Floating point Random_C
template<typename T>
class Random_C<T, false> {
   public:
    using Distributor_TP = typename std::uniform_real_distribution<T>::param_type;

    Random_C() {
        Distributor_TP uid(T{0}, T{1});
        _uniform_distribution.param(uid);
    }

    ~Random_C() = default;

    Random_C(uint32_t seed) {
        _random_engine.seed(seed);
        Distributor_TP uid(T{0}, T{1});
        _uniform_distribution.param(uid);
    }

    Random_C(T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    Random_C(uint32_t seed, T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        _random_engine.seed(seed);
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    Random_C(const Random_C<T>& rhs) { SetParam(rhs.GetParam()); }

    Random_C& operator=(const Random_C<T>& rhs) {
        if (&rhs == this) return *this;
        SetParam(rhs.GetParam());
        return *this;
    }

    Random_C(Random_C<T>&&) = delete;
    Random_C& operator=(Random_C<T>&&) = delete;

    T Get() { return _uniform_distribution(_random_engine); }

    std::vector<T> Get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = _uniform_distribution(_random_engine);
        }
        return rand_list;
    }

    Distributor_TP GetParam() const { return _uniform_distribution.param(); }
    void SetParam(const Distributor_TP& params) { _uniform_distribution.param(params); }

    void SetMinMax(T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    T GetMin(void) { return _uniform_distribution.min(); }
    T GetMax(void) { return _uniform_distribution.max(); }

   private:
    RandEngine_TP<T> _random_engine{std::random_device()()};
    std::uniform_real_distribution<T> _uniform_distribution;
};

// Integer Random_C
template<typename T>
class Random_C<T, true> {
   public:
    using Distributor_TP = typename std::uniform_int_distribution<T>::param_type;

    Random_C() {
        Distributor_TP uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        _uniform_distribution.param(uid);
    }

    ~Random_C() = default;

    Random_C(uint32_t seed) {
        _random_engine.seed(seed);
        Distributor_TP uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        _uniform_distribution.param(uid);
    }

    Random_C(T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    Random_C(uint32_t seed, T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        _random_engine.seed(seed);
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    Random_C(const Random_C<T>& rhs) { SetParam(rhs.GetParam()); }

    Random_C& operator=(const Random_C<T>& rhs) {
        if (&rhs == this) return *this;
        SetParam(rhs.GetParam());
        return *this;
    }

    Random_C(Random_C<T>&&) = delete;
    Random_C& operator=(Random_C<T>&&) = delete;

    T Get() { return _uniform_distribution(_random_engine); }

    std::vector<T> Get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = _uniform_distribution(_random_engine);
        }
        return rand_list;
    }

    Distributor_TP GetParam() const { return _uniform_distribution.param(); }
    void SetParam(const Distributor_TP& params) { _uniform_distribution.param(params); }

    void SetMinMax(T a, T b) {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        Distributor_TP uid(a, b);
        _uniform_distribution.param(uid);
    }

    T GetMin(void) { return _uniform_distribution.min(); }
    T GetMax(void) { return _uniform_distribution.max(); }

   private:
    RandEngine_TP<T> _random_engine{std::random_device()()};
    std::uniform_int_distribution<T> _uniform_distribution;
};

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_RANDOM_H
