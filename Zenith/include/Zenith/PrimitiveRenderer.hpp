#pragma once

#include <SFML/Graphics.hpp>

#include <span>

#include "Color.hpp"
#include "CustomRenderer.hpp"
#include "Geometry.hpp"
#include "SfmlRenderer.hpp"

namespace zth {

enum class RenderingAlgorithm
{
    Sfml,
    Custom,
};

enum class FillAlgorithm
{
    BoundaryFill,
    FloodFill,
};

class PrimitiveRenderer
{
public:
    RenderingAlgorithm rendering_algorithm = RenderingAlgorithm::Sfml;
    FillAlgorithm fill_algorithm = FillAlgorithm::BoundaryFill;

public:
    explicit PrimitiveRenderer(sf::RenderTarget& target)
        : _render_target(target), _sfml_renderer(target), _custom_renderer(target)
    {}

    PrimitiveRenderer(const PrimitiveRenderer&) = delete;
    PrimitiveRenderer(PrimitiveRenderer&&) = delete;

    ~PrimitiveRenderer() = default;

    auto operator=(const PrimitiveRenderer&) = delete;
    auto operator=(PrimitiveRenderer&&) = delete;

    void draw_point(const Vec2f& point, const Color& color = Color::white);

    void draw_line(const Vec2f& from, const Vec2f& to, const Color& color = Color::white);

    void draw_line(const Line& line, const Color& color = Color::white);

    void draw_lines(std::span<const Vec2f> points, const Color& color = Color::white);

    void draw_lines(std::span<const Line> lines, const Color& color = Color::white);

    void draw_closed_lines(std::span<const Vec2f> points, const Color& color = Color::white);

    void draw_closed_lines(std::span<const Line> lines, const Color& color = Color::white);

    void draw_rect(const Rect& rect, const Color& color = Color::white);

    void draw_filled_rect(const Rect& rect, const Color& outline_color = Color::white,
                          const Color& fill_color = Color::black);

    void draw_polygon(std::span<const Vec2f> points, const Color& color = Color::white);

    void draw_polygon(std::span<const Line> lines, const Color& color = Color::white);

    void draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black);

    void draw_filled_polygon(std::span<const Line> lines, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black);

    void draw_circle(const Circle& circle, const Color& color = Color::white);

    void draw_filled_circle(const Circle& circle, const Color& outline_color = Color::white,
                            const Color& fill_color = Color::black);

    void draw_ellipse(const Ellipse& ellipse, const Color& color = Color::white);

    void draw_filled_ellipse(const Ellipse& ellipse, const Color& outline_color = Color::white,
                             const Color& fill_color = Color::black);

private:
    sf::RenderTarget& _render_target;
    SfmlRenderer _sfml_renderer;
    CustomRenderer _custom_renderer;
};

} // namespace zth
