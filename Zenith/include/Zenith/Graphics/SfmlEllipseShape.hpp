#pragma once

#include <SFML/Graphics/Shape.hpp>

#include <cstddef>

#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class SfmlEllipseShape : public sf::Shape
{
public:
    explicit SfmlEllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.0f, 0.0f));
    explicit SfmlEllipseShape(const Ellipse& ellipse);
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(SfmlEllipseShape)

    ~SfmlEllipseShape() override = default;

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
