/* ---------------------------------------------------------------------
 * Copyright (c) 2026 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Running statistics calculator for data analysis.
 * ----------------------------------------------------------------------
 */

#pragma once

#include "core/types.h"

#include <cmath>
#include <limits>
#include <vector>

namespace vne::math {

/**
 * @class Statistic
 * @brief Calculates running statistics for a sequence of values.
 *
 * Computes statistics incrementally without storing all values:
 * - Count, Sum
 * - Min, Max
 * - Mean, Variance, Standard Deviation
 * - Root Mean Square (RMS)
 *
 * Common uses:
 * - Performance profiling (frame times, latency)
 * - Data analysis
 * - Signal processing
 * - Physics simulations
 *
 * @tparam T Floating-point type (float or double)
 */
template<FloatingPoint T = float>
class Statistic {
   public:
    // ========================================================================
    // Constructors
    // ========================================================================

    /**
     * @brief Default constructor. Initializes empty statistics.
     */
    constexpr Statistic() noexcept { reset(); }

    /**
     * @brief Constructs with initial values.
     */
    explicit Statistic(const std::vector<T>& values) noexcept {
        reset();
        for (const T& v : values) {
            addValue(v);
        }
    }

    // ========================================================================
    // Data Input
    // ========================================================================

    /**
     * @brief Resets all statistics to initial state.
     */
    constexpr void reset() noexcept {
        m_count = 0;
        m_sum = T(0);
        m_sum_square = T(0);
        m_min = std::numeric_limits<T>::max();
        m_max = std::numeric_limits<T>::lowest();
    }

    /**
     * @brief Adds a single value to the statistics.
     */
    constexpr void addValue(T value) noexcept {
        ++m_count;
        m_sum += value;
        m_sum_square += value * value;
        m_min = vne::math::min(m_min, value);
        m_max = vne::math::max(m_max, value);
    }

    /**
     * @brief Adds multiple values.
     */
    void addValues(const std::vector<T>& values) noexcept {
        for (const T& v : values) {
            addValue(v);
        }
    }

    /**
     * @brief Adds values from an initializer list.
     */
    void addValues(std::initializer_list<T> values) noexcept {
        for (const T& v : values) {
            addValue(v);
        }
    }

    // ========================================================================
    // Basic Statistics
    // ========================================================================

    /**
     * @brief Returns the number of values added.
     */
    [[nodiscard]] constexpr uint32_t count() const noexcept { return m_count; }

    /**
     * @brief Returns the sum of all values.
     */
    [[nodiscard]] constexpr T sum() const noexcept { return m_sum; }

    /**
     * @brief Returns the sum of squares of all values.
     */
    [[nodiscard]] constexpr T sumSquare() const noexcept { return m_sum_square; }

    /**
     * @brief Returns the minimum value, or max float if empty.
     */
    [[nodiscard]] constexpr T min() const noexcept { return m_min; }

    /**
     * @brief Returns the maximum value, or min float if empty.
     */
    [[nodiscard]] constexpr T max() const noexcept { return m_max; }

    /**
     * @brief Returns the range (max - min).
     */
    [[nodiscard]] constexpr T range() const noexcept { return m_count > 0 ? m_max - m_min : T(0); }

    // ========================================================================
    // Computed Statistics
    // ========================================================================

    /**
     * @brief Computes the arithmetic mean.
     *
     * @return Mean value, or 0 if empty
     */
    [[nodiscard]] constexpr T mean() const noexcept { return m_count > 0 ? m_sum / static_cast<T>(m_count) : T(0); }

    /**
     * @brief Computes the population variance.
     *
     * Uses the formula: Var = E[X²] - E[X]²
     *
     * @return Variance, or 0 if empty
     */
    [[nodiscard]] T variance() const noexcept {
        if (m_count == 0) {
            return T(0);
        }
        T n = static_cast<T>(m_count);
        T mean_sq = (m_sum / n) * (m_sum / n);
        T variance_val = m_sum_square / n - mean_sq;
        return vne::math::max(variance_val, T(0));  // Avoid negative due to floating-point errors
    }

    /**
     * @brief Computes the sample variance (unbiased estimator).
     *
     * Uses Bessel's correction: divide by (n-1) instead of n.
     *
     * @return Sample variance, or 0 if count < 2
     */
    [[nodiscard]] T sampleVariance() const noexcept {
        if (m_count < 2) {
            return T(0);
        }
        T n = static_cast<T>(m_count);
        T mean_val = m_sum / n;
        T sum_sq_diff = m_sum_square - n * mean_val * mean_val;
        return vne::math::max(sum_sq_diff / (n - T(1)), T(0));
    }

    /**
     * @brief Computes the population standard deviation.
     *
     * @return Standard deviation, or 0 if empty
     */
    [[nodiscard]] T stdDev() const noexcept { return std::sqrt(variance()); }

    /**
     * @brief Computes the sample standard deviation.
     *
     * @return Sample standard deviation, or 0 if count < 2
     */
    [[nodiscard]] T sampleStdDev() const noexcept { return std::sqrt(sampleVariance()); }

    /**
     * @brief Computes the root mean square (RMS).
     *
     * RMS = sqrt(mean(x²))
     *
     * @return RMS value, or 0 if empty
     */
    [[nodiscard]] T rms() const noexcept {
        if (m_count == 0) {
            return T(0);
        }
        return std::sqrt(m_sum_square / static_cast<T>(m_count));
    }

    /**
     * @brief Computes the coefficient of variation (CV).
     *
     * CV = stdDev / mean (relative variability)
     *
     * @return CV, or 0 if mean is zero
     */
    [[nodiscard]] T coefficientOfVariation() const noexcept {
        T m = mean();
        return isZero(m) ? T(0) : stdDev() / std::abs(m);
    }

    // ========================================================================
    // Queries
    // ========================================================================

    /**
     * @brief Checks if any values have been added.
     */
    [[nodiscard]] constexpr bool isEmpty() const noexcept { return m_count == 0; }

    /**
     * @brief Checks if the values have any variation.
     */
    [[nodiscard]] bool hasVariation(T epsilon = kEpsilon<T>) const noexcept { return range() > epsilon; }

    // ========================================================================
    // Merge Statistics
    // ========================================================================

    /**
     * @brief Merges another Statistic into this one.
     *
     * Combines statistics from two independent samples.
     */
    constexpr void merge(const Statistic& other) noexcept {
        if (other.m_count == 0) {
            return;
        }
        m_count += other.m_count;
        m_sum += other.m_sum;
        m_sum_square += other.m_sum_square;
        m_min = vne::math::min(m_min, other.m_min);
        m_max = vne::math::max(m_max, other.m_max);
    }

   private:
    uint32_t m_count = 0;                        ///< Number of values
    T m_sum = T(0);                              ///< Sum of values
    T m_sum_square = T(0);                       ///< Sum of squares
    T m_min = std::numeric_limits<T>::max();     ///< Minimum value
    T m_max = std::numeric_limits<T>::lowest();  ///< Maximum value
};

// Type aliases
using Statisticf = Statistic<float>;
using Statisticd = Statistic<double>;

}  // namespace vne::math
