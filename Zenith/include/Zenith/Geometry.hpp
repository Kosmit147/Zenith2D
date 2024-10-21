#pragma once

#include <SFML/System/Vector2.hpp>

namespace zth {

struct Point2D;

struct Vec2
{
    float x;
    float y;

    constexpr operator Point2D() const;
    explicit inline operator sf::Vector2f() const;
};

struct Point2D
{
    float x;
    float y;

    constexpr operator Vec2() const;
    explicit inline operator sf::Vector2f() const;

    constexpr Point2D operator+(const Point2D& other) const;
    constexpr Point2D operator-(const Point2D& other) const;
    template<typename T> constexpr Point2D operator*(T val) const;
    template<typename T> constexpr Point2D operator/(T val) const;

    constexpr Point2D& operator+=(const Point2D& other);
    constexpr Point2D& operator-=(const Point2D& other);
    template<typename T> constexpr Point2D& operator*=(T val);
    template<typename T> constexpr Point2D& operator/=(T val);

    constexpr Point2D operator-() const;

    constexpr bool operator==(const Point2D& other) const;
};

struct Line
{
    Point2D from;
    Point2D to;
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

// TODO
// wtf is this
// bool lines_intersect(const Line& first_line, const Line& second_line)
// {
//     int s1 = first_line.from.x * second_line.from.y + second_line.from.x * second_line.to.y
//              + first_line.from.y * second_line.to.x - second_line.from.y * second_line.to.x
//              - second_line.to.y * first_line.from.x - first_line.from.y * second_line.from.x;
//
//     int s2 = first_line.to.x * second_line.from.y + second_line.from.x * second_line.to.y
//              + first_line.to.y * second_line.to.x - second_line.from.y * second_line.to.x
//              - second_line.to.y * first_line.to.x - first_line.to.y * second_line.from.x;
//
//     int s3 = second_line.from.x * first_line.from.y + first_line.from.x * first_line.to.y
//              + second_line.from.y * first_line.to.x - first_line.from.y * first_line.to.x
//              - first_line.to.y * second_line.from.x - second_line.from.y * first_line.from.x;
//
//     int s4 = second_line.to.x * first_line.from.y + first_line.from.x * first_line.to.y
//              + second_line.to.y * first_line.to.x - first_line.from.y * first_line.to.x
//              - first_line.to.y * second_line.to.x - second_line.to.y * first_line.from.x;
//
//     if (s1 < 0 && s2 > 0 && s3 > 0 && s4 < 0 || s1 > 0 && s2 < 0 && s3 < 0 && s4 > 0)
//         return true;
//     else
//         return false;
// }

} // namespace zth

#include "Geometry.inl"
