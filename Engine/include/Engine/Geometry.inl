constexpr Vector2::operator Point2D() const
{
    return { .x = x, .y = y };
}

inline Vector2::operator sf::Vector2f() const
{
    return sf::Vector2f{ x, y };
}

constexpr Point2D::operator Vector2() const
{
    return { .x = x, .y = y };
}

inline Point2D::operator sf::Vector2f() const
{
    return sf::Vector2f{ x, y };
}

constexpr Point2D Point2D::operator+(const Point2D& other) const
{
    return { .x = x + other.x, .y = y + other.y };
}

constexpr Point2D Point2D::operator-(const Point2D& other) const
{
    return { .x = x - other.x, .y = y - other.y };
}

template<typename T> constexpr Point2D Point2D::operator*(T val) const
{
    return { .x = x * static_cast<float>(val), .y = y * static_cast<float>(val) };
}

template<typename T> constexpr Point2D Point2D::operator/(T val) const
{
    return { .x = x / static_cast<float>(val), .y = y / static_cast<float>(val) };
}

constexpr Point2D& Point2D::operator+=(const Point2D& other)
{
    *this = *this + other;
    return *this;
}

constexpr Point2D& Point2D::operator-=(const Point2D& other)
{
    *this = *this - other;
    return *this;
}

template<typename T> constexpr Point2D& Point2D::operator*(T val)
{
    *this = *this * val;
    return *this;
}

template<typename T> constexpr Point2D& Point2D::operator/(T val)
{
    *this = *this / val;
    return *this;
}

constexpr Point2D Point2D::operator-() const
{
    return { .x = -x, .y = -y };
}

constexpr bool Point2D::operator==(const Point2D& other) const
{
    return x == other.x && y == other.y;
}

constexpr Circle::operator Ellipse() const
{
    return Ellipse{ center, radius, radius };
}
