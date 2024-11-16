#pragma once

namespace zth {

constexpr Line Line::translated(const Vec2f& translation) const
{
    return { from + translation, to + translation };
}

constexpr Line& Line::translate(const Vec2f& translation)
{
    return *this = this->translated(translation);
}

constexpr Line Line::rotated(float angle, const Vec2f& pivot_point) const
{
    return { from.rotated(angle, pivot_point), to.rotated(angle, pivot_point) };
}

constexpr Line& Line::rotate(float angle, const Vec2f& pivot_point)
{
    return *this = this->rotated(angle, pivot_point);
}

constexpr Line Line::scaled(float factor, const Vec2f& scaling_point) const
{
    return { from.scaled(factor, scaling_point), to.scaled(factor, scaling_point) };
}

constexpr Line& Line::scale(float factor, const Vec2f& scaling_point)
{
    return *this = this->scaled(factor, scaling_point);
}

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

constexpr Rect Rect::translated(const Vec2f& translation) const
{
    return { position + translation, size };
}

constexpr Rect& Rect::translate(const Vec2f& translation)
{
    return *this = this->translated(translation);
}

// constexpr Rect Rect::rotated(float angle, const Vec2f& pivot_point) const
// {
//     auto rect_points = points();
//
//     for (auto& point : rect_points)
//         point = point.rotated(angle, pivot_point);
//
//     return { rect_points[0], size };
// }
//
// constexpr Rect& Rect::rotate(float angle, const Vec2f& pivot_point)
// {
//     *this = rotated(angle, pivot_point);
// }

constexpr Rect Rect::scaled(float factor, const Vec2f& scaling_point) const
{
    auto scaled_pos = position.scaled(factor, scaling_point);
    auto scaled_size = size * factor;

    if (factor < 0.0f)
    {
        scaled_pos += scaled_size;
        scaled_size = abs(scaled_size);
    }

    return { scaled_pos, scaled_size };
}

constexpr Rect& Rect::scale(float factor, const Vec2f& scaling_point)
{
    return *this = scaled(factor, scaling_point);
}

// the first point is the position (top-left point)
inline Rect Rect::from_sf_rect(const sf::FloatRect& rect)
{
    return {
        .position = static_cast<Vec2f>(rect.getPosition()),
        .size = static_cast<Vec2f>(rect.getSize()),
    };
}

constexpr Vec2f Rect::center() const
{
    return (position + (position + size)) / 2.0f;
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

constexpr Rect Circle::bounds() const
{
    auto half_size = Vec2f{ radius, radius };
    return { center - half_size, half_size * 2.0f };
}

constexpr Rect Ellipse::bounds() const
{
    return { center - radius, radius * 2.0f };
}

constexpr bool lines_intersect(const Line& first_line, const Line& second_line)
{
    return first_line.intersects(second_line);
}

} // namespace zth
