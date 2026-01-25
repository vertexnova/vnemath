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

#include <gtest/gtest.h>
#include "vertexnova/math/random.h"
#include <glm/glm.hpp>
#include <memory>  // for std::unique_ptr

using namespace VNE;

class RandomTest_C : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        _seed = 1023;
        _lower_f = 2.0f;
        _upper_f = 45.0f;
        _lower_i = 100;
        _upper_i = 400;
        _size = 10;
    }

    void TearDown() override {}

    template<typename T>
    bool IsInBetween(T x, T a, T b) {
        return x >= a && x <= b;
    }

   protected:
    float _lower_f;
    float _upper_f;
    uint32_t _seed;
    size_t _size;
    int _lower_i;
    int _upper_i;
};

/**
 * Test vne::math::Random<T, false>::Get(...)
 */
TEST_F(RandomTest_C, TestRealRandomGet) {
    auto default_rand = std::make_unique<vne::math::Random<float>>();
    auto rand_with_seed = std::make_unique<vne::math::Random<float>>(_seed);
    vne::math::Random<float> rand_with_ab(_lower_f, _upper_f);
    vne::math::Random<float> rand_with_seed_ab(_seed, _lower_f, _upper_f);
    vne::math::Random<float> rand_copy(rand_with_seed_ab);

    // Nondeterministic random numbers
    EXPECT_TRUE(IsInBetween(default_rand->get(), 0.0f, 1.0f));
    EXPECT_TRUE(IsInBetween(rand_with_ab.get(), _lower_f, _upper_f));
    EXPECT_TRUE(IsInBetween(rand_copy.get(), _lower_f, _upper_f));
    // Deterministic random numbers
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 0.0f, 1.0f));
    EXPECT_TRUE(IsInBetween(rand_with_seed_ab.get(), _lower_f, _upper_f));

    // Test Operator Overload
    auto rand_double = std::make_unique<vne::math::Random<double>>(_seed, 10.0, 20.0);
    EXPECT_TRUE(IsInBetween(rand_double->get(), 10.0, 20.0));
    EXPECT_DOUBLE_EQ(10.0, rand_double->getMin());
    EXPECT_DOUBLE_EQ(20.0, rand_double->getMax());

    auto rand_double_default = std::make_unique<vne::math::Random<double>>();
    EXPECT_DOUBLE_EQ(0.0, rand_double_default->getMin());
    EXPECT_DOUBLE_EQ(1.0, rand_double_default->getMax());

    rand_double_default = std::move(rand_double);
    EXPECT_DOUBLE_EQ(10.0, rand_double_default->getMin());
    EXPECT_DOUBLE_EQ(20.0, rand_double_default->getMax());
}

/**
 * Test floating point Random Exceptions
 */
TEST_F(RandomTest_C, TestRealRandomExceptions) {
#ifdef _DEBUG
    ASSERT_DEATH(std::make_unique<vne::math::Random<float>>(_upper_f, _lower_f), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
    ASSERT_DEATH(std::make_unique<vne::math::Random<float>>(_seed, _upper_f, _lower_f),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, false>::Get(...)
 */
TEST_F(RandomTest_C, TestRealRandomGetList) {
    auto rand_with_seed = std::make_unique<vne::math::Random<float>>(_seed);
    // Deterministic random numbers
    std::vector<float> random_numbers = rand_with_seed->get(_size);
    for (auto number : random_numbers) {
#ifdef _DEBUG
        std::cout << number << std::endl;
#endif  // _DEBUG
        EXPECT_TRUE(IsInBetween(number, 0.0f, 1.0f));
    }
}

/**
 * Test vne::math::Random<T, false>::GetParam(...) and
 * vne::math::Random_c<T, false>::SetParam(...)
 */
TEST_F(RandomTest_C, TestRealRandomGetAndSetParam) {
    auto default_rand = std::make_unique<vne::math::Random<float>>();
    auto rand_with_seed = std::make_unique<vne::math::Random<float>>(_seed);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 0.0f, 1.0f));
    rand_with_seed->setParam(default_rand->getParam());
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 0.0f, 1.0f));
}

/**
 * Test vne::math::Random<T, false>::GetMin(...),
 * vne::math::Random<T, false>::GetMax(...), and
 * vne::math::Random_c<T, false>::SetParam(...)
 */
TEST_F(RandomTest_C, TestRealRandomGetAndSetMinMax) {
    auto rand_with_seed = std::make_unique<vne::math::Random<float>>(_seed);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 0.0f, 1.0f));
    EXPECT_EQ(0.0f, rand_with_seed->getMin());
    EXPECT_EQ(1.0f, rand_with_seed->getMax());
    rand_with_seed->setMinMax(10.0f, 20.0f);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 10.0f, 20.0f));
    EXPECT_EQ(10.0f, rand_with_seed->getMin());
    EXPECT_EQ(20.0f, rand_with_seed->getMax());
    rand_with_seed->setMinMax(30.0f, 30.0f);
    EXPECT_EQ(30.0f, rand_with_seed->get());
    EXPECT_EQ(30.0f, rand_with_seed->getMin());
    EXPECT_EQ(30.0f, rand_with_seed->getMax());
#ifdef _DEBUG
    ASSERT_DEATH(rand_with_seed->setMinMax(50.0f, 40.0f), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, true>::Get(...)
 */
TEST_F(RandomTest_C, TestIntegerRandomGet) {
    auto default_rand = std::make_unique<vne::math::Random<int>>();
    auto rand_with_seed = std::make_unique<vne::math::Random<int>>(_seed);
    auto rand_with_ab = std::make_unique<vne::math::Random<int>>(_lower_i, _upper_i);
    auto rand_with_seed_ab = std::make_unique<vne::math::Random<int>>(_seed, _lower_i, _upper_i);

    vne::math::Random<int> rand_copy(*rand_with_seed_ab);

    // Nondeterministic random numbers
    EXPECT_TRUE(IsInBetween(default_rand->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    EXPECT_TRUE(IsInBetween(rand_with_ab->get(), _lower_i, _upper_i));
    EXPECT_TRUE(IsInBetween(rand_copy.get(), _lower_i, _upper_i));
    // Deterministic random numbers
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    EXPECT_TRUE(IsInBetween(rand_with_seed_ab->get(), _lower_i, _upper_i));

    // Test Operator Overload
    auto rand_uint = std::make_unique<vne::math::Random<unsigned int>>(_seed, 10, 20);
    EXPECT_TRUE(IsInBetween(rand_uint->get(), 10u, 20u));
    EXPECT_EQ(10u, rand_uint->getMin());
    EXPECT_EQ(20u, rand_uint->getMax());

    auto rand_uint_default = std::make_unique<vne::math::Random<unsigned int>>();
    EXPECT_EQ(std::numeric_limits<unsigned int>::min(), rand_uint_default->getMin());
    EXPECT_EQ(std::numeric_limits<unsigned int>::max(), rand_uint_default->getMax());

    rand_uint_default = std::move(rand_uint);
    EXPECT_EQ(10u, rand_uint_default->getMin());
    EXPECT_EQ(20u, rand_uint_default->getMax());
}

/**
 * Test vne::math::Random<T, true>::Get(...)
 */
TEST_F(RandomTest_C, TestIntegerRandomGetList) {
    auto rand_with_seed = std::make_unique<vne::math::Random<int>>(_seed, _lower_i, _upper_i);
    // Deterministic random numbers
    std::vector<int> random_numbers = rand_with_seed->get(_size);
    for (auto number : random_numbers) {
#ifdef _DEBUG
        std::cout << number << std::endl;
#endif  // _DEBUG
        EXPECT_TRUE(IsInBetween(number, _lower_i, _upper_i));
    }
}

/**
 * Test Integer Random Exceptions
 */
TEST_F(RandomTest_C, TestIntegerRandomExceptions) {
#ifdef _DEBUG
    ASSERT_DEATH(std::make_unique<vne::math::Random<int>>(_upper_i, _lower_i), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
    ASSERT_DEATH(std::make_unique<vne::math::Random<int>>(_seed, _upper_i, _lower_i), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, true>::GetParam(...) and
 * vne::math::Random_c<T, true>::SetParam(...)
 */
TEST_F(RandomTest_C, TestIntegerRandomGetAndSetParam) {
    auto default_rand = std::make_unique<vne::math::Random<int>>();
    auto rand_with_seed = std::make_unique<vne::math::Random<int>>(_seed, _lower_i, _upper_i);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), _lower_i, _upper_i));
    rand_with_seed->setParam(default_rand->getParam());
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}

/**
 * Test vne::math::Random<T, true>::GetMin(...),
 * vne::math::Random<T, true>::GetMax(...), and
 * vne::math::Random_c<T, true>::SetParam(...)
 */
TEST_F(RandomTest_C, TestIntegerRandomGetAndSetMinMax) {
    auto rand_with_seed = std::make_unique<vne::math::Random<int>>(_seed, _lower_i, _upper_i);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), _lower_i, _upper_i));
    EXPECT_EQ(_lower_i, rand_with_seed->getMin());
    EXPECT_EQ(_upper_i, rand_with_seed->getMax());
    rand_with_seed->setMinMax(10, 20);
    EXPECT_TRUE(IsInBetween(rand_with_seed->get(), 10, 20));
    EXPECT_EQ(10, rand_with_seed->getMin());
    EXPECT_EQ(20, rand_with_seed->getMax());
    rand_with_seed->setMinMax(30, 30);
    EXPECT_EQ(30, rand_with_seed->get());
    EXPECT_EQ(30, rand_with_seed->getMin());
    EXPECT_EQ(30, rand_with_seed->getMax());
#ifdef _DEBUG
    ASSERT_DEATH(rand_with_seed->setMinMax(50, 40), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}
