#pragma once

#include <SFML/Graphics.hpp>

#include <cstdint>
#include <optional>

#include "Color.h"
#include "Event.h"
#include "PrimitiveRenderer.h"

namespace zth {

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

    inline bool is_open() const { return _sf_window.isOpen(); }
    inline void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    inline void clear(Color color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    std::optional<Event> poll_event();

    inline void display() { _sf_window.display(); }
    inline void close() { _sf_window.close(); }

    inline auto& sf_window() { return _sf_window; }
    inline auto& sf_window() const { return _sf_window; }
    inline auto& renderer() { return _renderer; }
    inline auto& renderer() const { return _renderer; }

private:
    sf::RenderWindow _sf_window;
    PrimitiveRenderer _renderer;
};

} // namespace zth
