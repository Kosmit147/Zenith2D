/**
 * @file TriangleShape.hpp
 * @brief Declares the TriangleShape class, a drawable shape representing a triangle.
 */

#pragma once

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Shapes/Shape.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Renderer;

/**
 * @class TriangleShape
 * @brief A drawable 2D triangle shape that supports transformations and rendering.
 *
 * The TriangleShape class represents a triangle with position, rotation, and scaling capabilities.
 * It can be drawn using a Renderer and supports 2D transformations.
 */
class TriangleShape : public Shape
{
public:
    /// The geometric representation of the triangle.
    Triangle triangle{};

public:
    /**
     * @brief Default constructor for TriangleShape.
     */
    explicit TriangleShape() = default;

    /**
     * @brief Constructs a TriangleShape with a specified triangle geometry.
     * @param triangle The Triangle geometry defining the shape.
     */
    explicit TriangleShape(const Triangle& triangle);

    /**
     * @brief Constructs a TriangleShape with a specified triangle geometry and color.
     * @param triangle The Triangle geometry defining the shape.
     * @param color The color of the triangle shape.
     */
    explicit TriangleShape(const Triangle& triangle, const Color& color);

    /// Default copy and move constructors and assignments.
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(TriangleShape)

    /**
     * @brief Virtual destructor for TriangleShape.
     */
    ~TriangleShape() override = default;

    /**
     * @brief Draws the triangle using the specified renderer.
     * @param renderer The renderer to use for drawing the shape.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Translates (moves) the triangle by a specified vector.
     * @param translation The translation vector.
     * @return Reference to the transformed object.
     */
    Transformable2D& translate(const Vec2f& translation) override;

    /**
     * @brief Rotates the triangle by a specified angle around its origin.
     * @param angle The rotation angle in degrees.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle) override;

    /**
     * @brief Rotates the triangle by a specified angle around a pivot point.
     * @param angle The rotation angle in degrees.
     * @param pivot_point The point around which to rotate the shape.
     * @return Reference to the rotated object.
     */
    Transformable2D& rotate(float angle, const Vec2f& pivot_point) override;

    /**
     * @brief Scales the triangle by a specified factor from its origin.
     * @param factor The scaling factor.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor) override;

    /**
     * @brief Scales the triangle by a specified factor from a scaling point.
     * @param factor The scaling factor.
     * @param scaling_point The point from which to scale the shape.
     * @return Reference to the scaled object.
     */
    Transformable2D& scale(float factor, const Vec2f& scaling_point) override;
};

} // namespace zth
