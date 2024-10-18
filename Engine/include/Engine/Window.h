#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

#include "Color.h"
#include "Event.h"

struct Resolution
{
    uint32_t width;
    uint32_t height;

    explicit inline operator sf::VideoMode() const { return sf::VideoMode{ width, height }; }
};

struct WindowParams
{
    std::string_view title;
    Resolution resolution;
    bool fullscreen = false;
    uint32_t framerate_limit = 60;
};

class Window
{
public:
    Color clear_color = Color::Black;

public:
    Window(const WindowParams& window_params);

    inline auto is_open() const { return _sf_window.isOpen(); }
    inline auto clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    inline auto clear(Color color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    std::optional<Event> poll_event();

    inline auto display() { _sf_window.display(); }
    inline auto close() { _sf_window.close(); }

    inline auto& sf_window() { return _sf_window; }
    inline auto& sf_window() const { return _sf_window; }

private:
    sf::RenderWindow _sf_window;
};
