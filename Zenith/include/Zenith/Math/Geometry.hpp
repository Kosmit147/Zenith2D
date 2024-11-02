#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

template<typename T> struct Vec2
{
    T x;
    T y;

    constexpr Vec2() = default;
    constexpr Vec2(T x, T y) : x(x), y(y) {}
    explicit constexpr Vec2(const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) {}

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

struct Line
{
    Vec2f from;
    Vec2f to;

    constexpr bool intersects(const Line& other) const;
};

struct Rect
{
    Vec2f position;
    Vec2f size;

    constexpr std::array<Vec2f, 4> points() const;
};

struct Ellipse
{
    Vec2f center;
    Vec2f radius;
};

struct Circle
{
    Vec2f center;
    float radius;
};

constexpr bool lines_intersect(const Line& first_line, const Line& second_line);

} // namespace zth

#include "Geometry.inl"
