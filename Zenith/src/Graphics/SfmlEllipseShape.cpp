#include "Zenith/Graphics/SfmlEllipseShape.hpp"

namespace zth {

SfmlEllipseShape::SfmlEllipseShape(const sf::Vector2f& radius) : _radius(radius)
{
    update_point_count();
    update();
}

SfmlEllipseShape::SfmlEllipseShape(const Ellipse& ellipse) : _radius(ellipse.radius)
{
    update_point_count();
    setPosition(static_cast<sf::Vector2f>(ellipse.center - ellipse.radius));
    update();
}

void SfmlEllipseShape::set_radius(const sf::Vector2f& radius)
{
    _radius = radius;
    update();
}

sf::Vector2f SfmlEllipseShape::getPoint(std::size_t index) const
{
    constexpr auto pi = std::numbers::pi_v<float>;

    float angle = static_cast<float>(index) * 2.0f * pi / static_cast<float>(getPointCount()) - pi / 2.0f;
    float x = std::cos(angle) * _radius.x;
    float y = std::sin(angle) * _radius.y;

    return { _radius.x + x, _radius.y + y };
}

void SfmlEllipseShape::update_point_count()
{
    _point_count = static_cast<std::size_t>(std::ceil(std::max(_radius.x, _radius.y)));
}

} // namespace zth
