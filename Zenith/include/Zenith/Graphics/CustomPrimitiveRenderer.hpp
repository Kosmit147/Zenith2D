/**
 * @file CustomPrimitiveRenderer.hpp
 * @brief Defines a custom renderer for drawing various 2D shapes with support for filling algorithms.
 */

#pragma once

#include <SFML/Graphics/Image.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Graphics/VertexArray.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @enum FillAlgorithm
 * @brief Enumerates the available fill algorithms.
 */
enum class FillAlgorithm
{
    BoundaryFill, ///< Uses boundary fill algorithm.
    FloodFill,    ///< Uses flood fill algorithm.
};

/**
 * @class CustomPrimitiveRenderer
 * @brief A custom renderer for drawing 2D primitives with support for different fill algorithms.
 *
 * This class extends the `PrimitiveRenderer` class and provides methods for drawing various 2D shapes
 * like points, lines, triangles, rectangles, circles, and polygons. It also supports filling algorithms 
 * (boundary fill and flood fill) for shapes that can be filled.
 */
class CustomPrimitiveRenderer : public PrimitiveRenderer
{
public:
    FillAlgorithm fill_algorithm = FillAlgorithm::FloodFill; ///< The fill algorithm used for drawing shapes.

public:
    /**
     * @brief Constructor that initializes the custom primitive renderer.
     * @param render_target The target to render shapes on (e.g., window or texture).
     */
    explicit CustomPrimitiveRenderer(sf::RenderTarget& render_target) : PrimitiveRenderer(render_target) {}

    ~CustomPrimitiveRenderer() override = default; ///< Destructor.

    ZTH_NO_COPY_NO_MOVE(CustomPrimitiveRenderer) ///< Disable copy and move operations.

private:
    VertexArray _vertex_array{ PrimitiveType::Points }; ///< Vertex array used for drawing points.

private:
    /**
     * @brief Draws a single point.
     * @param point The position of the point.
     * @param color The color of the point.
     */
    void draw_point_impl(const Vec2f& point, const Color& color) override;

    /**
     * @brief Draws multiple points.
     * @param points A span of points to draw.
     * @param color The color of the points.
     */
    void draw_points_impl(std::span<const Vec2f> points, const Color& color) override;

    /**
     * @brief Draws a line between two points.
     * @param from The starting point of the line.
     * @param to The ending point of the line.
     * @param color The color of the line.
     */
    void draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color) override;

    /**
     * @brief Draws a line.
     * @param line The line to draw.
     * @param color The color of the line.
     */
    void draw_line_impl(const Line& line, const Color& color) override;

    /**
     * @brief Draws a strip of connected lines.
     * @param points A span of points forming the line strip.
     * @param color The color of the line strip.
     */
    void draw_line_strip_impl(std::span<const Vec2f> points, const Color& color) override;

    /**
     * @brief Draws multiple lines.
     * @param lines A span of lines to draw.
     * @param color The color of the lines.
     */
    void draw_lines_impl(std::span<const Line> lines, const Color& color) override;

    /**
     * @brief Draws a closed loop of lines.
     * @param points A span of points forming the closed loop.
     * @param color The color of the closed lines.
     */
    void draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color) override;

    /**
     * @brief Draws a closed loop of lines.
     * @param lines A span of lines forming the closed loop.
     * @param color The color of the closed lines.
     */
    void draw_closed_lines_impl(std::span<const Line> lines, const Color& color) override;

    /**
     * @brief Draws a triangle.
     * @param triangle The triangle to draw.
     * @param color The color of the triangle.
     */
    void draw_triangle_impl(const Triangle& triangle, const Color& color) override;

    /**
     * @brief Draws a filled triangle.
     * @param triangle The triangle to fill.
     * @param color The color of the filled triangle.
     */
    void draw_filled_triangle_impl(const Triangle& triangle, const Color& color) override;

    /**
     * @brief Draws a rectangle.
     * @param rect The rectangle to draw.
     * @param color The color of the rectangle.
     */
    void draw_rect_impl(const Rect& rect, const Color& color) override;

    /**
     * @brief Draws a filled rectangle.
     * @param rect The rectangle to fill.
     * @param color The color of the filled rectangle.
     */
    void draw_filled_rect_impl(const Rect& rect, const Color& color) override;

    /**
     * @brief Draws a convex polygon.
     * @param points A span of points defining the convex polygon.
     * @param color The color of the polygon.
     */
    void draw_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) override;

    /**
     * @brief Draws a convex polygon.
     * @param lines A span of lines defining the convex polygon.
     * @param color The color of the polygon.
     */
    void draw_convex_polygon_impl(std::span<const Line> lines, const Color& color) override;

    /**
     * @brief Draws a filled convex polygon.
     * @param points A span of points defining the convex polygon.
     * @param color The color of the filled polygon.
     */
    void draw_filled_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) override;

    /**
     * @brief Draws a filled convex polygon.
     * @param lines A span of lines defining the convex polygon.
     * @param color The color of the filled polygon.
     */
    void draw_filled_convex_polygon_impl(std::span<const Line> lines, const Color& color) override;

    /**
     * @brief Draws a circle.
     * @param circle The circle to draw.
     * @param color The color of the circle.
     */
    void draw_circle_impl(const Circle& circle, const Color& color) override;

    /**
     * @brief Draws an ellipse.
     * @param ellipse The ellipse to draw.
     * @param color The color of the ellipse.
     */
    void draw_ellipse_impl(const Ellipse& ellipse, const Color& color) override;

    /**
     * @brief Draws a filled circle.
     * @param circle The circle to fill.
     * @param color The color of the filled circle.
     */
    void draw_filled_circle_impl(const Circle& circle, const Color& color) override;

    /**
     * @brief Draws a filled ellipse.
     * @param ellipse The ellipse to fill.
     * @param color The color of the filled ellipse.
     */
    void draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color) override;

    // Helper methods for plotting shapes.
    void plot_point(const Vec2f& point, const Color& color);
    void plot_points(std::span<const Vec2f> points, const Color& color);
    void plot_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void plot_line(const Line& line, const Color& color);
    void plot_line_strip(std::span<const Vec2f> points, const Color& color);
    void plot_lines(std::span<const Line> lines, const Color& color);
    void plot_closed_lines(std::span<const Vec2f> points, const Color& color);
    void plot_closed_lines(std::span<const Line> lines, const Color& color);

    void plot_triangle(const Triangle& triangle, const Color& color);

    void plot_rect(const Rect& rect, const Color& color);

    void plot_convex_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_convex_polygon(std::span<const Line> lines, const Color& color);

    void plot_circle(const Circle& circle, const Color& color);
    void plot_ellipse(const Ellipse& ellipse, const Color& color);

    /**
     * @brief Draws a line on an image.
     * @param image The image to draw on.
     * @param from The starting point of the line.
     * @param to The ending point of the line.
     * @param color The color of the line.
     */
    static void draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to, const Color& color);

    /**
     * @brief Draws a line on an image.
     * @param image The image to draw on.
     * @param line The line to draw.
     * @param color The color of the line.
     */
    static void draw_line_on_image(sf::Image& image, const Line& line, const Color& color);

    /**
     * @brief Draws a line strip on an image.
     * @param image The image to draw on.
     * @param points The points forming the line strip.
     * @param color The color of the line strip.
     */
    static void draw_line_strip_on_image(sf::Image& image, std::span<const Vec2f> points, const Color& color);

    /**
     * @brief Draws multiple lines on an image.
     * @param image The image to draw on.
     * @param lines The lines to draw.
     * @param color The color of the lines.
     */
    static void draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color);

    /**
     * @brief Draws a triangle on an image.
     * @param image The image to draw on.
     * @param triangle The triangle to draw.
     * @param color The color of the triangle.
     */
    static void draw_triangle_on_image(sf::Image& image, const Triangle& triangle, const Color& color);

    /**
     * @brief Draws a rectangle on an image.
     * @param image The image to draw on.
     * @param rect The rectangle to draw.
     * @param color The color of the rectangle.
     */
    static void draw_rect_on_image(sf::Image& image, const Rect& rect, const Color& color);

    /**
     * @brief Draws a circle on an image.
     * @param image The image to draw on.
     * @param circle The circle to draw.
     * @param color The color of the circle.
     */
    static void draw_circle_on_image(sf::Image& image, const Circle& circle, const Color& color);

    /**
     * @brief Draws an ellipse on an image.
     * @param image The image to draw on.
     * @param ellipse The ellipse to draw.
     * @param color The color of the ellipse.
     */
    static void draw_ellipse_on_image(sf::Image& image, const Ellipse& ellipse, const Color& color);

    // Methods for filling shapes on an image.
    static Vec2u get_triangle_seed(const Triangle& triangle);
    static Vec2u get_rect_seed(const Rect& rect);
    static Vec2u get_convex_polygon_seed(std::span<const Vec2f> points);
    static Vec2u get_convex_polygon_seed(std::span<const Line> lines);
    static Vec2u get_circle_seed(const Circle& circle);
    static Vec2u get_ellipse_seed(const Ellipse& ellipse);

    /**
     * @brief Performs boundary fill on an image.
     * @param image The image to fill.
     * @param seed The starting point of the fill.
     * @param border_color The border color to stop the fill.
     * @param fill_color The color to fill the area.
     */
    static void boundary_fill_on_image(sf::Image& image, const Vec2u& seed, const Color& border_color,
                                       const Color& fill_color);

    /**
     * @brief Performs flood fill on an image.
     * @param image The image to fill.
     * @param seed The starting point of the fill.
     * @param fill_color The color to fill the area.
     * @param background_color The background color to stop the fill.
     */
    static void flood_fill_on_image(sf::Image& image, const Vec2u& seed, const Color& fill_color,
                                    const Color& background_color);

    /**
     * @brief Fills a shape on the image using the chosen fill algorithm.
     * @param image The image to fill.
     * @param seed The starting point of the fill.
     * @param border_color The border color to stop the fill.
     * @param fill_color The color to fill the shape.
     * @param background_color The background color to stop the fill.
     */
    void fill_on_image(sf::Image& image, const Vec2u& seed, const Color& border_color, const Color& fill_color,
                       const Color& background_color) const;

    /**
     * @brief Draws an image to the render target.
     * @param image The image to draw.
     */
    void draw_image(const sf::Image& image) const;

    /**
     * @brief Gets a temporary image for drawing.
     * @param target_size The size of the image.
     * @return A reference to the temporary image.
     */
    static sf::Image& get_tmp_image(const sf::Vector2u& target_size);

    /**
     * @brief Executes the drawing call.
     */
    void draw_call();
};

} // namespace zth
