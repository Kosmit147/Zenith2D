#include "Application.hpp"

#include <SFML/System/Time.hpp>

namespace zth {

Application::Application(const ApplicationSpec& spec) : _logger(spec.logger_spec), _internal_window(spec.window_spec) {}

void Application::run()
{
    sf::Clock delta_t_clock;

    while (_internal_window.is_open())
    {
        const auto delta_time = static_cast<u64>(delta_t_clock.restart().asMicroseconds());
        _internal_window.clear();

        while (auto event = _internal_window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                on_event(ev);
                _internal_window.close();
                return;
            }

            on_event(ev);
        }

        on_update(delta_time);
        _internal_window.display();
    }
}

} // namespace zth
