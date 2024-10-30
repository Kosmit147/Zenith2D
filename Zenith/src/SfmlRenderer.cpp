#include "SfmlRenderer.hpp"

#include "EllipseShape.hpp"
#include "Typedefs.hpp"

namespace zth {

void SfmlRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_line(from, to, color);
    _draw_call.execute(_target);
}

void SfmlRenderer::draw_line(const Line& line, const Color& color)
{
    plot_line(line, color);
    _draw_call.execute(_target);
}

void SfmlRenderer::draw_rect(const Rect& rect, const Color& outline_color, const Color& fill_color)
{
    sf::RectangleShape sf_rectangle;
    sf_rectangle.setSize(static_cast<sf::Vector2f>(rect.size));
    sf_rectangle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_rectangle.setOutlineThickness(1);
    sf_rectangle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_rectangle.setPosition(static_cast<sf::Vector2f>(rect.position));

    _window.draw(sf_rectangle);
}

void SfmlRenderer::draw_polygon(std::span<const Vec2f> points, const Color& outline_color,
                                const Color& fill_color) const
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(points.size());

    for (usize i = 0; i < points.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(points[i]));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(1);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));
    _window.draw(sf_polygon);
}

void SfmlRenderer::draw_polygon(std::span<const Line> lines, const Color& outline_color, const Color& fill_color)
{
    sf::ConvexShape sf_polygon;
    sf_polygon.setPointCount(lines.size());

    for (usize i = 0; i < lines.size(); i++)
        sf_polygon.setPoint(i, static_cast<sf::Vector2f>(lines[i].from));

    sf_polygon.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_polygon.setOutlineThickness(1);
    sf_polygon.setFillColor(static_cast<sf::Color>(fill_color));
    _window.draw(sf_polygon);
}

void SfmlRenderer::draw_circle_sfml(const Circle& circle, const Color& outline_color, const Color& fill_color)
{
    sf::CircleShape sf_circle;
    sf_circle.setRadius(circle.radius);
    sf_circle.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_circle.setOutlineThickness(1);
    sf_circle.setFillColor(static_cast<sf::Color>(fill_color));
    sf_circle.setPosition(static_cast<sf::Vector2f>(circle.center - Vec2f{ circle.radius, circle.radius }));

    _window.draw(sf_circle);
}

void SfmlRenderer::draw_ellipse(const Ellipse& ellipse, const Color& outline_color, const Color& fill_color)
{
    EllipseShape sf_ellipse(ellipse);
    sf_ellipse.setOutlineColor(static_cast<sf::Color>(outline_color));
    sf_ellipse.setOutlineThickness(1);
    sf_ellipse.setFillColor(static_cast<sf::Color>(fill_color));

    _window.draw(sf_ellipse);
}

void SfmlRenderer::plot_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(from), static_cast<sf::Color>(color));
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(to), static_cast<sf::Color>(color));
}

void SfmlRenderer::plot_line(const Line& line, const Color& color)
{
    plot_line(line.from, line.to, color);
}

void SfmlRenderer::plot_rect(const Rect& rect, const Color& outline_color, const Color& fill_color) {}

} // namespace zth
