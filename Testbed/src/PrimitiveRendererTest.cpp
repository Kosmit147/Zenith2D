#include "PrimitiveRendererTest.hpp"

#include <Zenith/Time/Timer.hpp>

void primitive_renderer_test(zth::PrimitiveRenderer& renderer)
{
    // switches between custom and sfml rendering every 2 seconds
    // switches between custom fill algorithms every 4 seconds

    static zth::Timer alg_timer;
    static zth::Timer fill_timer;

    if (alg_timer.elapsed_s() > 2.0)
    {
        auto alg = renderer.rendering_algorithm() == zth::RenderingAlgorithm::Sfml ? zth::RenderingAlgorithm::Custom
                                                                                   : zth::RenderingAlgorithm::Sfml;
        renderer.set_rendering_algorithm(alg);
        alg_timer.reset();
    }

    if (fill_timer.elapsed_s() > 4.0)
    {
        auto alg = renderer.fill_algorithm() == zth::FillAlgorithm::BoundaryFill ? zth::FillAlgorithm::FloodFill
                                                                                 : zth::FillAlgorithm::BoundaryFill;
        renderer.set_fill_algorithm(alg);
        fill_timer.reset();
    }

    static constexpr zth::Vec2f point = { 960.0f, 540.0f };

    renderer.draw_point(point, zth::Color::red);

    static constexpr zth::Vec2f points[] = {
        { 959.0f, 530.0f }, { 960.0f, 530.0f }, { 961.0f, 530.0f },
        { 959.0f, 531.0f }, { 960.0f, 531.0f }, { 961.0f, 531.0f },
    };

    renderer.draw_points(points, zth::Color::green);

    static constexpr zth::Vec2f line_from_points[] = { { 10.0f, 10.0f }, { 1910.0f, 10.0f } };

    renderer.draw_line(line_from_points[0], line_from_points[1], zth::Color::red);

    static constexpr zth::Line line = { { 10.0f, 20.0f }, { 1910.0f, 20.0f } };

    renderer.draw_line(line, zth::Color::green);

    static constexpr zth::Vec2f line_strip[] = {
        { 10.0f, 30.0f },
        { 1910.0f, 30.0f },
        { 1910.0f, 40.0f },
        { 10.0f, 40.0f },
    };

    renderer.draw_line_strip(line_strip, zth::Color::yellow);

    static constexpr zth::Line lines[] = { { { 10.0f, 50.0f }, { 1910.0f, 50.0f } },
                                           { { 1910.0f, 60.0f }, { 10.0f, 60.0f } } };

    renderer.draw_lines(lines, zth::Color::yellow);

    static constexpr zth::Vec2f closed_lines_from_points[] = {
        { 10.0f, 70.0f },
        { 100.0f, 70.0f },
        { 10.0f, 150.0f },
    };

    renderer.draw_closed_lines(closed_lines_from_points, zth::Color::blue);

    static constexpr zth::Line closed_lines[] = { { { 10.0f, 160.0f }, { 100.0f, 160.0f } },
                                                  { { 100.0f, 160.0f }, { 100.0f, 80.0f } } };

    renderer.draw_closed_lines(closed_lines, zth::Color::blue);

    static constexpr zth::Rect rect = { .position = { 110.0f, 70.0f }, .size = { 180.0f, 90.0f } };

    renderer.draw_rect(rect, zth::Color::blue);

    static constexpr zth::Rect filled_rect = { .position = { 300.0f, 70.0f }, .size = { 180.0f, 90.0f } };

    renderer.draw_filled_rect(filled_rect, zth::Color::blue);

    static constexpr zth::Vec2f polygon_from_points[] = {
        { 490.0f, 160.0f },
        { 590.0f, 160.0f },
        { 540.0f, 70.0f },
    };

    renderer.draw_polygon(polygon_from_points, zth::Color::blue);

    static constexpr zth::Line polygon_from_lines[] = { { { 600.0f, 160.0f }, { 700.0f, 160.0f } },
                                                        { { 700.0f, 160.0f }, { 650.0f, 70.0f } },
                                                        { { 650.0f, 70.0f }, { 600.0f, 160.0f } } };

    renderer.draw_polygon(polygon_from_lines, zth::Color::blue);

    static constexpr zth::Vec2f filled_polygon_from_points[] = {
        { 710.0f, 160.0f },
        { 810.0f, 160.0f },
        { 760.0f, 70.0f },
    };

    renderer.draw_filled_polygon(filled_polygon_from_points, zth::Color::blue);

    static constexpr zth::Line filled_polygon_from_lines[] = { { { 820.0f, 160.0f }, { 920.0f, 160.0f } },
                                                               { { 920.0f, 160.0f }, { 870.0f, 70.0f } },
                                                               { { 870.0f, 70.0f }, { 820.0f, 160.0f } } };

    renderer.draw_filled_polygon(filled_polygon_from_lines, zth::Color::blue);

    static constexpr zth::Circle circle = {
        .center = { 980.0f, 115.0f },
        .radius = 50.0f,
    };

    renderer.draw_circle(circle, zth::Color::blue);

    static constexpr zth::Circle filled_circle = {
        .center = { 1090.0f, 115.0f },
        .radius = 50.0f,
    };

    renderer.draw_filled_circle(filled_circle, zth::Color::blue);

    static constexpr zth::Ellipse ellipse = {
        .center = { 1250.0f, 115.0f },
        .radius = { 100.0f, 50.0f },
    };

    renderer.draw_ellipse(ellipse, zth::Color::blue);

    static constexpr zth::Ellipse filled_ellipse = {
        .center = { 1460.0f, 115.0f },
        .radius = { 100.0f, 50.0f },
    };

    renderer.draw_filled_ellipse(filled_ellipse, zth::Color::blue);
}
