#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <optional>
#include <string>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Renderer.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Resolution.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

struct WindowSpec
{
    std::string title;
    Resolution resolution = { 800, 600 };
    bool fullscreen = false;
    u32 frame_rate_limit = 60;
};

class Window
{
private:
    sf::RenderWindow _sf_window;

public:
    Renderer renderer{ _sf_window };
    Color clear_color = Color::black;

public:
    ~Window() = default;
    ZTH_NO_COPY_NO_MOVE(Window)

    bool is_open() const { return _sf_window.isOpen(); }
    void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    void clear(const Color& color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    friend class Application;
    friend class Engine;

private:
    explicit Window(const WindowSpec& spec);

    std::optional<Event> poll_event();
    void display() { _sf_window.display(); }
    void close() { _sf_window.close(); }
};

} // namespace zth
