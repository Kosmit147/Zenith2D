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
        if (auto ev = Event::from_sf_event(sf_event))
            return ev;
    }

    return {};
}

void Window::set_primitive_renderer_type(RendererType renderer_type)
{
    switch (renderer_type)
    {
    case RendererType::SfmlRenderer:
        _selected_primitive_renderer = &_sfml_primitive_renderer;
        break;
    case RendererType::CustomRenderer:
        _selected_primitive_renderer = &_custom_primitive_renderer;
        break;
    }
}

RendererType Window::get_primitive_renderer_type() const
{
    if (_selected_primitive_renderer == &_sfml_primitive_renderer)
        return RendererType::SfmlRenderer;
    else if (_selected_primitive_renderer == &_custom_primitive_renderer)
        return RendererType::CustomRenderer;

    assert(false);
    std::unreachable();
}

void WindowApi::set_primitive_renderer_type(RendererType renderer_type) const
{
    _window.set_primitive_renderer_type(renderer_type);
}

} // namespace zth
