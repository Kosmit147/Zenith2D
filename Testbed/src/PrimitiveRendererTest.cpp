#include "Testbed.hpp"

#include <Zenith/Time/Timer.hpp>

#include <cassert>

static void draw_primitives(zth::PrimitiveRenderer& renderer)
{
    zth::Vec2f point = { 960.0f, 540.0f };
    point.translate({ 300.0f, 300.0f }).rotate(5.0f, { 960.0f, 540.0f }).scale(-0.2f, { 960.0f, 540.0f });

    renderer.draw_point(point, zth::Color::red);

    static constexpr zth::Vec2f points[] = {
        { 959.0f, 530.0f }, { 960.0f, 530.0f }, { 961.0f, 530.0f },
        { 959.0f, 531.0f }, { 960.0f, 531.0f }, { 961.0f, 531.0f },
    };

    renderer.draw_points(points, zth::Color::green);

    zth::Line line = { { 900.0f, 540.0f }, { 1200.0f, 540.0f } };
    line.translate({ 300.0f, 300.0f }).rotate(5.0f, { 960.0f, 540.0f }).scale(-0.8f, { 960.0f, 540.0f });

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

    static constexpr zth::Rect rect = { .position = { 960.0f, 740.0f }, .size = { 180.0f, 90.0f } };

    renderer.draw_rect(rect, zth::Color::blue);

    static constexpr zth::Rect filled_rect = { .position = { 300.0f, 70.0f }, .size = { 180.0f, 90.0f } };

    renderer.draw_filled_rect(filled_rect, zth::Color::blue);

    static constexpr zth::Vec2f polygon_from_points[] = {
        { 490.0f, 160.0f },
        { 590.0f, 160.0f },
        { 540.0f, 70.0f },
    };

    renderer.draw_convex_polygon(polygon_from_points, zth::Color::blue);

    static constexpr zth::Line polygon_from_lines[] = { { { 600.0f, 160.0f }, { 700.0f, 160.0f } },
                                                        { { 700.0f, 160.0f }, { 650.0f, 70.0f } },
                                                        { { 650.0f, 70.0f }, { 600.0f, 160.0f } } };

    renderer.draw_convex_polygon(polygon_from_lines, zth::Color::blue);

    static constexpr zth::Vec2f filled_polygon_from_points[] = {
        { 710.0f, 160.0f },
        { 810.0f, 160.0f },
        { 760.0f, 70.0f },
    };

    renderer.draw_filled_convex_polygon(filled_polygon_from_points, zth::Color::blue);

    static constexpr zth::Line filled_polygon_from_lines[] = { { { 820.0f, 160.0f }, { 920.0f, 160.0f } },
                                                               { { 920.0f, 160.0f }, { 870.0f, 70.0f } },
                                                               { { 870.0f, 70.0f }, { 820.0f, 160.0f } } };

    renderer.draw_filled_convex_polygon(filled_polygon_from_lines, zth::Color::blue);

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

static void sfml_primitive_renderer_test(zth::PrimitiveRenderer& renderer)
{
    draw_primitives(renderer);
}

static void custom_primitive_renderer_test(zth::PrimitiveRenderer& primitive_renderer)
{
    // switches between custom fill algorithms every 4 seconds

    auto renderer = dynamic_cast<zth::CustomPrimitiveRenderer*>(&primitive_renderer);
    assert(renderer != nullptr);

    if (!renderer)
        return;

    static zth::Timer fill_alg_timer;

    if (fill_alg_timer.elapsed_s() > 4.0)
    {
        auto alg = renderer->fill_algorithm == zth::FillAlgorithm::BoundaryFill ? zth::FillAlgorithm::FloodFill
                                                                                : zth::FillAlgorithm::BoundaryFill;
        renderer->fill_algorithm = alg;
        fill_alg_timer.reset();
    }

    draw_primitives(*renderer);
}

void Testbed::primitive_renderer_test() const
{
    // switches between custom and sfml rendering every 2 seconds
    // switches between custom fill algorithms every 4 seconds

    static zth::Timer renderer_type_timer;

    auto renderer_type = _window.renderer.get_primitive_renderer_type();

    if (renderer_type_timer.elapsed_s() > 2.0)
    {
        renderer_type = renderer_type == zth::PrimitiveRendererType::SfmlPrimitiveRenderer
                            ? zth::PrimitiveRendererType::CustomPrimitiveRenderer
                            : zth::PrimitiveRendererType::SfmlPrimitiveRenderer;

        _window.renderer.set_primitive_renderer_type(renderer_type);
        renderer_type_timer.reset();
    }

    auto& renderer = _window.renderer.primitive_renderer();

    switch (renderer_type)
    {
    case zth::PrimitiveRendererType::SfmlPrimitiveRenderer:
        sfml_primitive_renderer_test(renderer);
        break;
    case zth::PrimitiveRendererType::CustomPrimitiveRenderer:
        custom_primitive_renderer_test(renderer);
        break;
    }
}
