#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class SfmlPrimitiveRenderer : public PrimitiveRenderer
{
public:
    explicit SfmlPrimitiveRenderer(sf::RenderTarget& target) : PrimitiveRenderer(target) {}
    ~SfmlPrimitiveRenderer() override = default;
    ZTH_NO_COPY_NO_MOVE(SfmlPrimitiveRenderer)

private:
    sf::VertexArray _vertex_array = sf::VertexArray{};

private:
    void draw_point_impl(const Vec2f& point, const Color& color) override;
    void draw_points_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color) override;
    void draw_line_impl(const Line& line, const Color& color) override;
    void draw_line_strip_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_lines_impl(std::span<const Line> lines, const Color& color) override;
    void draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_closed_lines_impl(std::span<const Line> lines, const Color& color) override;

    void draw_rect_impl(const Rect& rect, const Color& color) override;
    void draw_filled_rect_impl(const Rect& rect, const Color& color) override;

    // supports only convex polygons
    void draw_polygon_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_polygon_impl(std::span<const Line> lines, const Color& color) override;
    void draw_filled_polygon_impl(std::span<const Vec2f> points, const Color& color) override;
    void draw_filled_polygon_impl(std::span<const Line> lines, const Color& color) override;

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

    void plot_rect(const Rect& rect, const Color& color);
    void plot_filled_rect(const Rect& rect, const Color& color);

    void plot_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_polygon(std::span<const Line> lines, const Color& color);
    void plot_filled_polygon(std::span<const Vec2f> points, const Color& color);
    void plot_filled_polygon(std::span<const Line> lines, const Color& color);

    void draw_call(sf::PrimitiveType primitive_type);
};

} // namespace zth
