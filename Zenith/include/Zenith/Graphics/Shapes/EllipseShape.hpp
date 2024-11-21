/**
 * @file EllipseShape.hpp
 * @brief Declares the EllipseShape class, a drawable shape representing an ellipse.
 */

#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

/**
 * @class EllipseShape
 * @brief A drawable 2D ellipse shape that supports transformations and rendering.
 *
 * The EllipseShape class represents an ellipse with position, rotation, and scaling capabilities.
 * It can be drawn using a Renderer and supports 2D transformations.
 */
class EllipseShape : public Shape
{
public:
    /// The geometric representation of the ellipse.
    Ellipse ellipse{};

public:
    /**
     * @brief Default constructor for EllipseShape.
     */
    explicit EllipseShape() = default;

    /**
     * @brief Constructs an EllipseShape with a specified ellipse geometry.
     * @param ellipse The Ellipse geometry defining the shape.
     */
    explicit EllipseShape(const Ellipse& ellipse);

    /**
     * @brief Constructs an EllipseShape with a specified ellipse geometry and color.
     * @param ellipse The Ellipse geometry defining the shape.
     * @param color The color of the ellipse shape.
     */
    explicit EllipseShape(const Ellipse& ellipse, const Color& color);

    /// Default copy and move constructors and assignments.
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(EllipseShape)

    /**
     * @brief Virtual destructor for EllipseShape.
     */
    ~EllipseShape() override = default;

    /**
     * @brief Draws the ellipse using the specified renderer.
     * @param renderer The renderer to use for drawing the shape.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Translates (moves) the ellipse by a specified vector.
     * @param translation The translation vector.
     * @return Reference to the transformed object.
     */
    Transformable2D& translate(const Vec2f& translation) override;

    /**
     * @brief Rotates the ellipse by a specified angle around its origin.
     * @param angle The rotation angle in degrees.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle) override;

    /**
     * @brief Rotates the ellipse by a specified angle around a pivot point.
     * @param angle The rotation angle in degrees.
     * @param pivot_point The point around which to rotate the shape.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;

    /**
     * @brief Scales the ellipse by a specified factor from its origin.
     * @param factor The scaling factor.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor) override;

    /**
     * @brief Scales the ellipse by a specified factor from a scaling point.
     * @param factor The scaling factor.
     * @param scaling_point The point from which to scale the shape.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
