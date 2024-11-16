#include "Sandbox.hpp"

#include "Scene.hpp"

ZTH_IMPLEMENT_APP(Sandbox)

static const zth::ApplicationSpec spec = {
    .window_spec = {
        .title = "Sandbox",
        .resolution = { 1920, 1080 },
        .fullscreen = false,
        .frame_rate_limit = 60,
    },
    .logger_spec = {
        .target = zth::LogTarget::ConsoleAndFile,
        .log_file_path = "log/sandbox_log.txt",
    },
};

Sandbox::Sandbox() : Application(spec)
{
    zth::logger->log_notification("On init.");
    zth::engine->change_scene(std::make_unique<Scene>());
}

Sandbox::~Sandbox()
{
    zth::logger->log_notification("On shutdown.");
}

void Sandbox::on_update()
{
    zth::Logger::print_notification("On Update with delta time: {} seconds.", zth::engine->delta_time());
    zth::Logger::print_notification("FPS: {}", zth::engine->fps());

    auto& renderer = zth::engine->window.renderer;

    static constexpr zth::Rect rect = { .position = { 960.0f, 540.0f }, .size = { 100.0f, 100.0f } };
    zth::RectangleShape rectangleShape(rect, zth::Color::magenta);

    renderer.draw(rectangleShape);

    rectangleShape.translate({ 0.0f, 100.0f }).rotate(30.0f, { 960.0f, 540.0f });

    renderer.draw(rectangleShape);

    // zth::Logger::print_notification("On Update with delta time: {} seconds.", zth::engine->delta_time());
    // zth::Logger::print_notification("FPS: {}", zth::engine->fps());
}

void Sandbox::on_event(const zth::Event& event)
{
    switch (event.type())
    {
        using enum zth::EventType;
    case WindowResized:
    {
        auto& resize_event = event.resize_event();
        auto& new_res = resize_event.new_res;
        zth::Logger::print_notification("Window resized. New size: ({}, {}).", new_res.width, new_res.height);
    }
    break;
    case MouseButtonPressed:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button pressed. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    case MouseButtonReleased:
    {
        auto& mouse_button_event = event.mouse_button_event();
        auto [pos_x, pos_y] = mouse_button_event.cursor_pos;
        zth::Logger::print_notification("{} mouse button released. Cursor pos: ({}, {}).",
                                        to_string(mouse_button_event.button), pos_x, pos_y);
    }
    break;
    default:
        break;
    }
}
