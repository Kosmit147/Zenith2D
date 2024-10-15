#include "Engine.h"

#include <SFML/System/Time.hpp>

#include <utility>

static inline uint32_t get_window_style(const WindowParams& params)
{
    if (params.fullscreen)
        return sf::Style::Default | sf::Style::Fullscreen;
    else
        return sf::Style::Default;
}

Engine::Engine(const WindowParams& window_params, const OnInitFunc& init_func, const OnUpdateFunc& update_func, const OnEventFunc& event_func)
    : _window(static_cast<sf::VideoMode>(window_params.resolution), window_params.title.data(), get_window_style(window_params)),
      _init_func(init_func), _update_func(update_func), _event_func(event_func), _logger(true), _renderer(&_window)
{
    _window.setFramerateLimit(window_params.framerate_limit);
    _init_func();
}

Engine::Engine(const WindowParams& window_params, OnInitFunc&& init_func, OnUpdateFunc&& update_func, OnEventFunc&& event_func)
    : _window(static_cast<sf::VideoMode>(window_params.resolution), window_params.title.data(), get_window_style(window_params)),
      _init_func(std::move(init_func)), _update_func(std::move(update_func)), _event_func(std::move(event_func)),
	  _logger(true), _renderer(&_window)
{
    _window.setFramerateLimit(window_params.framerate_limit);
    _init_func();
}

void Engine::run()
{
    sf::Clock delta_clock;

    while (_window.isOpen())
    {
        for (auto sf_event = sf::Event{}; _window.pollEvent(sf_event);)
        {
            if (sf_event.type == sf::Event::Closed)
                _window.close();
            
            if (auto event = Event::create_from_sf_event(sf_event); event)
				_event_func(event.value());
        }

        auto delta_time = delta_clock.restart().asMicroseconds();
        _update_func(delta_time);

        _window.clear(static_cast<sf::Color>(clear_color));

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
