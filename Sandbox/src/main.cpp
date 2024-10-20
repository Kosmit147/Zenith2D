#include "Engine/Engine.h"

static void on_init(Logger& logger)
{
    logger.print_notification("On Init");
}

static void on_update(PrimitiveRenderer& renderer, Logger& logger, uint64_t delta_time)
{
    (void)delta_time;
    (void)logger;
    // logger.print_notification("On Update with delta time: {} ms.", delta_time);

    static constexpr Line lines[] = {
        Line{ { 2.0f, 2.0f }, { 2.0f, 1000.0f } },
        Line{ { 2.0f, 1000.0f }, { 150.0f, 600.0f } },
        Line{ { 150.0f, 600.0f }, { 1000.0f, 27.0f } },
    };

    renderer.draw(Point2D{ 300.0f, 300.0f }, Color::Magenta);
    renderer.draw(lines, Color::Green);
    renderer.draw(Circle{ Point2D{ 100.0f, 100.0f }, 50.0f }, Color::Magenta);
    renderer.draw(Circle{ Point2D{ 600.0f, 600.0f }, 50.0f }, Color::Magenta);
    renderer.draw(Ellipse{ Point2D{ 300.0f, 300.0f }, 50.0f, 80.0f }, Color::Cyan);
    renderer.draw(Ellipse{ Point2D{ 300.0f, 300.0f }, 80.0f, 30.0f }, Color::Cyan);
}

static void on_event(Logger& logger, const Event& e)
{
    switch (e.type())
    {
    case EventType::WindowResized:
    {
        auto& resize_event = e.resize_event();
        logger.print_notification("Window resized. New size: ({}, {}).", resize_event.width,
                                  resize_event.height);
    }
    break;
    case EventType::LostFocus:
    {
        logger.print_notification("Lost focus.");
    }
    break;
    case EventType::GainedFocus:
    {
        logger.print_notification("Gained focus.");
    }
    break;
    case EventType::KeyPressed:
    {
        auto& key_event = e.key_event();
        logger.print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case EventType::KeyReleased:
    {
        auto& key_event = e.key_event();
        logger.print_notification("{} key released.", to_string(key_event.key));
    }
    break;
    case EventType::MouseWheelScrolled:
    {
        auto& scroll_event = e.mouse_scroll_event();
        auto [pos_x, pos_y] = scroll_event.cursor_pos;
        logger.print_notification("Mouse scrolled: {}. Cursor pos: ({}, {}).", scroll_event.delta, pos_x,
                                  pos_y);
    }
    break;
    case EventType::MouseButtonPressed:
    {
        auto& mouse_button_event = e.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        logger.print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                  to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case EventType::MouseButtonReleased:
    {
        auto& mouse_button_event = e.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        logger.print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                  to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case EventType::MouseMoved:
    {
        auto& mouse_move_event = e.mouse_move_event();
        auto [pos_x, pos_y] = mouse_move_event.cursor_pos;
        logger.print_notification("Mouse moved. New cursor pos: ({}, {}).", pos_x, pos_y);
    }
    break;
    case EventType::MouseEntered:
    {
        logger.print_notification("Mouse entered.");
    }
    break;
    case EventType::MouseLeft:
    {
        logger.print_notification("Mouse left.");
    }
    break;
    default:
        break;
    }
}

int main()
{
    static constexpr WindowParams window_params = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .framerate_limit = 60,
    };

    Engine e{ window_params, on_init, on_update, on_event };

    e.logger().log_target = LogTarget::ConsoleAndFile;
    e.logger().log_file_path = "../log.txt";
    e.logger().log_error("Logger Test.");
    e.logger().log_error("Logger Test: {}, {}, {}.", 1, 2, 3);

    e.window().clear_color = Color::Black;
    e.run();
}
