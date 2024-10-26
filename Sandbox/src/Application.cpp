#include "Application.hpp"

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "../log.txt",
    },
};

Application::Application() : zth::Application(spec)
{
    zth::Logger::print_notification("On init.");
    _logger.log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    _window.clear_color = zth::Color::black;
}

Application::~Application()
{
    zth::Logger::print_notification("On shutdown.");
}

void Application::on_update(const zth::u64 delta_time)
{
    (void)delta_time;
    // logger().print_notification("On Update with delta time: {} microseconds.", delta_time);

    auto& renderer = _window.primitive_renderer;

    static constexpr zth::Line lines[] = {
        { { 2.0f, 2.0f }, { 2.0f, 1000.0f } },
        { { 2.0f, 1000.0f }, { 150.0f, 600.0f } },
        { { 150.0f, 600.0f }, { 1000.0f, 27.0f } },
        { { 1000.0f, 27.0f }, { 1600.0f, 100.0f } },
    };

    renderer.draw_point(zth::Point2D{ 300.0f, 300.0f }, zth::Color::magenta);
    renderer.draw_closed_lines(lines, zth::Color::green);
    renderer.draw_filled_circle(zth::Circle{ zth::Point2D{ 100.0f, 100.0f }, 50.0f }, zth::Color::magenta,
                                zth::Color::magenta);
    renderer.draw_filled_circle(zth::Circle{ zth::Point2D{ 600.0f, 600.0f }, 50.0f }, zth::Color::magenta,
                                zth::Color::magenta);
    renderer.draw_filled_ellipse(zth::Ellipse{ zth::Point2D{ 300.0f, 300.0f }, { 50.0f, 80.0f } }, zth::Color::cyan,
                                 zth::Color::cyan);
    renderer.draw_filled_ellipse(zth::Ellipse{ zth::Point2D{ 300.0f, 300.0f }, { 80.0f, 30.0f } }, zth::Color::cyan,
                                 zth::Color::cyan);

    static constexpr zth::Point2D polygon[] = {
        { 1300.0f, 450.0f },
        { 1500.0f, 450.0f },
        { 1400.0f, 400.0f },
        // { 1100.0f, 600.0f },
    };

    static constexpr zth::Line polygon_lines[] = {
        {
            { 1000.0f, 500.0f },
            { 1200.0f, 500.0f },
        },
        {
            { 1200.0f, 500.0f },
            { 1100.0f, 450.0f },
        },
        {
            { 1100.0f, 450.0f },
            { 1000.0f, 500.0f },
        },
    };

    renderer.draw_polygon(polygon, zth::Color::green);
    renderer.draw_filled_polygon(polygon_lines, zth::Color::blue, zth::Color::blue);

    static constexpr zth::Rect rect = { .position = { 1500.0f, 800.0f }, .size = { 200.0f, 200.0f } };

    renderer.draw_filled_rect(rect, zth::Color::blue, zth::Color::white);

    static constexpr zth::Point2D polygon_points[] = {
        { 1000.0f, 700.0f },  { 1400.0f, 500.0f }, { 1100.0f, 950.0f },
        { 1000.0f, 1000.0f }, { 900.0f, 950.0f },  { 900.0f, 850.0f },
    };

    renderer.draw_filled_polygon(polygon_points, zth::Color::white, zth::Color::red);
}

void Application::on_event(const zth::Event& event)
{
    switch (event.type())
    {
    case zth::EventType::WindowResized:
    {
        auto& resize_event = event.resize_event();
        zth::Logger::print_notification("Window resized. New size: ({}, {}).", resize_event.width, resize_event.height);
    }
    break;
    case zth::EventType::LostFocus:
    {
        zth::Logger::print_notification("Lost focus.");
    }
    break;
    case zth::EventType::GainedFocus:
    {
        zth::Logger::print_notification("Gained focus.");
    }
    break;
    case zth::EventType::KeyPressed:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case zth::EventType::KeyReleased:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key released.", to_string(key_event.key));
    }
    break;
    case zth::EventType::MouseWheelScrolled:
    {
        auto& scroll_event = event.mouse_scroll_event();
        auto [pos_x, pos_y] = scroll_event.cursor_pos;
        zth::Logger::print_notification("Mouse scrolled: {}. Cursor pos: ({}, {}).", scroll_event.delta, pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseButtonPressed:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseButtonReleased:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseMoved:
    {
        auto& mouse_move_event = event.mouse_move_event();
        auto [pos_x, pos_y] = mouse_move_event.cursor_pos;
        zth::Logger::print_notification("Mouse moved. New cursor pos: ({}, {}).", pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseEntered:
    {
        zth::Logger::print_notification("Mouse entered.");
    }
    break;
    case zth::EventType::MouseLeft:
    {
        zth::Logger::print_notification("Mouse left.");
    }
    break;
    default:
        break;
    }
}
