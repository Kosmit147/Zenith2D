#pragma once

#include <SFML/Graphics/Shape.hpp>

#include <cstddef>

#include "Geometry.hpp"

namespace zth {

class EllipseShape : public sf::Shape
{
public:
    EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.0f, 0.0f));
    EllipseShape(Ellipse ellipse);

    inline virtual ~EllipseShape(){};

    void setRadius(const sf::Vector2f& radius);

    inline auto& getRadius() const { return _radius; }
    inline virtual std::size_t getPointCount() const override { return _pointCount; }

    void updatePointCount();

    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:
    sf::Vector2f _radius;
    std::size_t _pointCount;
};

} // namespace zth
