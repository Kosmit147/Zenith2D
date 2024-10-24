#include "Window.hpp"

namespace zth {

static inline u32 get_window_style(const WindowSpec& spec)
{
    if (spec.fullscreen)
        return sf::Style::Default | sf::Style::Fullscreen;
    else
        return sf::Style::Default;
}

Window::Window(const WindowSpec& spec)
    : _sf_window(static_cast<sf::VideoMode>(spec.resolution), spec.title.data(), get_window_style(spec)),
      _renderer(*this)
{
    _sf_window.setFramerateLimit(spec.framerate_limit);
}

std::optional<Event> Window::poll_event()
{
    for (auto sf_event = sf::Event{}; _sf_window.pollEvent(sf_event);)
    {
        if (auto ev = Event::create_from_sf_event(sf_event); ev)
            return ev;
    }

    return {};
}

} // namespace zth
