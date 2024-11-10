#include "Zenith/Core/Engine.hpp"

#include "Zenith/Logging/Logger.hpp"

namespace zth {

Engine::Engine(const WindowSpec& window_spec)
    : window(window_spec)
{
    logger.get_or_init().log_notification("Engine initialized.");
}

Engine::~Engine()
{
    logger.get_or_init().log_notification("Engine shut down.");
}

void Engine::change_scene(std::unique_ptr<Scene> new_scene)
{
    _queued_scene = std::move(new_scene);
}

void Engine::on_update()
{
    if (_queued_scene)
    {
        scene = std::move(_queued_scene);
        scene->on_load();
    }

    if (scene)
        scene->update();
}

void Engine::on_event(const Event& event)
{
    if (event.is_input_event())
        on_input_event(event);

    if (scene)
        scene->dispatch_event(event);
}

void Engine::on_input_event(const Event& event)
{
    switch (event.type())
    {
    case EventType::KeyPressed:
    {
        const auto& [key] = event.key_event();
        input.set_key_pressed(key, true);
    }
    break;
    case EventType::KeyReleased:
    {
        const auto& [key] = event.key_event();
        input.set_key_pressed(key, false);
    }
    break;
    case EventType::MouseButtonPressed:
    {
        const auto& [button, cursor_pos] = event.mouse_button_event();
        input.set_mouse_button_pressed(button, true);
    }
    break;
    case EventType::MouseButtonReleased:
    {
        const auto& [button, cursor_pos] = event.mouse_button_event();
        input.set_mouse_button_pressed(button, false);
    }
    break;
    case EventType::MouseMoved:
    {
        const auto& [new_cursor_pos] = event.mouse_move_event();
        input.set_cursor_pos(new_cursor_pos);
    }
    break;
    case EventType::GainedFocus:
    case EventType::LostFocus:
    case EventType::MouseEntered:
    case EventType::MouseLeft:
    case EventType::MouseWheelScrolled:
    case EventType::WindowClosed:
    case EventType::WindowResized:
    {
        assert(false);
        std::unreachable();
    }
    }
}

} // namespace zth
