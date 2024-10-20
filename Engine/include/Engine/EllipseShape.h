#pragma once

#include <SFML/Graphics/Shape.hpp>

#include "Geometry.h"

class EllipseShape : public sf::Shape
{
public:
    EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.0f, 0.0f));
    EllipseShape(Ellipse ellipse);

    inline virtual ~EllipseShape(){};

    void setRadius(const sf::Vector2f& radius);

    inline auto& getRadius() const { return _radius; }
    inline virtual size_t getPointCount() const override { return _pointCount; }

    void updatePointCount();

    virtual sf::Vector2f getPoint(size_t index) const override;

private:
    sf::Vector2f _radius;
    size_t _pointCount;
};
