#pragma once

#include <SFML/System/Vector3.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

template<typename T> struct Vec3
{
    T x;
    T y;
    T z;

    constexpr Vec3() = default;
    constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    explicit constexpr Vec3(const sf::Vector3<T>& vec) : x(vec.x), y(vec.y), z(vec.z) {}

    constexpr T length() const;
    constexpr Vec3 normalized() const;
    constexpr void normalize();
    constexpr Vec3 reflected(const Vec3& normal) const;
    constexpr void reflect(const Vec3& normal);

    constexpr Vec3 operator+(const Vec3& other) const;
    constexpr Vec3 operator-(const Vec3& other) const;
    constexpr Vec3 operator*(T val) const;
    constexpr Vec3 operator/(T val) const;

    constexpr Vec3& operator+=(const Vec3& other);
    constexpr Vec3& operator-=(const Vec3& other);
    constexpr Vec3& operator*=(T val);
    constexpr Vec3& operator/=(T val);

    constexpr Vec3 operator-() const;

    constexpr auto operator<=>(const Vec3& other) const = default;

    template<typename Other> constexpr explicit operator Vec3<Other>() const;
    constexpr explicit operator sf::Vector3<T>() const;
};

using Vec3u = Vec3<u32>;
using Vec3i = Vec3<i32>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b);
template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c);
template<typename T> constexpr Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);

} // namespace zth

#include "Vec3.inl"
