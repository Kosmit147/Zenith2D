#pragma once

#include <SFML/System/Vector3.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

/**
 * @brief A 3D vector class that supports various vector operations.
 *
 * This class represents a 3D vector with `x`, `y`, and `z` components. It supports a variety of operations,
 * including translation, scaling, rotation, normalization, and more. It is templated to work with various numeric types.
 *
 * @tparam T The type of the vector components (e.g., float, int).
 */
template<typename T> struct Vec3
{
    T x; ///< The x component of the vector.
    T y; ///< The y component of the vector.
    T z; ///< The z component of the vector.

    /**
     * @brief Default constructor that initializes all components to zero.
     */
    constexpr Vec3() = default;

    /**
     * @brief Constructs a vector with the given x, y, and z components.
     * 
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     */
    constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    /**
     * @brief Converts an SFML vector to a Vec3.
     * 
     * @param vec The SFML vector to convert.
     */
    explicit constexpr Vec3(const sf::Vector3<T>& vec) : x(vec.x), y(vec.y), z(vec.z) {}

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
    constexpr Vec3 normalized() const;

    /**
     * @brief Normalizes the vector in place (magnitude = 1).
     * 
     * @return The normalized vector.
     */
    constexpr Vec3& normalize();

    /**
     * @brief Returns a new vector with absolute values of the x, y, and z components.
     * 
     * @return A vector with absolute values for all components.
     */
    constexpr Vec3 abs() const;

    /**
     * @brief Reflects the vector over a given normal vector.
     * 
     * @param normal The normal vector.
     * @return A new reflected vector.
     */
    constexpr Vec3 reflected(const Vec3& normal) const;

    /**
     * @brief Reflects the vector over a given normal vector in place.
     * 
     * @param normal The normal vector.
     * @return The reflected vector.
     */
    constexpr Vec3& reflect(const Vec3& normal);

    /**
     * @brief Adds two vectors.
     * 
     * @param other The vector to add.
     * @return The sum of the vectors.
     */
    constexpr Vec3 operator+(const Vec3& other) const;

    /**
     * @brief Subtracts one vector from another.
     * 
     * @param other The vector to subtract.
     * @return The difference between the vectors.
     */
    constexpr Vec3 operator-(const Vec3& other) const;

    /**
     * @brief Multiplies the vector by a scalar value.
     * 
     * @param val The scalar value.
     * @return The scaled vector.
     */
    constexpr Vec3 operator*(T val) const;

    /**
     * @brief Divides the vector by a scalar value.
     * 
     * @param val The scalar value.
     * @return The resulting vector.
     */
    constexpr Vec3 operator/(T val) const;

    /**
     * @brief Adds another vector in place.
     * 
     * @param other The vector to add.
     * @return The updated vector.
     */
    constexpr Vec3& operator+=(const Vec3& other);

    /**
     * @brief Subtracts another vector in place.
     * 
     * @param other The vector to subtract.
     * @return The updated vector.
     */
    constexpr Vec3& operator-=(const Vec3& other);

    /**
     * @brief Multiplies the vector by a scalar value in place.
     * 
     * @param val The scalar value.
     * @return The updated vector.
     */
    constexpr Vec3& operator*=(T val);

    /**
     * @brief Divides the vector by a scalar value in place.
     * 
     * @param val The scalar value.
     * @return The updated vector.
     */
    constexpr Vec3& operator/=(T val);

    /**
     * @brief Negates the vector (inverts its direction).
     * 
     * @return The negated vector.
     */
    constexpr Vec3 operator-() const;

    /**
     * @brief Compares two vectors for equality.
     * 
     * @param other The vector to compare.
     * @return `true` if the vectors are equal, `false` otherwise.
     */
    constexpr auto operator<=>(const Vec3& other) const = default;

    /**
     * @brief Converts the vector to another type.
     * 
     * @tparam Other The target type.
     * @return The converted vector.
     */
    template<typename Other> constexpr explicit operator Vec3<Other>() const;

    /**
     * @brief Converts the vector to an SFML vector.
     * 
     * @return The SFML vector representation of the vector.
     */
    constexpr explicit operator sf::Vector3<T>() const;
};

using Vec3u = Vec3<u32>; ///< A 3D vector of unsigned integers.
using Vec3i = Vec3<i32>; ///< A 3D vector of signed integers.
using Vec3f = Vec3<float>; ///< A 3D vector of floating-point numbers.
using Vec3d = Vec3<double>; ///< A 3D vector of double precision floating-point numbers.

/**
 * @brief Multiplies a scalar value by a vector.
 * 
 * @tparam T The type of the vector components.
 * @param val The scalar value.
 * @param vec The vector to scale.
 * @return The scaled vector.
 */
template<typename T> constexpr Vec3<T> operator*(T val, const Vec3<T>& vec);

/**
 * @brief Returns a vector with absolute values of the x, y, and z components.
 * 
 * @tparam T The type of the vector components.
 * @param vec The vector to get the absolute values of.
 * @return A new vector with absolute values.
 */
template<typename T> constexpr Vec3<T> abs(const Vec3<T>& vec);

/**
 * @brief Computes the dot product of two vectors.
 * 
 * @tparam T The type of the vector components.
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b);

/**
 * @brief Computes the dot product of three vectors.
 * 
 * @tparam T The type of the vector components.
 * @param a The first vector.
 * @param b The second vector.
 * @param c The third vector.
 * @return The dot product of the three vectors.
 */
template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c);

/**
 * @brief Computes the cross product of two vectors.
 * 
 * @tparam T The type of the vector components.
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product of the two vectors.
 */
template<typename T> constexpr Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);

} // namespace zth

#include "Vec3.inl"
