#include "PrimitiveRenderer.h"
#include <math.h>

void PrimitiveRenderer::draw(Point2D point)
{
    sf::RectangleShape drawable;
    sf::Vertex vertex({ point.x, point.y }, sf::Color::Green);
    _window->sf_window().draw(&vertex, 1, sf::Points);
}

void PrimitiveRenderer::draw(const Line& line, LineRenderingAlgorithm alg)
{
    if (alg == LineRenderingAlgorithm::Incremental)
    {
        float m = (line.to.y - line.from.y) / (line.to.x - line.from.x);

        if (m > 1.0f)
        {
            m = (line.to.x - line.from.x) / (line.to.y - line.from.y);
            float x = line.from.x;

            for (int y = line.from.y; y < line.to.y; y++)
            {
                x += m;
                draw(Point2D{ std::round(x), (float)y });
            }
        }
        else
        {
            float y = line.from.y;

            for (int x = line.from.x; x < line.to.x; x++)
            {
                y += m;
                draw(Point2D{ (float)x, std::round(y) });
            }
        }
    }
    else if (alg == LineRenderingAlgorithm::Default)
    {
        sf::Vertex drawable[] = { sf::Vertex(sf::Vector2f(line.from.x, line.from.y)),
                                  sf::Vertex(sf::Vector2f(line.to.x, line.to.y)) };

        _window->sf_window().draw(drawable, 2, sf::Lines);
    }
}

void PrimitiveRenderer::draw(std::span<Line> lines, LineRenderingAlgorithm alg)
{
    for (const auto& line : lines)
        draw(line, alg);
}

void PrimitiveRenderer::draw(const Circle& circle)
{
    float a, step;
    float x, y, xc, yc;
    xc = circle.centerPoint.x;
    yc = circle.centerPoint.y;
    step = 1.0 / circle.R;
    for (a = 0; a < M_PI / 4; a += step)
    {
        x = circle.R * std::cos(a);
        y = circle.R * std::sin(a);

        draw(Point2D{ xc + x + 0.5f, yc + y + 0.5f });
        draw(Point2D{ yc + y + 0.5f, xc + x + 0.5f });
        draw(Point2D{ xc - x + 0.5f, yc + y + 0.5f });
        draw(Point2D{ yc - y + 0.5f, xc + x + 0.5f });
        draw(Point2D{ xc - x + 0.5f, yc - y + 0.5f });
        draw(Point2D{ yc - y + 0.5f, xc - x + 0.5f });
        draw(Point2D{ yc + y + 0.5f, xc - x + 0.5f });
        draw(Point2D{ xc + x + 0.5f, yc - y + 0.5f });
    }
}

void PrimitiveRenderer::draw(const Ellipse& ellipse)
{
    float a, step;
    float x, y, xc, yc;

    xc = ellipse.centerPoint.x;
    yc = ellipse.centerPoint.y;

    if (ellipse.Rx > ellipse.Ry)
        step = 1.0 / ellipse.Rx;
    else
        step = 1.0 / ellipse.Ry;

    for (a = 0; a < M_PI / 2; a += step)
    {
        x = ellipse.Rx * std::cos(a);
        y = ellipse.Ry * std::sin(a);
        draw(Point2D{ xc + x, yc + y });
        draw(Point2D{ xc - x, yc + y });
        draw(Point2D{ xc - x, yc - y });
        draw(Point2D{ xc + x, yc - y });
    }
}
