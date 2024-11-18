#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <span>

#include "Zenith/Math/Vec2.hpp"

namespace zth {

struct Line
{
    Vec2f from;
    Vec2f to;

    constexpr Line translated(const Vec2f& translation) const;
    constexpr Line& translate(const Vec2f& translation);
    constexpr Line rotated(float angle) const;
    constexpr Line& rotate(float angle);
    constexpr Line rotated(float angle, const Vec2f& pivot_point) const;
    constexpr Line& rotate(float angle, const Vec2f& pivot_point);
    constexpr Line scaled(float factor) const;
    constexpr Line& scale(float factor);
    constexpr Line scaled(float factor, const Vec2f& scaling_point) const;
    constexpr Line& scale(float factor, const Vec2f& scaling_point);

    constexpr bool intersects(const Line& other) const;
};

struct Triangle
{
    std::array<Vec2f, 3> points;

    constexpr Triangle translated(const Vec2f& translation) const;
    constexpr Triangle& translate(const Vec2f& translation);
    constexpr Triangle rotated(float angle) const;
    constexpr Triangle& rotate(float angle);
    constexpr Triangle rotated(float angle, const Vec2f& pivot_point) const;
    constexpr Triangle& rotate(float angle, const Vec2f& pivot_point);
    constexpr Triangle scaled(float factor) const;
    constexpr Triangle& scale(float factor);
    constexpr Triangle scaled(float factor, const Vec2f& scaling_point) const;
    constexpr Triangle& scale(float factor, const Vec2f& scaling_point);
};

struct Rect
{
    Vec2f position;
    Vec2f size;

    static Rect from_sf_rect(const sf::FloatRect& rect);

    constexpr Rect translated(const Vec2f& translation) const;
    constexpr Rect& translate(const Vec2f& translation);

    // constexpr Rect rotated(float angle) const;
    // constexpr Rect& rotate(float angle);
    // constexpr Rect rotated(float angle, const Vec2f& pivot_point) const;
    // constexpr Rect& rotate(float angle, const Vec2f& pivot_point);

    constexpr Rect scaled(float factor) const;
    constexpr Rect& scale(float factor);
    constexpr Rect scaled(float factor, const Vec2f& scaling_point) const;
    constexpr Rect& scale(float factor, const Vec2f& scaling_point);

    // the first point is the position (top-left point)
    constexpr std::array<Vec2f, 4> points() const;
    constexpr Vec2f center() const;
};

struct IntRect
{
    Vec2i position;
    Vec2i size;

    explicit operator sf::Rect<i32>() const;
};

struct UIntRect
{
    Vec2u position;
    Vec2u size;

    explicit operator sf::Rect<u32>() const;
};

struct Circle
{
    Vec2f center;
    float radius;

    constexpr Circle translated(const Vec2f& translation) const;
    constexpr Circle& translate(const Vec2f& translation);
    constexpr Circle rotated(float angle) const;
    constexpr Circle& rotate(float angle);
    constexpr Circle rotated(float angle, const Vec2f& pivot_point) const;
    constexpr Circle& rotate(float angle, const Vec2f& pivot_point);
    constexpr Circle scaled(float factor) const;
    constexpr Circle& scale(float factor);
    constexpr Circle scaled(float factor, const Vec2f& scaling_point) const;
    constexpr Circle& scale(float factor, const Vec2f& scaling_point);

    constexpr Rect bounds() const;
};

struct Ellipse
{
    Vec2f center;
    Vec2f radius;

    constexpr Ellipse translated(const Vec2f& translation) const;
    constexpr Ellipse& translate(const Vec2f& translation);
    constexpr Ellipse rotated(float angle) const;
    constexpr Ellipse& rotate(float angle);
    constexpr Ellipse rotated(float angle, const Vec2f& pivot_point) const;
    constexpr Ellipse& rotate(float angle, const Vec2f& pivot_point);
    constexpr Ellipse scaled(float factor) const;
    constexpr Ellipse& scale(float factor);
    constexpr Ellipse scaled(float factor, const Vec2f& scaling_point) const;
    constexpr Ellipse& scale(float factor, const Vec2f& scaling_point);

    constexpr Rect bounds() const;
};

constexpr bool lines_intersect(const Line& first_line, const Line& second_line);
bool points_form_a_valid_polygon(std::span<const Vec2f> points);
bool lines_form_a_valid_polygon(std::span<const Line> lines);

} // namespace zth

#include "Geometry.inl"
