#include "Sandbox.hpp"

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

Sandbox::Sandbox()
    : Application(spec), _player_texture(zth::Texture::from_file("assets/emoji.png").value_or(zth::Texture{})),
      _player(_player_texture)
{
    zth::Logger::print_notification("On init.");
    _logger.log_error("Logger Test: {}, {}, {}.", 1, 2, 3);
    _window.set_clear_color(zth::Color::black);
    _event_dispatcher.register_listener(zth::EventType::KeyPressed, _player);
    _updater.register_updatable(_player);
}

Sandbox::~Sandbox()
{
    zth::Logger::print_notification("On shutdown.");
    _event_dispatcher.deregister_listener(_player);
    _updater.deregister_updatable(_player);
}

void Sandbox::on_update([[maybe_unused]] const double delta_time)
{
    zth::Logger::print_notification("On Update with delta time: {} seconds.", delta_time);
    zth::Logger::print_notification("FPS: {}", get_fps());
    _window.renderer.draw(_player);
}

void Sandbox::on_event(const zth::Event& event, [[maybe_unused]] const double delta_time)
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
    case KeyPressed:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key pressed.", to_string(key_event.key));
    }
    break;
    case KeyReleased:
    {
        auto& key_event = event.key_event();
        zth::Logger::print_notification("{} key released.", to_string(key_event.key));
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
