#include "Zenith/Math/Geometry.hpp"

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

bool points_form_a_valid_polygon(std::span<const Vec2f> points)
{
    if (points.empty())
        return false;

    // check if any lines intersect each other
    for (usize i = 0; i < points.size() - 1; i++)
    {
        Line current_line = { points[i], points[i + 1] };

        for (usize j = i + 1; j < points.size() - 1; j++)
        {
            Line other_line = { points[j], points[j + 1] };

            if (current_line.intersects(other_line))
                return false;
        }

        Line closing_line = { points[points.size() - 1], points[0] };

        if (current_line.intersects(closing_line))
            return false;
    }

    return true;
}

bool lines_form_a_valid_polygon(std::span<const Line> lines)
{
    if (lines.empty())
        return false;

    // make sure the lines connect to each other
    for (usize i = 0; i < lines.size() - 1; i++)
    {
        if (lines[i].to != lines[i + 1].from)
            return false;
    }

    // make sure the last line connects to the first one
    if (lines.back().to != lines.front().from)
        return false;

    // check if any lines intersect each other
    for (usize i = 0; i < lines.size() - 1; i++)
    {
        for (usize j = i + 1; j < lines.size(); j++)
        {
            if (lines_intersect(lines[i], lines[j]))
                return false;
        }
    }

    return true;
}

} // namespace zth
