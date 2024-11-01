#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

#include "Color.hpp"
#include "Event.hpp"
#include "PrimitiveRenderer.hpp"
#include "Typedefs.hpp"
#include "Utility.hpp"

namespace zth {

struct Resolution
{
    u32 width;
    u32 height;

    explicit operator sf::VideoMode() const { return sf::VideoMode{ width, height }; }
};

struct WindowSpec
{
    std::string title;
    Resolution resolution;
    bool fullscreen = false;
    u32 frame_rate_limit = 60;
};

class Window
{
public:
    Color clear_color = Color::black;
    PrimitiveRenderer primitive_renderer = PrimitiveRenderer{ _sf_window };

public:
    explicit Window(const WindowSpec& spec);
    ~Window() = default;
    ZTH_NO_COPY_NO_MOVE(Window)

    bool is_open() const { return _sf_window.isOpen(); }
    void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    void clear(const Color& color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    std::optional<Event> poll_event();

    void display() { _sf_window.display(); }
    void close() { _sf_window.close(); }

private:
    sf::RenderWindow _sf_window;
};

// user of the engine interacts with the window through this class
class WindowApi
{
private:
    Window& _window;

public:
    PrimitiveRenderer& primitive_renderer;

public:
    explicit WindowApi(Window& window) : _window(window), primitive_renderer(_window.primitive_renderer) {}
    ~WindowApi() = default;
    ZTH_NO_COPY_NO_MOVE(WindowApi)

    void set_clear_color(const Color& color) const { _window.clear_color = color; }
    void clear() const { _window.clear(); }
    void clear(const Color& color) const { _window.clear(color); }

    bool is_open() const { return _window.is_open(); }
};

} // namespace zth
