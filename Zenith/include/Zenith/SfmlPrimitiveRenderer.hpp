#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.hpp"
#include "DrawCall.hpp"
#include "Geometry.hpp"
#include "Utility.hpp"

namespace zth {

class SfmlPrimitiveRenderer
{
public:
    explicit SfmlPrimitiveRenderer(sf::RenderTarget& target) : _render_target(target) {}
    ~SfmlPrimitiveRenderer() = default;
    ZTH_NO_COPY_NO_MOVE(SfmlPrimitiveRenderer)

    void draw_point(const Vec2f& point, const Color& color);
    void draw_points(std::span<const Vec2f> points, const Color& color);
    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void draw_line(const Line& line, const Color& color);
    void draw_line_strip(std::span<const Vec2f> points, const Color& color);
    void draw_lines(std::span<const Line> lines, const Color& color);
    void draw_closed_lines(std::span<const Vec2f> points, const Color& color);
    void draw_closed_lines(std::span<const Line> lines, const Color& color);

    void draw_rect(const Rect& rect, const Color& color);
    void draw_filled_rect(const Rect& rect, const Color& color);

    // only supports convex polygons
    void draw_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_polygon(std::span<const Line> lines, const Color& color);
    void draw_filled_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_filled_polygon(std::span<const Line> lines, const Color& color);

    void draw_circle(const Circle& circle, const Color& color) const;
    void draw_ellipse(const Ellipse& ellipse, const Color& color) const;
    void draw_filled_circle(const Circle& circle, const Color& color) const;
    void draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const;

private:
    sf::RenderTarget& _render_target;
    DrawCall _draw_call = DrawCall{};

private:
    void plot_point(const Vec2f& point, const Color& color);
    void plot_points(std::span<const Vec2f> points, const Color& color);
    void plot_line(const Vec2f& from, const Vec2f& to, const Color& color);
    void plot_line(const Line& line, const Color& color);
    void plot_line_strip(std::span<const Vec2f> points, const Color& color);
    void plot_line_strip(std::span<const Line> lines, const Color& color);
    void plot_lines(std::span<const Line> lines, const Color& color);
    void plot_closed_lines(std::span<const Vec2f> points, const Color& color);
    void plot_closed_lines(std::span<const Line> lines, const Color& color);

    void plot_rect(const Rect& rect, const Color& color);
    void plot_filled_rect(const Rect& rect, const Color& color);

    void plot_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_polygon(std::span<const Line> lines, const Color& color);
    void plot_filled_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_filled_polygon(std::span<const Line> lines, const Color& color);
};

} // namespace zth
