/**
 * @file abs.hpp
 * @brief Defines a template function for calculating the absolute value of a number.
 * 
 * This file contains the `abs` template function, which returns the absolute value of a given
 * number. The function works for both integral and floating-point types.
 */

#pragma once

namespace zth {

/**
 * @brief Returns the absolute value of a number.
 * 
 * This function computes the absolute value of a number, which is the number without its sign.
 * If the input number is negative, the function returns its negation, and if the input is 
 * positive or zero, it returns the number unchanged.
 * 
 * @tparam T The type of the input value. It can be any type that supports comparison with zero
 *          and negation (e.g., `int`, `float`, `double`).
 * @param val The number whose absolute value is to be computed.
 * 
 * @return The absolute value of the input number.
 */
template<typename T> constexpr T abs(T val)
{
    return val < 0 ? -val : val;
}

} // namespace zth
