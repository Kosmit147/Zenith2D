#include "Zenith/Core/Application.hpp"

#include <SFML/System/Clock.hpp>

namespace zth {

Application::Application(const ApplicationSpec& spec) : _logger(spec.logger_spec), _internal_window(spec.window_spec) {}

void Application::run()
{
    sf::Clock delta_t_clock;

    while (_internal_window.is_open())
    {
        const auto delta_time = delta_t_clock.restart().asMilliseconds() / 1000.0;
        _internal_window.clear();

        while (auto event = _internal_window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                handle_event(ev, delta_time);
                _internal_window.close();
                return;
            }

            handle_event(ev, delta_time);
        }

        handle_update(delta_time);
        _internal_window.display();
        _frame_counter.update();
    }
}

void Application::handle_update(double delta_time)
{
    on_update(delta_time);
    _updater.update(delta_time);
}

void Application::handle_event(const Event& event, double delta_time)
{
    on_event(event, delta_time);
    _event_dispatcher.dispatch(event, delta_time);
}

} // namespace zth
