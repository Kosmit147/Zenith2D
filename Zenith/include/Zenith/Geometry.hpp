#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>
#include <type_traits>

#include "Typedefs.hpp"

namespace zth {

template<typename T> struct Vec2
{
    T x;
    T y;

    Vec2() = default;
    Vec2(T x, T y) : x(x), y(y) {}
    explicit Vec2(const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) {}

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
