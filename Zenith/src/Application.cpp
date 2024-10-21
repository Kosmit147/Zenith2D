#include "Application.hpp"

#include <SFML/System/Time.hpp>

namespace zth {

void Application::run()
{
    sf::Clock delta_t_clock;

    while (_window.is_open())
    {
        auto delta_time = static_cast<u64>(delta_t_clock.restart().asMicroseconds());
        _window.clear();

        while (auto event = _window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                on_event(ev);
                _window.close();
                return;
            }

            on_event(ev);
        }

        on_update(delta_time);
        _window.display();
    }
}

} // namespace zth
