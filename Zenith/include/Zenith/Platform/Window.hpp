#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/CustomPrimitiveRenderer.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Graphics/SfmlPrimitiveRenderer.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Utility/Utility.hpp"

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

    auto& primitive_renderer() const { return *_selected_primitive_renderer; }
    void set_primitive_renderer_type(RendererType renderer_type);
    RendererType get_primitive_renderer_type() const;

private:
    sf::RenderWindow _sf_window;
    SfmlPrimitiveRenderer _sfml_primitive_renderer{ _sf_window };
    CustomPrimitiveRenderer _custom_primitive_renderer{ _sf_window };
    PrimitiveRenderer* _selected_primitive_renderer = &_sfml_primitive_renderer;
};

// user of the engine interacts with the window through this class
class WindowApi
{
private:
    Window& _window;

public:
    explicit WindowApi(Window& window) : _window(window) {}
    ~WindowApi() = default;
    ZTH_NO_COPY_NO_MOVE(WindowApi)

    void set_clear_color(const Color& color) const { _window.clear_color = color; }
    void clear() const { _window.clear(); }
    void clear(const Color& color) const { _window.clear(color); }

    bool is_open() const { return _window.is_open(); }

    auto& primitive_renderer() const { return _window.primitive_renderer(); }
    void set_primitive_renderer_type(RendererType renderer_type) const;
    auto get_primitive_renderer_type() const { return _window.get_primitive_renderer_type(); }
};

} // namespace zth
