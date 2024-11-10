#pragma once

#include <SFML/System/Vector2.hpp>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

template<typename T> struct Vec2
{
    T x;
    T y;

    constexpr Vec2() = default;
    constexpr Vec2(T x, T y) : x(x), y(y) {}
    explicit constexpr Vec2(const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) {}

    static constexpr Vec2 from_angle(T angle);

    constexpr T length() const;
    constexpr Vec2 normalized() const;
    constexpr void normalize();
    constexpr Vec2 reflected(const Vec2& normal) const;
    constexpr void reflect(const Vec2& normal);
    constexpr Vec2 translated(const Vec2& translation) const;
    constexpr void translate(const Vec2& translation);
    constexpr Vec2 rotated(float angle, const Vec2& pivot_point) const;
    constexpr void rotate(float angle, const Vec2& pivot_point);
    constexpr Vec2 scaled(float factor, const Vec2& scaling_point) const;
    constexpr void scale(float factor, const Vec2& scaling_point);

    constexpr Vec2 operator+(const Vec2& other) const;
    constexpr Vec2 operator-(const Vec2& other) const;
    constexpr Vec2 operator*(T val) const;
    constexpr Vec2 operator/(T val) const;

    constexpr Vec2& operator+=(const Vec2& other);
    constexpr Vec2& operator-=(const Vec2& other);
    constexpr Vec2& operator*=(T val);
    constexpr Vec2& operator/=(T val);

    constexpr Vec2 operator-() const;

    constexpr auto operator<=>(const Vec2& other) const = default;

    template<typename Other> constexpr explicit operator Vec2<Other>() const;
    constexpr explicit operator sf::Vector2<T>() const;
};

using Vec2u = Vec2<u32>;
using Vec2i = Vec2<i32>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;

template<typename T> constexpr T dot(const Vec2<T>& a, const Vec2<T>& b);

} // namespace zth

#include "Vec2.inl"
