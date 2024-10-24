namespace zth {

constexpr Vec2 Vec2::operator+(const Vec2& other) const
{
    return { .x = x + other.x, .y = y + other.y };
}

constexpr Vec2 Vec2::operator-(const Vec2& other) const
{
    return { .x = x - other.x, .y = y - other.y };
}

constexpr Vec2 Vec2::operator*(float val) const
{
    return { .x = x * val, .y = y * val };
}

constexpr Vec2 Vec2::operator/(float val) const
{
    return { .x = x / val, .y = y / val };
}

constexpr Vec2& Vec2::operator+=(const Vec2& other)
{
    *this = *this + other;
    return *this;
}

constexpr Vec2& Vec2::operator-=(const Vec2& other)
{
    *this = *this - other;
    return *this;
}

constexpr Vec2& Vec2::operator*=(float val)
{
    *this = *this * val;
    return *this;
}

constexpr Vec2& Vec2::operator/=(float val)
{
    *this = *this / val;
    return *this;
}

constexpr Vec2 Vec2::operator-() const
{
    return { .x = -x, .y = -y };
}

constexpr bool Vec2::operator==(const Vec2& other) const
{
    return x == other.x && y == other.y;
}

constexpr Vec2::operator Size() const
{
    return Size{ x, y };
}

constexpr Vec2::operator Point2D() const
{
    return Point2D{ x, y };
}

inline Vec2::operator sf::Vector2f() const
{
    return sf::Vector2f{ x, y };
}

constexpr Size::operator Vec2() const
{
    return Vec2{ width, height };
}

inline Size::operator sf::Vector2f() const
{
    return sf::Vector2f{ width, height };
}

constexpr Point2D Point2D::operator+(const Point2D& other) const
{
    return { .x = x + other.x, .y = y + other.y };
}

constexpr Point2D Point2D::operator-(const Point2D& other) const
{
    return { .x = x - other.x, .y = y - other.y };
}

constexpr Point2D Point2D::operator*(float val) const
{
    return { .x = x * val, .y = y * val };
}

constexpr Point2D Point2D::operator/(float val) const
{
    return { .x = x / val, .y = y / val };
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

constexpr Point2D& Point2D::operator*=(float val)
{
    *this = *this * val;
    return *this;
}

constexpr Point2D& Point2D::operator/=(float val)
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

constexpr Point2D::operator Vec2() const
{
    return Vec2{ x, y };
}

inline Point2D::operator sf::Vector2f() const
{
    return sf::Vector2f{ x, y };
}

constexpr bool Line::intersects(const Line& other) const
{
    auto det = [](const Point2D& a, const Point2D& b, const Point2D& c) {
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

constexpr Circle::operator Ellipse() const
{
    return Ellipse{ center, { radius, radius } };
}

constexpr bool lines_intersect(const Line& first_line, const Line& second_line)
{
    return first_line.intersects(second_line);
}

} // namespace zth
