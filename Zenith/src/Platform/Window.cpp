#include "Zenith/Platform/Window.hpp"

#include "Zenith/Graphics/OpenGlContextSettings.hpp"

namespace zth {

static constexpr OpenGlContextSettings opengl_context_settings = {
    .version = { 4, 3 },
    .depth_bits = 0,
    .stencil_bits = 0,
    .antialiasing_level = 0,

#ifdef _DEBUG
    .attributes = sf::ContextSettings::Default | sf::ContextSettings::Debug,
#else
    .attributes = sf::ContextSettings::Default,
#endif

    .s_rgb_capable = false,
};

static u32 get_sf_window_style(const WindowSpec& spec)
{
    if (spec.fullscreen)
        return sf::Style::Default | sf::Style::Fullscreen;
    else
        return sf::Style::Default;
}

Window::Window(const WindowSpec& spec)
    : _sf_window(static_cast<sf::VideoMode>(spec.resolution), spec.title, get_sf_window_style(spec),
                 static_cast<sf::ContextSettings>(opengl_context_settings))
{
    _sf_window.setFramerateLimit(spec.frame_rate_limit);
}

std::optional<Event> Window::poll_event()
{
    for (auto event = sf::Event{}; _sf_window.pollEvent(event);)
    {
        if (auto ev = Event::from_sf_event(event))
            return ev;
    }

    return {};
}

} // namespace zth
