#pragma once

#include <SFML/System/Vector2.hpp>

struct Point2D
{
    float x, y;

    explicit inline operator sf::Vector2f() const { return sf::Vector2f{ x, y }; }
};

struct Line
{
    Point2D from;
    Point2D to;
};
