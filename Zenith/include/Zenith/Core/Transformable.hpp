/**
 * @file Transformable2D.hpp
 * @brief Declares the Transformable2D interface for 2D transformations.
 */

#pragma once

#include "Zenith/Math/Vec2.hpp"

namespace zth {

/**
 * @class Transformable2D
 * @brief Interface for objects that support 2D transformations such as translation, rotation, and scaling.
 *
 * Classes that inherit from Transformable2D must implement the transformation methods, allowing for movement,
 * rotation, and scaling in 2D space.
 */
class Transformable2D
{
public:
    /**
     * @brief Virtual destructor for Transformable2D.
     */
    virtual ~Transformable2D() = default;

    /**
     * @brief Translates the object by a given vector.
     * @param translation The vector by which to translate the object.
     * @return Reference to the transformed object.
     */
    virtual Transformable2D& translate(const Vec2f& translation) = 0;

    /**
     * @brief Rotates the object by a specified angle around its origin.
     * @param angle The rotation angle in degrees.
     * @return Reference to the rotated object.
     */
    virtual Transformable2D& rotate(float angle) = 0;

    /**
     * @brief Rotates the object by a specified angle around a pivot point.
     * @param angle The rotation angle in degrees.
     * @param pivot_point The point around which to rotate the object.
     * @return Reference to the rotated object.
     */
    virtual Transformable2D& rotate(float angle, const Vec2f& pivot_point) = 0;

    /**
     * @brief Scales the object by a specified factor from its origin.
     * @param factor The scaling factor.
     * @return Reference to the scaled object.
     */
    virtual Transformable2D& scale(float factor) = 0;

    /**
     * @brief Scales the object by a specified factor from a scaling point.
     * @param factor The scaling factor.
     * @param scaling_point The point from which to scale the object.
     * @return Reference to the scaled object.
     */
    virtual Transformable2D& scale(float factor, const Vec2f& scaling_point) = 0;
};

} // namespace zth
