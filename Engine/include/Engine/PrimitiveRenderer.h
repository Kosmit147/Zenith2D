#pragma once

#include <SFML/Graphics.hpp>

#include <span>

struct Point2D
{
    float x, y;
};

struct Line
{
    Point2D from;
    Point2D to;
};

enum class LineRenderingAlgorithm
{
    Default,
    Incremental,
};

class PrimitiveRenderer
{
public:
    inline PrimitiveRenderer(sf::RenderWindow* window) : _window(window) {}

    void draw(Point2D point);
    void draw(const Line& line, LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);
    void draw(std::span<Line> lines, LineRenderingAlgorithm alg = LineRenderingAlgorithm::Default);

private:
    sf::RenderWindow* _window;
};