#pragma once

namespace zth {

constexpr bool Line::intersects(const Line& other) const
{
    auto det = [](const Vec2f& a, const Vec2f& b, const Vec2f& c) {
        return a.x * c.y + c.x * b.y + a.y * b.x - c.y * b.x - b.y * a.x - a.y * c.x;
    };

    auto& [a, b] = *this;
    auto& [c, d] = other;

    float d1 = det(a, d, c);
    float d2 = det(b, d, c);
    float d3 = det(c, b, a);
    float d4 = det(d, b, a);

    if ((d1 < 0.0f && d2 > 0.0f && d3 > 0.0f && d4 < 0.0f) || (d1 > 0.0f && d2 < 0.0f && d3 < 0.0f && d4 > 0.0f))
        return true;
    else
        return false;
}

constexpr std::array<Vec2f, 4> Rect::points() const
{
    auto [x1, y1] = position;
    auto [x2, y2] = position + size;

    return {
        Vec2f{ x1, y1 },
        Vec2f{ x2, y1 },
        Vec2f{ x2, y2 },
        Vec2f{ x1, y2 },
    };
}

inline IntRect::operator sf::Rect<i32>() const
{
    return sf::Rect<i32>{
        static_cast<sf::Vector2i>(position),
        static_cast<sf::Vector2i>(size),
    };
}

inline UIntRect::operator sf::Rect<u32>() const
{
    return sf::Rect<u32>{
        static_cast<sf::Vector2u>(position),
        static_cast<sf::Vector2u>(size),
    };
}

constexpr bool lines_intersect(const Line& first_line, const Line& second_line)
{
    return first_line.intersects(second_line);
}
constexpr Line Line::translated(const Vec2<float>& translation) const
{
    return { from.translated(translation), to.translated(translation) };
}

constexpr void Line::translate(const Vec2<float>& translation)
{
    from.translate(translation);
    to.translate(translation);
}

constexpr Line Line::rotated(float angle, const Vec2f& pivot_point) const
{
    return { from.rotated(angle, pivot_point), to.rotated(angle, pivot_point) };
}

constexpr void Line::rotate(float angle, const Vec2f& pivot_point)
{
    from.rotate(angle, pivot_point);
    to.rotate(angle, pivot_point);
}

constexpr Line Line::scaled(float factor, const Vec2f& scaling_point) const
{
    return { from.scaled(factor, scaling_point), to.scaled(factor, scaling_point) };
}
constexpr void Line::scale(float factor, const Vec2f& scaling_point)
{
    from.scale(factor, scaling_point);
    to.scale(factor, scaling_point);
}

constexpr Rect Rect::translated(const Vec2<float>& translation) const
{
    return { position + translation, size };
}

constexpr void Rect::translate(const Vec2<float>& translation)
{
    position.translate(translation);
}

constexpr Rect Rect::rotated(float angle, const Vec2<float>& pivot_point) const
{
    auto rect_points = points();
    for (auto& point : rect_points)
    {
        point = point.rotated(angle, pivot_point);
    }
    return { rect_points[0], size };
}

constexpr void Rect::rotate(float angle, const Vec2<float>& pivot_point)
{
    *this = rotated(angle, pivot_point);
}

constexpr Rect Rect::scaled(float factor, const Vec2<float>& scaling_point) const
{
    auto rect_points = points();
    for (auto& point : rect_points)
    {
        point = scaling_point + (point - scaling_point) * factor;
    }
    return { rect_points[0], size * factor };
}

constexpr void Rect::scale(float factor, const Vec2<float>& scaling_point)
{
    *this = scaled(factor, scaling_point);
}

} // namespace zth
