#pragma once

#include <cmath>

namespace zth {

template<typename T> constexpr Vec2<T> Vec2<T>::from_angle(T angle)
{
    return { std::cos(angle), std::sin(angle) };
}

template<typename T> constexpr T Vec2<T>::length() const
{
    return std::hypot(x, y);
}

template<typename T> constexpr Vec2<T> Vec2<T>::normalized() const
{
    auto len = length();

    if (len == 0)
        return { 0, 0 };

    return { x / len, y / len };
}

template<typename T> constexpr void Vec2<T>::normalize()
{
    *this = this->normalized();
}

template<typename T> constexpr Vec2<T> Vec2<T>::reflected(const Vec2& normal) const
{
    return *this - normal * 2 * dot(*this, normal);
}

template<typename T> constexpr void Vec2<T>::reflect(const Vec2& normal)
{
    *this = this->reflected(normal);
}

template<typename T> constexpr Vec2<T> Vec2<T>::translated(const Vec2& translation) const
{
    return *this + translation;
}

template<typename T> constexpr void Vec2<T>::translate(const Vec2& translation)
{
    *this = this->translated(translation);
}

template<typename T> constexpr Vec2<T> Vec2<T>::rotated(float angle, const Vec2& pivot_point) const
{
    auto diff = *this - pivot_point;

    auto new_x = pivot_point.x + diff.x * std::cos(angle) - diff.y * std::sin(angle);
    auto new_y = pivot_point.y + diff.x * std::sin(angle) + diff.y * std::cos(angle);

    return { new_x, new_y };
}

template<typename T> constexpr void Vec2<T>::rotate(float angle, const Vec2& pivot_point)
{
    *this = this->rotated(angle, pivot_point);
}

template<typename T> constexpr Vec2<T> Vec2<T>::scaled(float factor, const Vec2& scaling_point) const
{
    return { this->x * factor + (1 - factor) * scaling_point.x, this->y * factor + (1 - factor) * scaling_point.y };
}

template<typename T> constexpr void Vec2<T>::scale(float factor, const Vec2& scaling_point)
{
    *this = this->scaled(factor, scaling_point);
}

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

template<typename T> constexpr T dot(const Vec2<T>& a, const Vec2<T>& b)
{
    return a.x * b.x + a.y * b.y;
}

} // namespace zth
