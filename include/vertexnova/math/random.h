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
 * @brief Defines the Random class template for random number generation.
 */

// Project includes
#include "vertexnova/common/macros.h"

// Standard library includes
#include <limits>
#include <random>
#include <type_traits>
#include <vector>

namespace vne::math {

/**
 * @brief Type alias for Mersenne Twister engine based on type size
 *
 * Uses std::mt19937 for types <= 4 bytes, std::mt19937_64 for larger types.
 */
template<typename T>
using RandEngine = typename std::conditional<sizeof(T) <= 4, std::mt19937, std::mt19937_64>::type;

/**
 * @class Random
 * @brief A wrapper class for C++ standard random library using Mersenne Twister.
 *
 * This template class provides uniform random number generation for both
 * floating-point and integer types. The specialization is automatically
 * selected based on the template parameter type.
 *
 * @tparam T The numeric type to generate (float, double, int, etc.)
 *
 * @example
 * @code
 * Random<float> rand_float;                 // Random floats in [0, 1]
 * Random<float> rand_range(0.0f, 100.0f);   // Random floats in [0, 100]
 * Random<int> rand_int(1, 6);               // Random integers in [1, 6]
 *
 * float value = rand_float.get();
 * std::vector<int> dice_rolls = rand_int.get(10);
 * @endcode
 */
template<typename T = float, bool = std::is_integral<std::decay_t<T>>::value>
class Random {};

/**
 * @brief Floating-point specialization of Random
 *
 * Generates uniformly distributed floating-point numbers using
 * std::uniform_real_distribution.
 */
template<typename T>
class Random<T, false> {
   public:
    /// Type alias for the distribution parameter
    using DistributorParam = typename std::uniform_real_distribution<T>::param_type;

    /**
     * @brief Default constructor
     *
     * Initializes with range [0, 1] and random seed.
     */
    Random() noexcept {
        DistributorParam uid(T{0}, T{1});
        uniform_distribution_.param(uid);
    }

    /** @brief Default destructor */
    ~Random() noexcept = default;

    /**
     * @brief Constructor with specific seed
     * @param seed The seed value for reproducible sequences
     *
     * Initializes with range [0, 1] and specified seed.
     */
    explicit Random(uint32_t seed) noexcept {
        random_engine_.seed(seed);
        DistributorParam uid(T{0}, T{1});
        uniform_distribution_.param(uid);
    }

    /**
     * @brief Constructor with range
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    Random(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /**
     * @brief Constructor with seed and range
     * @param seed The seed value for reproducible sequences
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    Random(uint32_t seed, T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        random_engine_.seed(seed);
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /** @brief Copy constructor */
    Random(const Random<T>& rhs) noexcept { setParam(rhs.getParam()); }

    /** @brief Copy assignment operator */
    Random& operator=(const Random<T>& rhs) noexcept {
        if (&rhs == this)
            return *this;
        setParam(rhs.getParam());
        return *this;
    }

    Random(Random<T>&&) = delete;
    Random& operator=(Random<T>&&) = delete;

    /**
     * @brief Generates a single random value
     * @return A random value in the configured range
     */
    [[nodiscard]] T get() noexcept { return uniform_distribution_(random_engine_); }

    /**
     * @brief Generates multiple random values
     * @param n The number of values to generate
     * @return A vector of random values
     */
    [[nodiscard]] std::vector<T> get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = uniform_distribution_(random_engine_);
        }
        return rand_list;
    }

    /**
     * @brief Gets the distribution parameters
     * @return The current distribution parameters
     */
    [[nodiscard]] DistributorParam getParam() const noexcept { return uniform_distribution_.param(); }

    /**
     * @brief Sets the distribution parameters
     * @param params The new distribution parameters
     */
    void setParam(const DistributorParam& params) noexcept { uniform_distribution_.param(params); }

    /**
     * @brief Sets the range for random generation
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    void setMinMax(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /** @brief Gets the minimum value of the range */
    [[nodiscard]] T getMin() const noexcept { return uniform_distribution_.min(); }

    /** @brief Gets the maximum value of the range */
    [[nodiscard]] T getMax() const noexcept { return uniform_distribution_.max(); }

   private:
    RandEngine<T> random_engine_{std::random_device()()};
    std::uniform_real_distribution<T> uniform_distribution_;
};

/**
 * @brief Integer specialization of Random
 *
 * Generates uniformly distributed integer numbers using
 * std::uniform_int_distribution.
 */
template<typename T>
class Random<T, true> {
   public:
    /// Type alias for the distribution parameter
    using DistributorParam = typename std::uniform_int_distribution<T>::param_type;

    /**
     * @brief Default constructor
     *
     * Initializes with full range of type T.
     */
    Random() noexcept {
        DistributorParam uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        uniform_distribution_.param(uid);
    }

    /** @brief Default destructor */
    ~Random() noexcept = default;

    /**
     * @brief Constructor with specific seed
     * @param seed The seed value for reproducible sequences
     */
    explicit Random(uint32_t seed) noexcept {
        random_engine_.seed(seed);
        DistributorParam uid(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        uniform_distribution_.param(uid);
    }

    /**
     * @brief Constructor with range
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    Random(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /**
     * @brief Constructor with seed and range
     * @param seed The seed value for reproducible sequences
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    Random(uint32_t seed, T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        random_engine_.seed(seed);
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /** @brief Copy constructor */
    Random(const Random<T>& rhs) noexcept { setParam(rhs.getParam()); }

    /** @brief Copy assignment operator */
    Random& operator=(const Random<T>& rhs) noexcept {
        if (&rhs == this)
            return *this;
        setParam(rhs.getParam());
        return *this;
    }

    Random(Random<T>&&) = delete;
    Random& operator=(Random<T>&&) = delete;

    /**
     * @brief Generates a single random value
     * @return A random value in the configured range
     */
    [[nodiscard]] T get() noexcept { return uniform_distribution_(random_engine_); }

    /**
     * @brief Generates multiple random values
     * @param n The number of values to generate
     * @return A vector of random values
     */
    [[nodiscard]] std::vector<T> get(size_t n) {
        std::vector<T> rand_list(n, T{0});
        for (size_t i = 0; i < n; ++i) {
            rand_list[i] = uniform_distribution_(random_engine_);
        }
        return rand_list;
    }

    /**
     * @brief Gets the distribution parameters
     * @return The current distribution parameters
     */
    [[nodiscard]] DistributorParam getParam() const noexcept { return uniform_distribution_.param(); }

    /**
     * @brief Sets the distribution parameters
     * @param params The new distribution parameters
     */
    void setParam(const DistributorParam& params) noexcept { uniform_distribution_.param(params); }

    /**
     * @brief Sets the range for random generation
     * @param a Minimum value (inclusive)
     * @param b Maximum value (inclusive)
     */
    void setMinMax(T a, T b) noexcept {
        VNE_ASSERT_MSG(a <= b, "invalid min and max arguments");
        DistributorParam uid(a, b);
        uniform_distribution_.param(uid);
    }

    /** @brief Gets the minimum value of the range */
    [[nodiscard]] T getMin() const noexcept { return uniform_distribution_.min(); }

    /** @brief Gets the maximum value of the range */
    [[nodiscard]] T getMax() const noexcept { return uniform_distribution_.max(); }

   private:
    RandEngine<T> random_engine_{std::random_device()()};
    std::uniform_int_distribution<T> uniform_distribution_;
};

}  // namespace vne::math
