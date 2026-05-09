/**
 * @file PrimitiveRenderer.hpp
 * @brief Defines the `PrimitiveRenderer` class for rendering 2D shapes and primitives.
 */

#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @class PrimitiveRenderer
 * @brief A class responsible for rendering basic geometric primitives.
 *
 * This class provides methods to draw basic shapes (points, lines, rectangles, circles, etc.)
 * to a given SFML render target. It also provides specific methods for filled and unfilled
 * shapes.
 *
 * @note The implementation for drawing the primitives should be provided in a derived class.
 */
class PrimitiveRenderer
{
public:
    /**
     * @brief Constructs a PrimitiveRenderer with a specific SFML render target.
     * @param render_target The target render window or texture to draw on.
     */
    explicit PrimitiveRenderer(sf::RenderTarget& render_target) : _render_target(render_target) {}

    virtual ~PrimitiveRenderer() = default;

    // Delete copy and move constructors and assignment operators
    ZTH_NO_COPY_NO_MOVE(PrimitiveRenderer)

    /**
     * @brief Draws a single point on the render target.
     * @param point The position of the point to be drawn.
     * @param color The color of the point.
     */
    void draw_point(const Vec2f& point, const Color& color);

    /**
     * @brief Draws multiple points on the render target.
     * @param points A span of points to be drawn.
     * @param color The color of the points.
     */
    void draw_points(std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws a line between two points on the render target.
     * @param from The starting point of the line.
     * @param to The ending point of the line.
     * @param color The color of the line.
     */
    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);

    /**
     * @brief Draws a line based on a Line object.
     * @param line The line to be drawn.
     * @param color The color of the line.
     */
    void draw_line(const Line& line, const Color& color);

    /**
     * @brief Draws a strip of connected lines from a series of points.
     * @param points A span of points to form the line strip.
     * @param color The color of the lines.
     */
    void draw_line_strip(std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws multiple lines based on a series of Line objects.
     * @param lines A span of lines to be drawn.
     * @param color The color of the lines.
     */
    void draw_lines(std::span<const Line> lines, const Color& color);

    /**
     * @brief Draws a closed shape formed by connecting a series of points.
     * @param points A span of points that form a closed shape.
     * @param color The color of the closed lines.
     */
    void draw_closed_lines(std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws a closed shape formed by connecting a series of Line objects.
     * @param lines A span of lines that form a closed shape.
     * @param color The color of the closed lines.
     */
    void draw_closed_lines(std::span<const Line> lines, const Color& color);

    /**
     * @brief Draws a triangle.
     * @param triangle The triangle to be drawn.
     * @param color The color of the triangle.
     */
    void draw_triangle(const Triangle& triangle, const Color& color);

    /**
     * @brief Draws a filled triangle.
     * @param triangle The triangle to be filled and drawn.
     * @param color The color of the filled triangle.
     */
    void draw_filled_triangle(const Triangle& triangle, const Color& color);

    /**
     * @brief Draws a rectangle.
     * @param rect The rectangle to be drawn.
     * @param color The color of the rectangle.
     */
    void draw_rect(const Rect& rect, const Color& color);

    /**
     * @brief Draws a filled rectangle.
     * @param rect The rectangle to be filled and drawn.
     * @param color The color of the filled rectangle.
     */
    void draw_filled_rect(const Rect& rect, const Color& color);

    /**
     * @brief Draws a convex polygon.
     * @param points A span of points forming the convex polygon.
     * @param color The color of the polygon.
     */
    void draw_convex_polygon(std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws a convex polygon.
     * @param lines A span of lines forming the convex polygon.
     * @param color The color of the polygon.
     */
    void draw_convex_polygon(std::span<const Line> lines, const Color& color);

    /**
     * @brief Draws a filled convex polygon.
     * @param points A span of points forming the convex polygon.
     * @param color The color of the filled polygon.
     */
    void draw_filled_convex_polygon(std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws a filled convex polygon.
     * @param lines A span of lines forming the convex polygon.
     * @param color The color of the filled polygon.
     */
    void draw_filled_convex_polygon(std::span<const Line> lines, const Color& color);

    /**
     * @brief Draws a circle.
     * @param circle The circle to be drawn.
     * @param color The color of the circle.
     */
    void draw_circle(const Circle& circle, const Color& color);

    /**
     * @brief Draws an ellipse.
     * @param ellipse The ellipse to be drawn.
     * @param color The color of the ellipse.
     */
    void draw_ellipse(const Ellipse& ellipse, const Color& color);

    /**
     * @brief Draws a filled circle.
     * @param circle The circle to be filled and drawn.
     * @param color The color of the filled circle.
     */
    void draw_filled_circle(const Circle& circle, const Color& color);

    /**
     * @brief Draws a filled ellipse.
     * @param ellipse The ellipse to be filled and drawn.
     * @param color The color of the filled ellipse.
     */
    void draw_filled_ellipse(const Ellipse& ellipse, const Color& color);

protected:
    sf::RenderTarget& _render_target; ///< The render target for drawing shapes.

private:
    // Private methods to implement drawing logic for individual shapes.
    virtual void draw_point_impl(const Vec2f& point, const Color& color) = 0;
    virtual void draw_points_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color) = 0;
    virtual void draw_line_impl(const Line& line, const Color& color) = 0;
    virtual void draw_line_strip_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_lines_impl(std::span<const Line> lines, const Color& color) = 0;
    virtual void draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_closed_lines_impl(std::span<const Line> lines, const Color& color) = 0;

    virtual void draw_triangle_impl(const Triangle& triangle, const Color& color) = 0;
    virtual void draw_filled_triangle_impl(const Triangle& triangle, const Color& color) = 0;

    virtual void draw_rect_impl(const Rect& rect, const Color& color) = 0;
    virtual void draw_filled_rect_impl(const Rect& rect, const Color& color) = 0;

    virtual void draw_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_convex_polygon_impl(std::span<const Line> lines, const Color& color) = 0;
    virtual void draw_filled_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) = 0;
    virtual void draw_filled_convex_polygon_impl(std::span<const Line> lines, const Color& color) = 0;

    virtual void draw_circle_impl(const Circle& circle, const Color& color) = 0;
    virtual void draw_ellipse_impl(const Ellipse& ellipse, const Color& color) = 0;
    virtual void draw_filled_circle_impl(const Circle& circle, const Color& color) = 0;
    virtual void draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color) = 0;
};

} // namespace zth
