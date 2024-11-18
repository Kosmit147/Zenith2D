#pragma once

#include <SFML/System/Vector2.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @brief A 2D vector class that supports various vector operations.
 *
 * This class represents a 2D vector with `x` and `y` components. It supports a variety of operations, 
 * including translation, scaling, rotation, normalization, and more. It is templated to work with various numeric types.
 *
 * @tparam T The type of the vector components (e.g., float, int).
 */
template<typename T> struct Vec2
{
    T x; ///< The x component of the vector.
    T y; ///< The y component of the vector.

    /**
     * @brief Default constructor that initializes both components to zero.
     */
    constexpr Vec2() = default;

    /**
     * @brief Constructs a vector with the given x and y components.
     * 
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     */
    constexpr Vec2(T x, T y) : x(x), y(y) {}

    /**
     * @brief Converts an SFML vector to a Vec2.
     * 
     * @param vec The SFML vector to convert.
     */
    explicit constexpr Vec2(const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) {}

    /**
     * @brief Creates a unit vector from an angle.
     * 
     * @param angle The angle in degrees.
     * @return A vector representing the direction of the given angle with unit length.
     */
    static constexpr Vec2 from_angle(T angle);

    /**
     * @brief Returns the magnitude (length) of the vector.
     * 
     * @return The length of the vector.
     */
    constexpr T length() const;

    /**
     * @brief Returns a normalized (unit) vector (magnitude = 1).
     * 
     * @return A normalized vector.
     */
    constexpr Vec2 normalized() const;

    /**
     * @brief Normalizes the vector in place (magnitude = 1).
     * 
     * @return The normalized vector.
     */
    constexpr Vec2& normalize();

    /**
     * @brief Returns a new vector with absolute values of the x and y components.
     * 
     * @return A vector with absolute values for both components.
     */
    constexpr Vec2 abs() const;

    /**
     * @brief Translates the vector by the given translation vector.
     * 
     * @param translation The translation vector.
     * @return A new vector after translation.
     */
    constexpr Vec2 translated(const Vec2& translation) const;

    /**
     * @brief Translates the vector by the given translation vector in place.
     * 
     * @param translation The translation vector.
     */
    constexpr Vec2& translate(const Vec2& translation);

    /**
     * @brief Rotates the vector by a given angle (in degrees).
     * 
     * @param angle The rotation angle in degrees.
     * @return A new rotated vector.
     */
    constexpr Vec2 rotated(float angle) const;

    /**
     * @brief Rotates the vector in place by the given angle (in degrees).
     * 
     * @param angle The rotation angle in degrees.
     * @return The rotated vector.
     */
    constexpr Vec2& rotate(float angle);

    /**
     * @brief Rotates the vector around a pivot point by a given angle (in degrees).
     * 
     * @param angle The rotation angle in degrees.
     * @param pivot_point The pivot point to rotate around.
     * @return A new rotated vector.
     */
    constexpr Vec2 rotated(float angle, const Vec2& pivot_point) const;

    /**
     * @brief Rotates the vector around a pivot point by a given angle (in degrees) in place.
     * 
     * @param angle The rotation angle in degrees.
     * @param pivot_point The pivot point to rotate around.
     * @return The rotated vector.
     */
    constexpr Vec2& rotate(float angle, const Vec2& pivot_point);

    /**
     * @brief Scales the vector by the given factor.
     * 
     * @param factor The scaling factor.
     * @return A new scaled vector.
     */
    constexpr Vec2 scaled(float factor) const;

    /**
     * @brief Scales the vector by the given factor in place.
     * 
     * @param factor The scaling factor.
     * @return The scaled vector.
     */
    constexpr Vec2& scale(float factor);

    /**
     * @brief Scales the vector by the given factor around a specified scaling point.
     * 
     * @param factor The scaling factor.
     * @param scaling_point The point around which to scale.
     * @return A new scaled vector.
     */
    constexpr Vec2 scaled(float factor, const Vec2& scaling_point) const;

    /**
     * @brief Scales the vector by the given factor around a specified scaling point in place.
     * 
     * @param factor The scaling factor.
     * @param scaling_point The point around which to scale.
     * @return The scaled vector.
     */
    constexpr Vec2& scale(float factor, const Vec2& scaling_point);

    /**
     * @brief Reflects the vector over a given normal vector.
     * 
     * @param normal The normal vector.
     * @return A new reflected vector.
     */
    constexpr Vec2 reflected(const Vec2& normal) const;

    /**
     * @brief Reflects the vector over a given normal vector in place.
     * 
     * @param normal The normal vector.
     * @return The reflected vector.
     */
    constexpr Vec2& reflect(const Vec2& normal);

    /**
     * @brief Adds two vectors.
     * 
     * @param other The vector to add.
     * @return The sum of the vectors.
     */
    constexpr Vec2 operator+(const Vec2& other) const;

    /**
     * @brief Subtracts one vector from another.
     * 
     * @param other The vector to subtract.
     * @return The difference between the vectors.
     */
    constexpr Vec2 operator-(const Vec2& other) const;

    /**
     * @brief Multiplies the vector by a scalar value.
     * 
     * @param val The scalar value.
     * @return The scaled vector.
     */
    constexpr Vec2 operator*(T val) const;

    /**
     * @brief Divides the vector by a scalar value.
     * 
     * @param val The scalar value.
     * @return The resulting vector.
     */
    constexpr Vec2 operator/(T val) const;

    /**
     * @brief Adds another vector in place.
     * 
     * @param other The vector to add.
     * @return The updated vector.
     */
    constexpr Vec2& operator+=(const Vec2& other);

    /**
     * @brief Subtracts another vector in place.
     * 
     * @param other The vector to subtract.
     * @return The updated vector.
     */
    constexpr Vec2& operator-=(const Vec2& other);

    /**
     * @brief Multiplies the vector by a scalar value in place.
     * 
     * @param val The scalar value.
     * @return The updated vector.
     */
    constexpr Vec2& operator*=(T val);

    /**
     * @brief Divides the vector by a scalar value in place.
     * 
     * @param val The scalar value.
     * @return The updated vector.
     */
    constexpr Vec2& operator/=(T val);

    /**
     * @brief Negates the vector (inverts its direction).
     * 
     * @return The negated vector.
     */
    constexpr Vec2 operator-() const;

    /**
     * @brief Compares two vectors for equality.
     * 
     * @param other The vector to compare.
     * @return `true` if the vectors are equal, `false` otherwise.
     */
    constexpr auto operator<=>(const Vec2& other) const = default;

    /**
     * @brief Converts the vector to another type.
     * 
     * @tparam Other The target type.
     * @return The converted vector.
     */
    template<typename Other> constexpr explicit operator Vec2<Other>() const;

    /**
     * @brief Converts the vector to an SFML vector.
     * 
     * @return The SFML vector representation of the vector.
     */
    constexpr explicit operator sf::Vector2<T>() const;
};

using Vec2u = Vec2<u32>; ///< A 2D vector of unsigned integers.
using Vec2i = Vec2<i32>; ///< A 2D vector of signed integers.
using Vec2f = Vec2<float>; ///< A 2D vector of floating-point numbers.
using Vec2d = Vec2<double>; ///< A 2D vector of double precision floating-point numbers.

/**
 * @brief Multiplies a scalar value by a vector.
 * 
 * @tparam T The type of the vector components.
 * @param val The scalar value.
 * @param vec The vector to scale.
 * @return The scaled vector.
 */
template<typename T> constexpr Vec2<T> operator*(T val, const Vec2<T>& vec);

/**
 * @brief Returns a vector with absolute values of the x and y components.
 * 
 * @tparam T The type of the vector components.
 * @param vec The vector to get the absolute values of.
 * @return A new vector with absolute values.
 */
template<typename T> constexpr Vec2<T> abs(const Vec2<T>& vec);

/**
 * @brief Computes the dot product of two vectors.
 * 
 * @tparam T The type of the vector components.
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
template<typename T> constexpr T dot(const Vec2<T>& a, const Vec2<T>& b);

} // namespace zth

#include "Vec2.inl"
