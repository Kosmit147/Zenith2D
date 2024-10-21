#include "Application.hpp"

static const zth::ApplicationSpec spec = {
	.window_spec = {
		.title = "Sandbox",
		.resolution = { 1920, 1080 },
		.fullscreen = false,
		.framerate_limit = 60,
	},
	.logger_spec = {
		.target = zth::LogTarget::ConsoleAndFile,
		.log_file_path = "../log.txt",
	},
};

Application::Application() : zth::Application(spec)
{
    logger().print_notification("On init.");
    logger().log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    window().clear_color = zth::Color::Black;
}

Application::~Application()
{
    logger().print_notification("On shutdown.");
}

void Application::on_update(zth::u64 delta_time)
{
    (void)delta_time;
    // logger().print_notification("On Update with delta time: {} microseconds.", delta_time);

    auto& renderer = window().renderer();

    static constexpr zth::Line lines[] = {
        { { 2.0f, 2.0f }, { 2.0f, 1000.0f } },
        { { 2.0f, 1000.0f }, { 150.0f, 600.0f } },
        { { 150.0f, 600.0f }, { 1000.0f, 27.0f } },
        { { 1000.0f, 27.0f }, { 1600.0f, 100.0f } },
    };

    renderer.draw(zth::Point2D{ 300.0f, 300.0f }, zth::Color::Magenta);
    renderer.draw(lines, zth::Color::Green, zth::RenderingAlgorithm::Custom);
    renderer.draw(zth::Circle{ zth::Point2D{ 100.0f, 100.0f }, 50.0f }, zth::Color::Magenta,
                  zth::RenderingAlgorithm::Custom);
    renderer.draw(zth::Circle{ zth::Point2D{ 600.0f, 600.0f }, 50.0f }, zth::Color::Magenta,
                  zth::RenderingAlgorithm::Custom);
    renderer.draw(zth::Ellipse{ zth::Point2D{ 300.0f, 300.0f }, { 50.0f, 80.0f } }, zth::Color::Cyan,
                  zth::RenderingAlgorithm::Custom);
    renderer.draw(zth::Ellipse{ zth::Point2D{ 300.0f, 300.0f }, { 80.0f, 30.0f } }, zth::Color::Cyan,
                  zth::RenderingAlgorithm::Custom);
}

void Application::on_event(const zth::Event& event)
{
    switch (event.type())
    {
    case zth::EventType::WindowResized:
    {
        auto& resize_event = event.resize_event();
        logger().print_notification("Window resized. New size: ({}, {}).", resize_event.width,
                                    resize_event.height);
    }
    break;
    case zth::EventType::LostFocus:
    {
        logger().print_notification("Lost focus.");
    }
    break;
    case zth::EventType::GainedFocus:
    {
        logger().print_notification("Gained focus.");
    }
    break;
    case zth::EventType::KeyPressed:
    {
        auto& key_event = event.key_event();
        logger().print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case zth::EventType::KeyReleased:
    {
        auto& key_event = event.key_event();
        logger().print_notification("{} key released.", to_string(key_event.key));
    }
    break;
    case zth::EventType::MouseWheelScrolled:
    {
        auto& scroll_event = event.mouse_scroll_event();
        auto [pos_x, pos_y] = scroll_event.cursor_pos;
        logger().print_notification("Mouse scrolled: {}. Cursor pos: ({}, {}).", scroll_event.delta, pos_x,
                                    pos_y);
    }
    break;
    case zth::EventType::MouseButtonPressed:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        logger().print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                    to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseButtonReleased:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        logger().print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                    to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseMoved:
    {
        auto& mouse_move_event = event.mouse_move_event();
        auto [pos_x, pos_y] = mouse_move_event.cursor_pos;
        logger().print_notification("Mouse moved. New cursor pos: ({}, {}).", pos_x, pos_y);
    }
    break;
    case zth::EventType::MouseEntered:
    {
        logger().print_notification("Mouse entered.");
    }
    break;
    case zth::EventType::MouseLeft:
    {
        logger().print_notification("Mouse left.");
    }
    break;
    default:
        break;
    }
}
