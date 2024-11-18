/**
 * @file SfmlPrimitiveRenderer.hpp
 * @brief Defines the `SfmlPrimitiveRenderer` class, which provides implementation for rendering various primitives using SFML.
 */

#pragma once

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Graphics/VertexArray.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @class SfmlPrimitiveRenderer
 * @brief Renders primitives using SFML.
 *
 * `SfmlPrimitiveRenderer` is a subclass of `PrimitiveRenderer` that implements the methods for drawing various types of primitives 
 * (points, lines, polygons, etc.) using the SFML graphics system. This class is responsible for creating and managing 
 * SFML's `sf::VertexArray` to render shapes efficiently.
 */
class SfmlPrimitiveRenderer : public PrimitiveRenderer
{
public:
    /**
     * @brief Constructs a `SfmlPrimitiveRenderer` that draws primitives on the specified render target.
     * @param render_target The target to render to (e.g., window or texture).
     */
    explicit SfmlPrimitiveRenderer(sf::RenderTarget& render_target) : PrimitiveRenderer(render_target) {}

    /**
     * @brief Destructor for `SfmlPrimitiveRenderer`.
     */
    ~SfmlPrimitiveRenderer() override = default;

    /**
     * @brief Deleted copy constructor and move constructor.
     */
    ZTH_NO_COPY_NO_MOVE(SfmlPrimitiveRenderer)

private:
    VertexArray _vertex_array; ///< The vertex array used for drawing primitives.

    // Implementation methods for drawing different types of primitives.
    void draw_point_impl(const Vec2f& point, const Color& color) override;
    void draw_points_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color) override;
    void draw_line_impl(const Line& line, const Color& color) override;
    void draw_line_strip_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_lines_impl(std::span<const Line> lines, const Color& color) override;
    void draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_closed_lines_impl(std::span<const Line> lines, const Color& color) override;

    void draw_triangle_impl(const Triangle& triangle, const Color& color) override;
    void draw_filled_triangle_impl(const Triangle& triangle, const Color& color) override;

    void draw_rect_impl(const Rect& rect, const Color& color) override;
    void draw_filled_rect_impl(const Rect& rect, const Color& color) override;

    void draw_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_convex_polygon_impl(std::span<const Line> lines, const Color& color) override;
    void draw_filled_convex_polygon_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_filled_convex_polygon_impl(std::span<const Line> lines, const Color& color) override;

    void draw_circle_impl(const Circle& circle, const Color& color) override;
    void draw_ellipse_impl(const Ellipse& ellipse, const Color& color) override;
    void draw_filled_circle_impl(const Circle& circle, const Color& color) override;
    void draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color) override;

    // Plotting methods for individual primitives (used internally).
    void plot_point(const Vec2f& point, const Color& color);
    void plot_points(std::span<const Vec2f> points, const Color& color);
    void plot_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void plot_line(const Line& line, const Color& color);
    void plot_line_strip(std::span<const Vec2f> points, const Color& color);
    void plot_lines(std::span<const Line> lines, const Color& color);
    void plot_closed_lines(std::span<const Vec2f> points, const Color& color);
    void plot_closed_lines(std::span<const Line> lines, const Color& color);

    void plot_triangle(const Triangle& triangle, const Color& color);
    void plot_filled_triangle(const Triangle& triangle, const Color& color);

    void plot_rect(const Rect& rect, const Color& color);
    void plot_filled_rect(const Rect& rect, const Color& color);

    void plot_convex_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_convex_polygon(std::span<const Line> lines, const Color& color);
    void plot_filled_convex_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_filled_convex_polygon(std::span<const Line> lines, const Color& color);

    /**
     * @brief Performs the actual drawing of the primitive after it's been prepared.
     * @param primitive_type The type of primitive to be drawn (point, line, triangle, etc.).
     */
    void draw_call(PrimitiveType primitive_type);
};

} // namespace zth
