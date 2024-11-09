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
    constexpr Line() = default;
    constexpr Line(const Vec2f& from, const Vec2f& to) : from(from), to(to) {}
    constexpr Line translated_line(const Vec2f& translation) const;
    constexpr void translate_line(const Vec2f& translation);
    constexpr Line rotated_line(const float& angle, const Vec2f& pivot_point) const;
    constexpr void rotate_line(const float& angle, const Vec2f& pivot_point);
    constexpr Line scaled_line(const float& factor, const Vec2f& scaling_point) const;
    constexpr void scale_line(const float& factor, const Vec2f& scaling_point);

    constexpr bool intersects(const Line& other) const;
};

struct Rect
{
    Vec2f position;
    Vec2f size;
    constexpr Rect translated_rect(const Vec2f& translation) const;
    constexpr void translate_rect(const Vec2f& translation);
    constexpr Rect rotated_rect(const float& angle, const Vec2f& pivot_point) const;
    constexpr void rotate_rect(const float& angle, const Vec2f& pivot_point);
    constexpr Rect scaled_rect(const float& factor, const Vec2f& scaling_point) const;
    constexpr void scale_rect(const float& factor, const Vec2f& scaling_point);
    constexpr std::array<Vec2f, 4> points() const;
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
bool points_form_a_valid_polygon(std::span<const Vec2f> points);
bool lines_form_a_valid_polygon(std::span<const Line> lines);
} // namespace zth

#include "Geometry.inl"
