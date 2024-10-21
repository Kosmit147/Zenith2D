#include "EllipseShape.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace zth {

EllipseShape::EllipseShape(const sf::Vector2f& radius) : _radius(radius)
{
    updatePointCount();
    update();
}

EllipseShape::EllipseShape(Ellipse ellipse) : _radius(ellipse.radius)
{
    updatePointCount();
    setPosition(static_cast<sf::Vector2f>(ellipse.center - ellipse.radius));
    update();
}

void EllipseShape::setRadius(const sf::Vector2f& radius)
{
    _radius = radius;
    update();
}

void EllipseShape::updatePointCount()
{
    _pointCount = static_cast<std::size_t>(std::ceil(std::max(_radius.x, _radius.y)));
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const
{
    constexpr auto pi = std::numbers::pi_v<float>;

    float angle = static_cast<float>(index) * 2.0f * pi / static_cast<float>(getPointCount()) - pi / 2.0f;
    float x = std::cos(angle) * _radius.x;
    float y = std::sin(angle) * _radius.y;

    return sf::Vector2f(_radius.x + x, _radius.y + y);
}

} // namespace zth
