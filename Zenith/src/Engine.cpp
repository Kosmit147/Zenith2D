#include "Engine.h"

#include <SFML/System/Time.hpp>

#include <utility>

namespace zth {

Engine::Engine(const WindowParams& window_params, const OnInitFunc& init_func,
               const OnUpdateFunc& update_func, const OnEventFunc& event_func)
    : _init_func(init_func), _update_func(update_func), _event_func(event_func), _window(window_params),
      _logger(LogTarget::Console)
{
    _init_func(_logger);
}

Engine::Engine(const WindowParams& window_params, OnInitFunc&& init_func, OnUpdateFunc&& update_func,
               OnEventFunc&& event_func)
    : _init_func(std::move(init_func)), _update_func(std::move(update_func)),
      _event_func(std::move(event_func)), _window(window_params), _logger(LogTarget::Console)
{
    _init_func(_logger);
}

void Engine::run()
{
    sf::Clock delta_clock;

    while (_window.is_open())
    {
        _window.clear();

        while (auto event = _window.poll_event())
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                _event_func(_logger, ev);
                _window.close();
                return;
            }

            _event_func(_logger, ev);
        }

        auto delta_time = static_cast<uint64_t>(delta_clock.restart().asMicroseconds());
        _update_func(_window.renderer(), _logger, delta_time);

        _window.display();
    }
}

} // namespace zth
