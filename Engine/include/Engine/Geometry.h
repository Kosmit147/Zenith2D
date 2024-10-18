#pragma once

struct Point2D
{
    float x, y;
};

struct Line
{
    Point2D from;
    Point2D to;
};

struct Circle
{
    Point2D centerPoint;
    float R;
};

struct Ellipse
{
    Point2D centerPoint;
    float Rx, Ry;
};
