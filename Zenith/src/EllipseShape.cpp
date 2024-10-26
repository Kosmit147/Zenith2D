#include "EllipseShape.hpp"

namespace zth {

EllipseShape::EllipseShape(const sf::Vector2f& radius) : _radius(radius)
{
    update_point_count();
    update();
}

EllipseShape::EllipseShape(const Ellipse& ellipse) : _radius(ellipse.radius)
{
    update_point_count();
    setPosition(static_cast<sf::Vector2f>(ellipse.center - ellipse.radius));
    update();
}

void EllipseShape::set_radius(const sf::Vector2f& radius)
{
    _radius = radius;
    update();
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const
{
    constexpr auto pi = std::numbers::pi_v<float>;

    float angle = static_cast<float>(index) * 2.0f * pi / static_cast<float>(getPointCount()) - pi / 2.0f;
    float x = std::cos(angle) * _radius.x;
    float y = std::sin(angle) * _radius.y;

    return { _radius.x + x, _radius.y + y };
}

void EllipseShape::update_point_count()
{
    _point_count = static_cast<std::size_t>(std::ceil(std::max(_radius.x, _radius.y)));
}

} // namespace zth
