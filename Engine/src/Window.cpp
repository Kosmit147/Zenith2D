#include "Window.h"

static inline uint32_t get_window_style(const WindowParams& params)
{
    if (params.fullscreen)
        return sf::Style::Default | sf::Style::Fullscreen;
    else
        return sf::Style::Default;
}

Window::Window(const WindowParams& window_params)
    : _sf_window(static_cast<sf::VideoMode>(window_params.resolution), window_params.title.data(),
                 get_window_style(window_params)),
      _renderer(this)
{
    _sf_window.setFramerateLimit(window_params.framerate_limit);
}

std::optional<Event> Window::poll_event()
{
    if (auto sf_event = sf::Event{}; _sf_window.pollEvent(sf_event))
        return Event::create_from_sf_event(sf_event);

    return {};
}
