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

constexpr bool Rect::contains(const Vec2f& point) const
{
    auto bottom_left = position + size;

    if (point >= position && point <= bottom_left)
        return true;
    else
        return false;
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
