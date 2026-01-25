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

// Testing framework
#include <gtest/gtest.h>

// Project headers
#include "vertexnova/math/random.h"

// System headers
#include <memory>

// Third-party headers
#include <glm/glm.hpp>

using namespace vne;

class RandomTest : public ::testing::Test {
    // Interface of test fixture base class
   protected:
    void SetUp() override {
        seed_ = 1023;
        lower_f_ = 2.0f;
        upper_f_ = 45.0f;
        lower_i_ = 100;
        upper_i_ = 400;
        size_ = 10;
    }

    void TearDown() override {}

    template<typename T>
    bool IsInBetween(T x, T a, T b) {
        return x >= a && x <= b;
    }

   protected:
    float lower_f_;
    float upper_f_;
    uint32_t seed_;
    size_t size_;
    int lower_i_;
    int upper_i_;
};

/**
 * Test vne::math::Random<T, false>::Get(...)
 */
TEST_F(RandomTest, TestRealRandomGet) {
    auto default_rand = std::make_unique<vne::math::Random<float>>();
    auto rand_withseed_ = std::make_unique<vne::math::Random<float>>(seed_);
    vne::math::Random<float> rand_with_ab(lower_f_, upper_f_);
    vne::math::Random<float> rand_withseed__ab(seed_, lower_f_, upper_f_);
    vne::math::Random<float> rand_copy(rand_withseed__ab);

    // Nondeterministic random numbers
    EXPECT_TRUE(IsInBetween(default_rand->get(), 0.0f, 1.0f));
    EXPECT_TRUE(IsInBetween(rand_with_ab.get(), lower_f_, upper_f_));
    EXPECT_TRUE(IsInBetween(rand_copy.get(), lower_f_, upper_f_));
    // Deterministic random numbers
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 0.0f, 1.0f));
    EXPECT_TRUE(IsInBetween(rand_withseed__ab.get(), lower_f_, upper_f_));

    // Test Operator Overload
    auto rand_double = std::make_unique<vne::math::Random<double>>(seed_, 10.0, 20.0);
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
TEST_F(RandomTest, TestRealRandomExceptions) {
#ifdef _DEBUG
    ASSERT_DEATH(std::make_unique<vne::math::Random<float>>(upper_f_, lower_f_),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
    ASSERT_DEATH(std::make_unique<vne::math::Random<float>>(seed_, upper_f_, lower_f_),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, false>::Get(...)
 */
TEST_F(RandomTest, TestRealRandomGetList) {
    auto rand_withseed_ = std::make_unique<vne::math::Random<float>>(seed_);
    // Deterministic random numbers
    std::vector<float> random_numbers = rand_withseed_->get(size_);
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
TEST_F(RandomTest, TestRealRandomGetAndSetParam) {
    auto default_rand = std::make_unique<vne::math::Random<float>>();
    auto rand_withseed_ = std::make_unique<vne::math::Random<float>>(seed_);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 0.0f, 1.0f));
    rand_withseed_->setParam(default_rand->getParam());
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 0.0f, 1.0f));
}

/**
 * Test vne::math::Random<T, false>::GetMin(...),
 * vne::math::Random<T, false>::GetMax(...), and
 * vne::math::Random_c<T, false>::SetParam(...)
 */
TEST_F(RandomTest, TestRealRandomGetAndSetMinMax) {
    auto rand_withseed_ = std::make_unique<vne::math::Random<float>>(seed_);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 0.0f, 1.0f));
    EXPECT_EQ(0.0f, rand_withseed_->getMin());
    EXPECT_EQ(1.0f, rand_withseed_->getMax());
    rand_withseed_->setMinMax(10.0f, 20.0f);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 10.0f, 20.0f));
    EXPECT_EQ(10.0f, rand_withseed_->getMin());
    EXPECT_EQ(20.0f, rand_withseed_->getMax());
    rand_withseed_->setMinMax(30.0f, 30.0f);
    EXPECT_EQ(30.0f, rand_withseed_->get());
    EXPECT_EQ(30.0f, rand_withseed_->getMin());
    EXPECT_EQ(30.0f, rand_withseed_->getMax());
#ifdef _DEBUG
    ASSERT_DEATH(rand_withseed_->setMinMax(50.0f, 40.0f),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, true>::Get(...)
 */
TEST_F(RandomTest, TestIntegerRandomGet) {
    auto default_rand = std::make_unique<vne::math::Random<int>>();
    auto rand_withseed_ = std::make_unique<vne::math::Random<int>>(seed_);
    auto rand_with_ab = std::make_unique<vne::math::Random<int>>(lower_i_, upper_i_);
    auto rand_withseed__ab = std::make_unique<vne::math::Random<int>>(seed_, lower_i_, upper_i_);

    vne::math::Random<int> rand_copy(*rand_withseed__ab);

    // Nondeterministic random numbers
    EXPECT_TRUE(IsInBetween(default_rand->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    EXPECT_TRUE(IsInBetween(rand_with_ab->get(), lower_i_, upper_i_));
    EXPECT_TRUE(IsInBetween(rand_copy.get(), lower_i_, upper_i_));
    // Deterministic random numbers
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    EXPECT_TRUE(IsInBetween(rand_withseed__ab->get(), lower_i_, upper_i_));

    // Test Operator Overload
    auto rand_uint = std::make_unique<vne::math::Random<unsigned int>>(seed_, 10, 20);
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
TEST_F(RandomTest, TestIntegerRandomGetList) {
    auto rand_withseed_ = std::make_unique<vne::math::Random<int>>(seed_, lower_i_, upper_i_);
    // Deterministic random numbers
    std::vector<int> random_numbers = rand_withseed_->get(size_);
    for (auto number : random_numbers) {
#ifdef _DEBUG
        std::cout << number << std::endl;
#endif  // _DEBUG
        EXPECT_TRUE(IsInBetween(number, lower_i_, upper_i_));
    }
}

/**
 * Test Integer Random Exceptions
 */
TEST_F(RandomTest, TestIntegerRandomExceptions) {
#ifdef _DEBUG
    ASSERT_DEATH(std::make_unique<vne::math::Random<int>>(upper_i_, lower_i_),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
    ASSERT_DEATH(std::make_unique<vne::math::Random<int>>(seed_, upper_i_, lower_i_),
                 ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}

/**
 * Test vne::math::Random<T, true>::GetParam(...) and
 * vne::math::Random_c<T, true>::SetParam(...)
 */
TEST_F(RandomTest, TestIntegerRandomGetAndSetParam) {
    auto default_rand = std::make_unique<vne::math::Random<int>>();
    auto rand_withseed_ = std::make_unique<vne::math::Random<int>>(seed_, lower_i_, upper_i_);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), lower_i_, upper_i_));
    rand_withseed_->setParam(default_rand->getParam());
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}

/**
 * Test vne::math::Random<T, true>::GetMin(...),
 * vne::math::Random<T, true>::GetMax(...), and
 * vne::math::Random_c<T, true>::SetParam(...)
 */
TEST_F(RandomTest, TestIntegerRandomGetAndSetMinMax) {
    auto rand_withseed_ = std::make_unique<vne::math::Random<int>>(seed_, lower_i_, upper_i_);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), lower_i_, upper_i_));
    EXPECT_EQ(lower_i_, rand_withseed_->getMin());
    EXPECT_EQ(upper_i_, rand_withseed_->getMax());
    rand_withseed_->setMinMax(10, 20);
    EXPECT_TRUE(IsInBetween(rand_withseed_->get(), 10, 20));
    EXPECT_EQ(10, rand_withseed_->getMin());
    EXPECT_EQ(20, rand_withseed_->getMax());
    rand_withseed_->setMinMax(30, 30);
    EXPECT_EQ(30, rand_withseed_->get());
    EXPECT_EQ(30, rand_withseed_->getMin());
    EXPECT_EQ(30, rand_withseed_->getMax());
#ifdef _DEBUG
    ASSERT_DEATH(rand_withseed_->setMinMax(50, 40), ".* Assertion Failed: a <= b :: invalid min and max arguments.*");
#endif  // _DEBUG
}
