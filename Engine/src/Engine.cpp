#include "Engine.h"

#include <SFML/System/Time.hpp>

#include <utility>

Engine::Engine(const WindowParams& window_params, const OnInitFunc& init_func,
               const OnUpdateFunc& update_func, const OnEventFunc& event_func)
    : _window(window_params), _init_func(init_func), _update_func(update_func), _event_func(event_func),
      _logger(LogTarget::Console), _renderer(&_window)
{
    _init_func();
}

Engine::Engine(const WindowParams& window_params, OnInitFunc&& init_func, OnUpdateFunc&& update_func,
               OnEventFunc&& event_func)
    : _window(window_params), _init_func(std::move(init_func)), _update_func(std::move(update_func)),
      _event_func(std::move(event_func)), _logger(LogTarget::Console), _renderer(&_window)
{
    _init_func();
}

void Engine::run()
{
    sf::Clock delta_clock;

    while (_window.is_open())
    {
        for (auto event = _window.poll_event(); event;)
        {
            const auto& ev = event.value();

            if (ev.type() == EventType::WindowClosed)
            {
                _window.close();
                return;
            }

            _event_func(ev);
        }

        auto delta_time = delta_clock.restart().asMicroseconds();
        _update_func(delta_time);

        _window.clear();

        Line lines[] = {
            Line{ { 2.0f, 2.0f }, { 2.0f, 1000.0f } },
            Line{ { 2.0f, 1000.0f }, { 150.0f, 600.0f } },
            Line{ { 150.0f, 600.0f }, { 1000.0f, 27.0f } },
        };

        _renderer.draw(Point2D{ 300.0f, 300.0f });
        _renderer.draw(lines);

        _window.display();
    }
}
