#pragma once

#include <SFML/Graphics/Shape.hpp>

#include <cstddef>

#include "Zenith/Math/Geometry.hpp"

namespace zth {

class EllipseShape : public sf::Shape
{
public:
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.0f, 0.0f));
    explicit EllipseShape(const Ellipse& ellipse);

    EllipseShape(const EllipseShape&) = default;
    EllipseShape(EllipseShape&&) = default;

    ~EllipseShape() override = default;

    EllipseShape& operator=(const EllipseShape&) = default;
    EllipseShape& operator=(EllipseShape&&) = default;

    void set_radius(const sf::Vector2f& radius);

    auto& get_radius() const { return _radius; }
    std::size_t getPointCount() const override { return _point_count; }
    sf::Vector2f getPoint(std::size_t index) const override;

    void update_point_count();

private:
    sf::Vector2f _radius;
    std::size_t _point_count;
};

} // namespace zth
