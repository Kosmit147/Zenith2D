#include "Zenith/Platform/Window.hpp"

namespace zth {

static u32 get_window_style(const WindowSpec& spec)
{
    if (spec.fullscreen)
        return sf::Style::Default | sf::Style::Fullscreen;
    else
        return sf::Style::Default;
}

Window::Window(const WindowSpec& spec)
    : _sf_window(static_cast<sf::VideoMode>(spec.resolution), spec.title, get_window_style(spec))
{
    _sf_window.setFramerateLimit(spec.frame_rate_limit);
}

std::optional<Event> Window::poll_event()
{
    for (auto sf_event = sf::Event{}; _sf_window.pollEvent(sf_event);)
    {
        if (auto ev = Event::create_from_sf_event(sf_event))
            return ev;
    }

    return {};
}

} // namespace zth
