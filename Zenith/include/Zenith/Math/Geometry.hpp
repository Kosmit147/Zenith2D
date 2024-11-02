#pragma once

#include <array>

#include "Zenith/Math/Vec2.hpp"

namespace zth {

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