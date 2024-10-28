#pragma once

#include <SFML/System/Vector2.hpp>

#include <array>

namespace zth {

struct Size;
struct Point2D;

struct Vec2
{
    float x;
    float y;

    constexpr Vec2 operator+(const Vec2& other) const;
    constexpr Vec2 operator-(const Vec2& other) const;
    constexpr Vec2 operator*(float val) const;
    constexpr Vec2 operator/(float val) const;

    constexpr Vec2& operator+=(const Vec2& other);
    constexpr Vec2& operator-=(const Vec2& other);
    constexpr Vec2& operator*=(float val);
    constexpr Vec2& operator/=(float val);

    constexpr Vec2 operator-() const;

    constexpr bool operator==(const Vec2& other) const;

    constexpr operator Size() const;
    constexpr operator Point2D() const;
    explicit inline operator sf::Vector2f() const;
};

struct Size
{
    float width;
    float height;

    constexpr operator Vec2() const;
    constexpr operator Point2D() const;
    explicit inline operator sf::Vector2f() const;
};

struct Point2D
{
    float x;
    float y;

    constexpr Point2D operator+(const Point2D& other) const;
    constexpr Point2D operator-(const Point2D& other) const;
    constexpr Point2D operator*(float val) const;
    constexpr Point2D operator/(float val) const;

    constexpr Point2D& operator+=(const Point2D& other);
    constexpr Point2D& operator-=(const Point2D& other);
    constexpr Point2D& operator*=(float val);
    constexpr Point2D& operator/=(float val);

    constexpr Point2D operator-() const;

    constexpr bool operator==(const Point2D& other) const;

    constexpr operator Vec2() const;
    constexpr operator Size() const;
    explicit inline operator sf::Vector2f() const;
};

struct Line
{
    Point2D from;
    Point2D to;

    constexpr bool intersects(const Line& other) const;
};

struct Rect
{
    Point2D position;
    Size size;

    constexpr std::array<Point2D, 4> points() const;
};

struct Ellipse
{
    Point2D center;
    Vec2 radius;
};

struct Circle
{
    Point2D center;
    float radius;

    explicit constexpr operator Ellipse() const;
};

constexpr bool lines_intersect(const Line& first_line, const Line& second_line);

} // namespace zth

#include "Geometry.inl"
