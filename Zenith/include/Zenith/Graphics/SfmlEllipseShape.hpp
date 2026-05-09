/**
 * @file SfmlEllipseShape.hpp
 * @brief Defines the `SfmlEllipseShape` class, a custom SFML shape for rendering ellipses.
 */

#pragma once

#include <SFML/Graphics/Shape.hpp>

#include <cstddef>

#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @class SfmlEllipseShape
 * @brief A custom SFML shape for rendering ellipses.
 *
 * `SfmlEllipseShape` is a subclass of SFML's `sf::Shape` designed to represent and render ellipses. The class allows
 * setting the radius of the ellipse and provides methods to query the number of points and get a specific point of
 * the ellipse's shape. The number of points is dynamically calculated based on the radius of the ellipse.
 */
class SfmlEllipseShape : public sf::Shape
{
public:
    /**
     * @brief Constructs an `SfmlEllipseShape` with a specified radius.
     * @param radius The radius of the ellipse (default is (0, 0)).
     */
    explicit SfmlEllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.0f, 0.0f));

    /**
     * @brief Constructs an `SfmlEllipseShape` using an `Ellipse` object.
     * @param ellipse The ellipse object from which the shape will be created.
     */
    explicit SfmlEllipseShape(const Ellipse& ellipse);

    /**
     * @brief Default copy constructor and move constructor.
     */
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(SfmlEllipseShape)

    /**
     * @brief Destructor for the `SfmlEllipseShape` class.
     */
    ~SfmlEllipseShape() override = default;

    /**
     * @brief Sets the radius of the ellipse.
     * @param radius The new radius of the ellipse.
     */
    void set_radius(const sf::Vector2f& radius);

    /**
     * @brief Gets the radius of the ellipse.
     * @return A reference to the radius of the ellipse.
     */
    auto& get_radius() const { return _radius; }

    /**
     * @brief Gets the number of points used to represent the ellipse.
     * @return The number of points in the ellipse shape.
     */
    std::size_t getPointCount() const override { return _point_count; }

    /**
     * @brief Gets the point at a specified index.
     * @param index The index of the point to retrieve.
     * @return The point at the given index.
     */
    sf::Vector2f getPoint(std::size_t index) const override;

    /**
     * @brief Updates the point count based on the current radius.
     */
    void update_point_count();

private:
    sf::Vector2f _radius; ///< The radius of the ellipse.
    std::size_t _point_count; ///< The number of points used to approximate the ellipse.
};

} // namespace zth
