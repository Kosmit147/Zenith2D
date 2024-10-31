#pragma once

namespace zth {

template<typename T> constexpr Vec2<T> Vec2<T>::operator+(const Vec2& other) const
{
    return { x + other.x, y + other.y };
}

template<typename T> constexpr Vec2<T> Vec2<T>::operator-(const Vec2& other) const
{
    return { x - other.x, y - other.y };
}

template<typename T> constexpr Vec2<T> Vec2<T>::operator*(T val) const
{
    return { x * val, y * val };
}

template<typename T> constexpr Vec2<T> Vec2<T>::operator/(T val) const
{
    return { x / val, y / val };
}

template<typename T> constexpr Vec2<T>& Vec2<T>::operator+=(const Vec2& other)
{
    return *this = *this + other;
}

template<typename T> constexpr Vec2<T>& Vec2<T>::operator-=(const Vec2& other)
{
    return *this = *this - other;
}

template<typename T> constexpr Vec2<T>& Vec2<T>::operator*=(T val)
{
    return *this = *this * val;
}

template<typename T> constexpr Vec2<T>& Vec2<T>::operator/=(T val)
{
    return *this = *this / val;
}

template<typename T> constexpr Vec2<T> Vec2<T>::operator-() const
{
    return { -x, -y };
}

template<typename T> template<typename Other> constexpr Vec2<T>::operator Vec2<Other>() const
{
    return Vec2<Other>{ static_cast<Other>(x), static_cast<Other>(y) };
}

template<typename T> constexpr Vec2<T>::operator sf::Vector2<T>() const
{
    return sf::Vector2<T>{ x, y };
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

constexpr bool lines_intersect(const Line& first_line, const Line& second_line)
{
    return first_line.intersects(second_line);
}

} // namespace zth
