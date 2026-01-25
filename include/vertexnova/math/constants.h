#ifndef VNE_MATH_CONSTANTS_H
#define VNE_MATH_CONSTANTS_H

/* ---------------------------------------------------------------------
 * Copyright (c) 2024 Ajeet Singh Yadav. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License")
 *
 * Author:    Ajeet Singh Yadav
 * Created:   August-2024
 *
 * Autodoc:   yes
 * ----------------------------------------------------------------------
 */

/**
 * @file constants.h
 *
 * @brief Contains numeric math constants and limits.
 *
 * @author Ajeet Singh Yadav
 * Contact: yadav.ajeetsingh2020@gmail.com
 *
 */

// System library includes
#include <limits>  // For numeric_limits

////////////////////////////////////////////////////////////////////////////
//                                 Macros                                 //
// /////////////////////////////////////////////////////////////////////////

//! The circumference of a circle with diameter 1, pi.
#ifndef PI
#define PI 3.1415926535897932385E0  //!< pi
#endif

#ifndef TWO_PI
#define TWO_PI 6.28318530717958647693E0  //!< 2 * pi
#endif

#ifndef HALF_PI
#define HALF_PI 1.5707963267948966192E0  //!< pi/2
#endif

#ifndef QUARTER_PI
#define QUARTER_PI 7.8539816339744830962E-1  //!< pi/4
#endif

#ifndef ONE_OVER_PI
#define ONE_OVER_PI 3.1830988618379067154E-1  //!< 1/pi
#endif

#ifndef ONE_OVER_TWO_PI
#define ONE_OVER_TWO_PI 1.5915494309189535E-1  //!< 1/(2*pi)
#endif

#ifndef TWO_OVER_PI
#define TWO_OVER_PI 6.3661977236758134308E-1  //!< 2/pi
#endif

#ifndef SQRT_PI
#define SQRT_PI 1.7724538509055161E0  //!< sqrt(pi)
#endif

#ifndef TWO_OVER_SQRT_PI
#define TWO_OVER_SQRT_PI 1.1283791670955125739E0  //!< 2/sqrt(pi)
#endif

//! The base of natural logarithms, e.
#ifndef E
#define E 2.7182818284590452354E0  //!< e
#endif

//! The base 2 logarithm of e.
#ifndef LOG2E
#define LOG2E 1.4426950408889634074E0  //!< log2(e)
#endif

//! The base 10 logarithm of e.
#ifndef LOG10E
#define LOG10E 4.3429448190325182765E-1  //!< log10(e)
#endif

//! The natural logarithm of 2.
#ifndef LN2
#define LN2 6.9314718055994530942E-1  //!< ln(2)
#endif

//! The natural logarithm of 10.
#ifndef LN10
#define LN10 2.3025850929940456840E0  //!< ln(10)
#endif

#ifndef SQRT_TWO
#define SQRT_TWO 1.4142135623730950488E0  //!< sqrt(2)
#endif

#ifndef SQRT_THREE
#define SQRT_THREE 1.73205080756887729352E0  //!< sqrt(3)
#endif

#ifndef SQRT_ONE_OVER_TWO
#define SQRT_ONE_OVER_TWO 7.0710678118654752440E-1  //!< 1/sqrt(2)
#endif

#ifndef SQRT_ONE_OVER_THREE
#define SQRT_ONE_OVER_THREE 5.7735026918962576450E-1  //!< 1/sqrt(3)
#endif

namespace VNE {
namespace Math {

////////////////////////////////////////////////////////////////////////////
//                              Constants                                 //
// /////////////////////////////////////////////////////////////////////////

//! A huge number that should be larger than any valid number used.
constexpr float FLOAT_INFINITY = std::numeric_limits<float>::infinity();
constexpr double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();

//! The smallest positive value where 1.0f + FLT_EPSILON != 1.0f
constexpr float FLOAT_EPSILON = std::numeric_limits<float>::epsilon();
constexpr double DOUBLE_EPSILON = std::numeric_limits<double>::epsilon();

//! The smallest normal positive value
constexpr float FLOAT_MIN = std::numeric_limits<float>::min();
constexpr double DOUBLE_MIN = std::numeric_limits<double>::min();

//! The largest normal value
constexpr float FLOAT_MAX = std::numeric_limits<float>::max();
constexpr double DOUBLE_MAX = std::numeric_limits<double>::max();

//! Not-a-Number value
constexpr float FLOAT_NAN = std::numeric_limits<float>::quiet_NaN();
constexpr double DOUBLE_NAN = std::numeric_limits<double>::quiet_NaN();

}  // namespace Math
}  // namespace VNE

#endif  // VNE_MATH_CONSTANTS_H
