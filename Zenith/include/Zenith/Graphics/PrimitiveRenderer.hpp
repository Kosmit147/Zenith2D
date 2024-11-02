#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/CustomPrimitiveRenderer.hpp"
#include "Zenith/Graphics/SfmlPrimitiveRenderer.hpp"
#include "Zenith/Math/Geometry.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

enum class RenderingAlgorithm
{
    Sfml,
    Custom,
};

// PrimitiveRenderer should handle whether the parameters passed to it to draw are correct
class PrimitiveRenderer
{
public:
    explicit PrimitiveRenderer(sf::RenderTarget& target);
    ~PrimitiveRenderer() = default;
    ZTH_NO_COPY_NO_MOVE(PrimitiveRenderer)

    auto rendering_algorithm() const { return _rendering_algorithm; }
    auto fill_algorithm() const { return _custom_renderer.fill_algorithm; }

    void set_rendering_algorithm(RenderingAlgorithm alg) { _rendering_algorithm = alg; }
    void set_fill_algorithm(FillAlgorithm alg) { _custom_renderer.fill_algorithm = alg; }

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

    void draw_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_polygon(std::span<const Line> lines, const Color& color);
    void draw_filled_polygon(std::span<const Vec2f> points, const Color& color);
    void draw_filled_polygon(std::span<const Line> lines, const Color& color);

    void draw_circle(const Circle& circle, const Color& color);
    void draw_ellipse(const Ellipse& ellipse, const Color& color);
    void draw_filled_circle(const Circle& circle, const Color& color) const;
    void draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const;

private:
    RenderingAlgorithm _rendering_algorithm = RenderingAlgorithm::Sfml;

    sf::RenderTarget& _render_target;
    SfmlPrimitiveRenderer _sfml_renderer;
    CustomPrimitiveRenderer _custom_renderer;
};

} // namespace zth
