#include "Zenith/Core/Application.hpp"

#include <SFML/System/Clock.hpp>

#include "Zenith/Core/Engine.hpp"
#include "Zenith/Logging/Logger.hpp"

namespace zth {

Application::Application(const ApplicationSpec& spec)
{
    // logger should be initialized first
    logger.init(spec.logger_spec);
    engine.init(spec.window_spec);
}

Application::~Application()
{
    engine.terminate();
    logger.terminate();
}

void Application::run()
{
    sf::Clock delta_t_clock;

    while (engine->window.is_open())
    {
        engine->_delta_time = delta_t_clock.restart().asMilliseconds() / 1000.0;
        engine->window.clear();

        while (auto event = engine->window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                handle_event(ev);
                engine->window.close();
                return;
            }

            handle_event(ev);
        }

        handle_update();
        engine->window.display();
        engine->_frame_counter.update();
    }
}

void Application::handle_update()
{
    on_update();
    engine->_updater.update();
}

void Application::handle_event(const Event& event)
{
    if (event.is_input_event())
        handle_input_event(event);

    on_event(event);
    engine->_event_dispatcher.dispatch(event);
}

void Application::handle_input_event(const Event& event)
{
    switch (event.type())
    {
    case EventType::KeyPressed:
    {
        const auto& [key] = event.key_event();
        engine->input.set_key_pressed(key, true);
    }
    break;
    case EventType::KeyReleased:
    {
        const auto& [key] = event.key_event();
        engine->input.set_key_pressed(key, false);
    }
    break;
    case EventType::MouseButtonPressed:
    {
        const auto& [button, cursor_pos] = event.mouse_button_event();
        engine->input.set_mouse_button_pressed(button, true);
    }
    break;
    case EventType::MouseButtonReleased:
    {
        const auto& [button, cursor_pos] = event.mouse_button_event();
        engine->input.set_mouse_button_pressed(button, false);
    }
    break;
    case EventType::MouseMoved:
    {
        const auto& [new_cursor_pos] = event.mouse_move_event();
        engine->input.set_cursor_pos(new_cursor_pos);
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
