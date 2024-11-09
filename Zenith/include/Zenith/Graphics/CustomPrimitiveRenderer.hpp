#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

enum class FillAlgorithm
{
    BoundaryFill,
    FloodFill,
};

// TODO: Refactor this class
class CustomPrimitiveRenderer : public PrimitiveRenderer
{
public:
    FillAlgorithm fill_algorithm = FillAlgorithm::FloodFill;

public:
    explicit CustomPrimitiveRenderer(sf::RenderTarget& render_target) : PrimitiveRenderer(render_target) {}
    ~CustomPrimitiveRenderer() override = default;
    ZTH_NO_COPY_NO_MOVE(CustomPrimitiveRenderer)

private:
    sf::VertexArray _vertex_array{ sf::Points, 0 }; // we're only ever drawing points in custom renderer

private:
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

    static void draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to, const Color& color);
    static void draw_line_on_image(sf::Image& image, const Line& line, const Color& color);
    static void draw_line_strip_on_image(sf::Image& image, std::span<const Vec2f> points, const Color& color);
    static void draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color);
    static void draw_triangle_on_image(sf::Image& image, const Triangle& triangle, const Color& color);
    static void draw_rect_on_image(sf::Image& image, const Rect& rect, const Color& color);
    static void draw_circle_on_image(sf::Image& image, const Circle& circle, const Color& color);
    static void draw_ellipse_on_image(sf::Image& image, const Ellipse& ellipse, const Color& color);

    static void boundary_fill(sf::Image& image, const Vec2u& seed, const Color& border_color, const Color& fill_color);
    static void flood_fill(sf::Image& image, const Vec2u& seed, const Color& fill_color, const Color& background_color);

    static sf::Image& get_tmp_image(const sf::Vector2u& target_size);

    void draw_call();
};

} // namespace zth
