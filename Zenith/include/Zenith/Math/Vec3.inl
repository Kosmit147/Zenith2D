#pragma once

#include <cmath>

namespace zth {

template<typename T> constexpr T Vec3<T>::length() const
{
    return std::hypot(x, y, z);
}

template<typename T> constexpr Vec3<T> Vec3<T>::normalized() const
{
    auto len = length();

    if (len == 0)
        return { 0, 0, 0 };

    return { x / len, y / len, z / len };
}

template<typename T> constexpr void Vec3<T>::normalize()
{
    *this = this->normalized();
}

template<typename T> constexpr Vec3<T> Vec3<T>::reflected(const Vec3& normal) const
{
    return *this - normal * 2 * dot(*this, normal);
}

template<typename T> constexpr void Vec3<T>::reflect(const Vec3& normal)
{
    *this = this->reflected(normal);
}

template<typename T> constexpr Vec3<T> Vec3<T>::operator+(const Vec3& other) const
{
    return { x + other.x, y + other.y, z + other.z };
}

template<typename T> constexpr Vec3<T> Vec3<T>::operator-(const Vec3& other) const
{
    return { x - other.x, y - other.y, z - other.z };
}

template<typename T> constexpr Vec3<T> Vec3<T>::operator*(T val) const
{
    return { x * val, y * val, z * val };
}

template<typename T> constexpr Vec3<T> Vec3<T>::operator/(T val) const
{
    return { x / val, y / val, z / val };
}

template<typename T> constexpr Vec3<T>& Vec3<T>::operator+=(const Vec3& other)
{
    return *this = *this + other;
}

template<typename T> constexpr Vec3<T>& Vec3<T>::operator-=(const Vec3& other)
{
    return *this = *this - other;
}

template<typename T> constexpr Vec3<T>& Vec3<T>::operator*=(T val)
{
    return *this = *this * val;
}

template<typename T> constexpr Vec3<T>& Vec3<T>::operator/=(T val)
{
    return *this = *this / val;
}

template<typename T> constexpr Vec3<T> Vec3<T>::operator-() const
{
    return { -x, -y, -z };
}

template<typename T> template<typename Other> constexpr Vec3<T>::operator Vec3<Other>() const
{
    return Vec3<Other>{ static_cast<Other>(x), static_cast<Other>(y), static_cast<Other>(z) };
}

template<typename T> constexpr Vec3<T>::operator sf::Vector3<T>() const
{
    return sf::Vector3<T>{ x, y, z };
}

template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T> constexpr T dot(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c)
{
    return a.x * b.x * c.x + a.y * b.y * c.y + a.z * b.z * c.z;
}

template<typename T> constexpr Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>{
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x,
    };
}

} // namespace zth
