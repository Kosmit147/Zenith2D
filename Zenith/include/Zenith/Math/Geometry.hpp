/**
 * @file Geometry.hpp
 * @brief Defines geometric shapes and operations on them.
 * 
 * This file contains structures and functions that represent and manipulate common geometric shapes,
 * such as lines, triangles, rectangles, circles, and ellipses. Each shape comes with transformations
 * like translation, rotation, scaling, and methods for checking intersections and bounds.
 */

#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <array>
#include <span>

#include "Zenith/Math/Vec2.hpp"

namespace zth {

/**
 * @brief Represents a 2D line defined by two points.
 */
struct Line
{
    Vec2f from; ///< Starting point of the line.
    Vec2f to;   ///< Ending point of the line.

    /**
     * @brief Translates the line by a given vector.
     * 
     * @param translation The translation vector.
     * @return A new `Line` object with the translated points.
     */
    constexpr Line translated(const Vec2f& translation) const;

    /**
     * @brief Translates the line by a given vector in place.
     * 
     * @param translation The translation vector.
     * @return The modified `Line` object.
     */
    constexpr Line& translate(const Vec2f& translation);

    /**
     * @brief Rotates the line by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @return A new `Line` object with the rotated points.
     */
    constexpr Line rotated(float angle) const;

    /**
     * @brief Rotates the line by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @return The modified `Line` object.
     */
    constexpr Line& rotate(float angle);

    /**
     * @brief Rotates the line around a pivot point by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the line.
     * @return A new `Line` object with the rotated points.
     */
    constexpr Line rotated(float angle, const Vec2f& pivot_point) const;

    /**
     * @brief Rotates the line around a pivot point by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the line.
     * @return The modified `Line` object.
     */
    constexpr Line& rotate(float angle, const Vec2f& pivot_point);

    /**
     * @brief Scales the line by a given factor.
     * 
     * @param factor The scale factor.
     * @return A new `Line` object with the scaled points.
     */
    constexpr Line scaled(float factor) const;

    /**
     * @brief Scales the line by a given factor in place.
     * 
     * @param factor The scale factor.
     * @return The modified `Line` object.
     */
    constexpr Line& scale(float factor);

    /**
     * @brief Scales the line by a given factor around a scaling point.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the line.
     * @return A new `Line` object with the scaled points.
     */
    constexpr Line scaled(float factor, const Vec2f& scaling_point) const;

    /**
     * @brief Scales the line by a given factor around a scaling point in place.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the line.
     * @return The modified `Line` object.
     */
    constexpr Line& scale(float factor, const Vec2f& scaling_point);

    /**
     * @brief Checks if this line intersects another line.
     * 
     * @param other The other line to check intersection with.
     * @return `true` if the lines intersect, otherwise `false`.
     */
    constexpr bool intersects(const Line& other) const;
};

/**
 * @brief Represents a 2D triangle defined by three points.
 */
struct Triangle
{
    std::array<Vec2f, 3> points; ///< The three points that define the triangle.

    /**
     * @brief Translates the triangle by a given vector.
     * 
     * @param translation The translation vector.
     * @return A new `Triangle` object with the translated points.
     */
    constexpr Triangle translated(const Vec2f& translation) const;

    /**
     * @brief Translates the triangle by a given vector in place.
     * 
     * @param translation The translation vector.
     * @return The modified `Triangle` object.
     */
    constexpr Triangle& translate(const Vec2f& translation);

    /**
     * @brief Rotates the triangle by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @return A new `Triangle` object with the rotated points.
     */
    constexpr Triangle rotated(float angle) const;

    /**
     * @brief Rotates the triangle by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @return The modified `Triangle` object.
     */
    constexpr Triangle& rotate(float angle);

    /**
     * @brief Rotates the triangle around a pivot point by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the triangle.
     * @return A new `Triangle` object with the rotated points.
     */
    constexpr Triangle rotated(float angle, const Vec2f& pivot_point) const;

    /**
     * @brief Rotates the triangle around a pivot point by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the triangle.
     * @return The modified `Triangle` object.
     */
    constexpr Triangle& rotate(float angle, const Vec2f& pivot_point);

    /**
     * @brief Scales the triangle by a given factor.
     * 
     * @param factor The scale factor.
     * @return A new `Triangle` object with the scaled points.
     */
    constexpr Triangle scaled(float factor) const;

    /**
     * @brief Scales the triangle by a given factor in place.
     * 
     * @param factor The scale factor.
     * @return The modified `Triangle` object.
     */
    constexpr Triangle& scale(float factor);

    /**
     * @brief Scales the triangle by a given factor around a scaling point.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the triangle.
     * @return A new `Triangle` object with the scaled points.
     */
    constexpr Triangle scaled(float factor, const Vec2f& scaling_point) const;

    /**
     * @brief Scales the triangle by a given factor around a scaling point in place.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the triangle.
     * @return The modified `Triangle` object.
     */
    constexpr Triangle& scale(float factor, const Vec2f& scaling_point);
};

/**
 * @brief Represents a 2D rectangle defined by a position and size.
 */
struct Rect
{
    Vec2f position; ///< Position of the rectangle (top-left corner).
    Vec2f size;     ///< Size of the rectangle (width and height).

    /**
     * @brief Converts an SFML rectangle to a `Rect`.
     * 
     * @param rect The SFML rectangle to convert.
     * @return A `Rect` object representing the SFML rectangle.
     */
    static Rect from_sf_rect(const sf::FloatRect& rect);

    /**
     * @brief Translates the rectangle by a given vector.
     * 
     * @param translation The translation vector.
     * @return A new `Rect` object with the translated position.
     */
    constexpr Rect translated(const Vec2f& translation) const;

    /**
     * @brief Translates the rectangle by a given vector in place.
     * 
     * @param translation The translation vector.
     * @return The modified `Rect` object.
     */
    constexpr Rect& translate(const Vec2f& translation);

    /**
     * @brief Scales the rectangle by a given factor.
     * 
     * @param factor The scale factor.
     * @return A new `Rect` object with the scaled size.
     */
    constexpr Rect scaled(float factor) const;

    /**
     * @brief Scales the rectangle by a given factor in place.
     * 
     * @param factor The scale factor.
     * @return The modified `Rect` object.
     */
    constexpr Rect& scale(float factor);

    /**
     * @brief Scales the rectangle by a given factor around a scaling point.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the rectangle.
     * @return A new `Rect` object with the scaled size.
     */
    constexpr Rect scaled(float factor, const Vec2f& scaling_point) const;

    /**
     * @brief Scales the rectangle by a given factor around a scaling point in place.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the rectangle.
     * @return The modified `Rect` object.
     */
    constexpr Rect& scale(float factor, const Vec2f& scaling_point);

    /**
     * @brief Gets the four corner points of the rectangle.
     * 
     * @return An array of four points representing the corners of the rectangle.
     */
    constexpr std::array<Vec2f, 4> points() const;

    /**
     * @brief Gets the center of the rectangle.
     * 
     * @return The center point of the rectangle.
     */
    constexpr Vec2f center() const;

    /**
     * @brief Checks if a point is inside the rectangle.
     * 
     * @param point The point to check.
     * @return `true` if the point is inside the rectangle, otherwise `false`.
     */
    constexpr bool contains(const Vec2f& point) const;
};

/**
 * @brief Represents a 2D rectangle with integer position and size.
 */
struct IntRect
{
    Vec2i position; ///< Position of the rectangle (top-left corner).
    Vec2i size;     ///< Size of the rectangle (width and height).

    /**
     * @brief Converts the `IntRect` to an SFML rectangle.
     * 
     * @return The corresponding SFML rectangle.
     */
    explicit operator sf::Rect<i32>() const;
};

/**
 * @brief Represents a 2D rectangle with unsigned integer position and size.
 */
struct UIntRect
{
    Vec2u position; ///< Position of the rectangle (top-left corner).
    Vec2u size;     ///< Size of the rectangle (width and height).

    /**
     * @brief Converts the `UIntRect` to an SFML rectangle.
     * 
     * @return The corresponding SFML rectangle.
     */
    explicit operator sf::Rect<u32>() const;
};

/**
 * @brief Represents a 2D circle defined by a center point and a radius.
 */
struct Circle
{
    Vec2f center; ///< Center of the circle.
    float radius; ///< Radius of the circle.

    /**
     * @brief Translates the circle by a given vector.
     * 
     * @param translation The translation vector.
     * @return A new `Circle` object with the translated center.
     */
    constexpr Circle translated(const Vec2f& translation) const;

    /**
     * @brief Translates the circle by a given vector in place.
     * 
     * @param translation The translation vector.
     * @return The modified `Circle` object.
     */
    constexpr Circle& translate(const Vec2f& translation);

    /**
     * @brief Rotates the circle by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @return A new `Circle` object with the rotated center.
     */
    constexpr Circle rotated(float angle) const;

    /**
     * @brief Rotates the circle by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @return The modified `Circle` object.
     */
    constexpr Circle& rotate(float angle);

    /**
     * @brief Rotates the circle around a pivot point by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the circle.
     * @return A new `Circle` object with the rotated center.
     */
    constexpr Circle rotated(float angle, const Vec2f& pivot_point) const;

    /**
     * @brief Rotates the circle around a pivot point by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the circle.
     * @return The modified `Circle` object.
     */
    constexpr Circle& rotate(float angle, const Vec2f& pivot_point);

    /**
     * @brief Scales the circle by a given factor.
     * 
     * @param factor The scale factor.
     * @return A new `Circle` object with the scaled radius.
     */
    constexpr Circle scaled(float factor) const;

    /**
     * @brief Scales the circle by a given factor in place.
     * 
     * @param factor The scale factor.
     * @return The modified `Circle` object.
     */
    constexpr Circle& scale(float factor);

    /**
     * @brief Scales the circle by a given factor around a scaling point.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the circle.
     * @return A new `Circle` object with the scaled radius.
     */
    constexpr Circle scaled(float factor, const Vec2f& scaling_point) const;

    /**
     * @brief Scales the circle by a given factor around a scaling point in place.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the circle.
     * @return The modified `Circle` object.
     */
    constexpr Circle& scale(float factor, const Vec2f& scaling_point);

    /**
     * @brief Gets the bounding rectangle of the circle.
     * 
     * @return A `Rect` object representing the bounding box of the circle.
     */
    constexpr Rect bounds() const;
};

/**
 * @brief Represents a 2D ellipse defined by a center point and radii along the X and Y axes.
 */
struct Ellipse
{
    Vec2f center; ///< Center of the ellipse.
    Vec2f radius; ///< Radii of the ellipse (horizontal and vertical).

    /**
     * @brief Translates the ellipse by a given vector.
     * 
     * @param translation The translation vector.
     * @return A new `Ellipse` object with the translated center.
     */
    constexpr Ellipse translated(const Vec2f& translation) const;

    /**
     * @brief Translates the ellipse by a given vector in place.
     * 
     * @param translation The translation vector.
     * @return The modified `Ellipse` object.
     */
    constexpr Ellipse& translate(const Vec2f& translation);

    /**
     * @brief Rotates the ellipse by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @return A new `Ellipse` object with the rotated center.
     */
    constexpr Ellipse rotated(float angle) const;

    /**
     * @brief Rotates the ellipse by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @return The modified `Ellipse` object.
     */
    constexpr Ellipse& rotate(float angle);

    /**
     * @brief Rotates the ellipse around a pivot point by a given angle.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the ellipse.
     * @return A new `Ellipse` object with the rotated center.
     */
    constexpr Ellipse rotated(float angle, const Vec2f& pivot_point) const;

    /**
     * @brief Rotates the ellipse around a pivot point by a given angle in place.
     * 
     * @param angle The angle of rotation in degrees.
     * @param pivot_point The point around which to rotate the ellipse.
     * @return The modified `Ellipse` object.
     */
    constexpr Ellipse& rotate(float angle, const Vec2f& pivot_point);

    /**
     * @brief Scales the ellipse by a given factor.
     * 
     * @param factor The scale factor.
     * @return A new `Ellipse` object with the scaled radii.
     */
    constexpr Ellipse scaled(float factor) const;

    /**
     * @brief Scales the ellipse by a given factor in place.
     * 
     * @param factor The scale factor.
     * @return The modified `Ellipse` object.
     */
    constexpr Ellipse& scale(float factor);

    /**
     * @brief Scales the ellipse by a given factor around a scaling point.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the ellipse.
     * @return A new `Ellipse` object with the scaled radii.
     */
    constexpr Ellipse scaled(float factor, const Vec2f& scaling_point) const;

    /**
     * @brief Scales the ellipse by a given factor around a scaling point in place.
     * 
     * @param factor The scale factor.
     * @param scaling_point The point around which to scale the ellipse.
     * @return The modified `Ellipse` object.
     */
    constexpr Ellipse& scale(float factor, const Vec2f& scaling_point);

    /**
     * @brief Gets the bounding rectangle of the ellipse.
     * 
     * @return A `Rect` object representing the bounding box of the ellipse.
     */
    constexpr Rect bounds() const;
};

/**
 * @brief Checks if two lines intersect.
 * 
 * @param first_line The first line.
 * @param second_line The second line.
 * @return `true` if the lines intersect, otherwise `false`.
 */
constexpr bool lines_intersect(const Line& first_line, const Line& second_line);

/**
 * @brief Checks if the points form a valid polygon.
 * 
 * @param points The points to check.
 * @return `true` if the points form a valid polygon, otherwise `false`.
 */
bool points_form_a_valid_polygon(std::span<const Vec2f> points);

/**
 * @brief Checks if the lines form a valid polygon.
 * 
 * @param lines The lines to check.
 * @return `true` if the lines form a valid polygon, otherwise `false`.
 */
bool lines_form_a_valid_polygon(std::span<const Line> lines);

} // namespace zth

#include "Geometry.inl"
