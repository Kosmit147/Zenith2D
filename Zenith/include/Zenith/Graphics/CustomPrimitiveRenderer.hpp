#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
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
class CustomPrimitiveRenderer
{
public:
    FillAlgorithm fill_algorithm = FillAlgorithm::FloodFill;

public:
    explicit CustomPrimitiveRenderer(sf::RenderTarget& target) : _render_target(target) {}
    ~CustomPrimitiveRenderer() = default;
    ZTH_NO_COPY_NO_MOVE(CustomPrimitiveRenderer)

    void draw_point(const Vec2f& point, const Color& color);
    void draw_points(std::span<const Vec2f> points, const Color& color);
    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void draw_line(const Line& line, const Color& color);
    void draw_line_strip(std::span<const Vec2f> points, const Color& color);
    void draw_lines(std::span<const Line> lines, const Color& color);
    void draw_closed_lines(std::span<const Vec2f> points, const Color& color);
    void draw_closed_lines(std::span<const Line> lines, const Color& color);

    void draw_rect(const Rect& rect, const Color& color);
    void draw_filled_rect(const Rect& rect, const Color& color) const;

    void draw_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_polygon(std::span<const Line> lines, const Color& color);
    void draw_filled_polygon(std::span<const Vec2f> points, const Color& color) const;
    void draw_filled_polygon(std::span<const Line> lines, const Color& color) const;

    void draw_circle(const Circle& circle, const Color& color);
    void draw_ellipse(const Ellipse& ellipse, const Color& color);
    void draw_filled_circle(const Circle& circle, const Color& color) const;
    void draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const;

private:
    sf::RenderTarget& _render_target;
    sf::VertexArray _vertex_array =
        sf::VertexArray{ sf::Points, 0 }; // we're only ever drawing points in custom renderer

private:
    void plot_point(const Vec2f& point, const Color& color);
    void plot_points(std::span<const Vec2f> points, const Color& color);
    void plot_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void plot_line(const Line& line, const Color& color);
    void plot_line_strip(std::span<const Vec2f> points, const Color& color);
    void plot_lines(std::span<const Line> lines, const Color& color);
    void plot_closed_lines(std::span<const Vec2f> points, const Color& color);
    void plot_closed_lines(std::span<const Line> lines, const Color& color);

    void plot_rect(const Rect& rect, const Color& color);

    void plot_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_polygon(std::span<const Line> lines, const Color& color);

    void plot_circle(const Circle& circle, const Color& color);
    void plot_ellipse(const Ellipse& ellipse, const Color& color);

    static void draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to, const Color& color);
    static void draw_line_on_image(sf::Image& image, const Line& line, const Color& color);
    static void draw_line_strip_on_image(sf::Image& image, std::span<const Vec2f> points, const Color& color);
    static void draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color);
    static void draw_rect_on_image(sf::Image& image, const Rect& rect, const Color& color);
    static void draw_circle_on_image(sf::Image& image, const Circle& circle, const Color& color);
    static void draw_ellipse_on_image(sf::Image& image, const Ellipse& ellipse, const Color& color);

    static void boundary_fill(sf::Image& image, const Vec2u& seed, const Color& border_color, const Color& fill_color);
    static void flood_fill(sf::Image& image, const Vec2u& seed, const Color& fill_color, const Color& background_color);

    static sf::Image& get_tmp_image(sf::Vector2u target_size);

    void draw();
};

} // namespace zth
