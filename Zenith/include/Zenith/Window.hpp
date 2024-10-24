#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

#include "Color.hpp"
#include "Event.hpp"
#include "PrimitiveRenderer.hpp"
#include "Typedefs.hpp"

namespace zth {

struct Resolution
{
    u32 width;
    u32 height;

    explicit inline operator sf::VideoMode() const { return sf::VideoMode{ width, height }; }
};

struct WindowSpec
{
    std::string_view title;
    Resolution resolution;
    bool fullscreen = false;
    u32 framerate_limit = 60;
};

class Window
{
public:
    Color clear_color = Color::Black;

public:
    Window(const WindowSpec& spec);

    Window(const Window& other) = delete;

    inline bool is_open() const { return _sf_window.isOpen(); }
    inline void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    inline void clear(const Color& color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    std::optional<Event> poll_event();

    inline void display() { _sf_window.display(); }
    inline void close() { _sf_window.close(); }

    // TODO: drawing api

    inline auto& sf_window() { return _sf_window; }
    inline auto& sf_window() const { return _sf_window; }
    inline auto& renderer() { return _renderer; }
    inline auto& renderer() const { return _renderer; }

private:
    sf::RenderWindow _sf_window;
    PrimitiveRenderer _renderer;
};

} // namespace zth
