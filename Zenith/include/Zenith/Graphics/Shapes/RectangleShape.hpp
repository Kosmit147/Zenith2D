/**
 * @file RectangleShape.hpp
 * @brief Declares the RectangleShape class, a drawable shape representing a rectangle.
 */

#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

/**
 * @class RectangleShape
 * @brief A drawable 2D rectangle shape that supports transformations and rendering.
 *
 * The RectangleShape class represents a rectangle with position, rotation, and scaling capabilities.
 * It can be drawn using a Renderer and supports 2D transformations.
 */
class RectangleShape : public Shape
{
public:
    /// The geometric representation of the rectangle.
    Rect rect{};

public:
    /**
     * @brief Default constructor for RectangleShape.
     */
    explicit RectangleShape() = default;

    /**
     * @brief Constructs a RectangleShape with a specified rectangle geometry.
     * @param rect The Rect geometry defining the shape.
     */
    explicit RectangleShape(const Rect& rect);

    /**
     * @brief Constructs a RectangleShape with a specified rectangle geometry and color.
     * @param rect The Rect geometry defining the shape.
     * @param color The color of the rectangle shape.
     */
    explicit RectangleShape(const Rect& rect, const Color& color);

    /// Default copy and move constructors and assignments.
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(RectangleShape)

    /**
     * @brief Virtual destructor for RectangleShape.
     */
    ~RectangleShape() override = default;

    /**
     * @brief Draws the rectangle using the specified renderer.
     * @param renderer The renderer to use for drawing the shape.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Translates (moves) the rectangle by a specified vector.
     * @param translation The translation vector.
     * @return Reference to the transformed object.
     */
    Transformable2D& translate(const Vec2f& translation) override;

    /**
     * @brief Rotates the rectangle by a specified angle around its origin.
     * @param angle The rotation angle in degrees.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle) override;

    /**
     * @brief Rotates the rectangle by a specified angle around a pivot point.
     * @param angle The rotation angle in degrees.
     * @param pivot_point The point around which to rotate the shape.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;

    /**
     * @brief Scales the rectangle by a specified factor from its origin.
     * @param factor The scaling factor.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor) override;

    /**
     * @brief Scales the rectangle by a specified factor from a scaling point.
     * @param factor The scaling factor.
     * @param scaling_point The point from which to scale the shape.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
