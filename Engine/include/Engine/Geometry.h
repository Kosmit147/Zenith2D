#pragma once

#include <SFML/System/Vector2.hpp>

struct Point2D
{
    float x;
    float y;

    explicit inline operator sf::Vector2f() const { return sf::Vector2f{ x, y }; }
};

struct Line
{
    Point2D from;
    Point2D to;
};

struct Ellipse
{
    Point2D center;
    float radius_x;
    float radius_y;
};

struct Circle
{
    Point2D center;
    float radius;

    explicit constexpr operator Ellipse() const { return Ellipse{ center, radius, radius }; }
};

// TODO
// wtf is this
// bool lines_intersect(const Line& first_line, const Line& second_line)
// {
//     int s1 = first_line.from.x * second_line.from.y + second_line.from.x * second_line.to.y
//              + first_line.from.y * second_line.to.x - second_line.from.y * second_line.to.x
//              - second_line.to.y * first_line.from.x - first_line.from.y * second_line.from.x;
// 
//     int s2 = first_line.to.x * second_line.from.y + second_line.from.x * second_line.to.y
//              + first_line.to.y * second_line.to.x - second_line.from.y * second_line.to.x
//              - second_line.to.y * first_line.to.x - first_line.to.y * second_line.from.x;
// 
//     int s3 = second_line.from.x * first_line.from.y + first_line.from.x * first_line.to.y
//              + second_line.from.y * first_line.to.x - first_line.from.y * first_line.to.x
//              - first_line.to.y * second_line.from.x - second_line.from.y * first_line.from.x;
// 
//     int s4 = second_line.to.x * first_line.from.y + first_line.from.x * first_line.to.y
//              + second_line.to.y * first_line.to.x - first_line.from.y * first_line.to.x
//              - first_line.to.y * second_line.to.x - second_line.to.y * first_line.from.x;
// 
//     if (s1 < 0 && s2 > 0 && s3 > 0 && s4 < 0 || s1 > 0 && s2 < 0 && s3 < 0 && s4 > 0)
//         return true;
//     else
//         return false;
// }
