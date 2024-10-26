#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <utility>

#include "Color.hpp"
#include "Event.hpp"
#include "PrimitiveRenderer.hpp"
#include "Typedefs.hpp"

namespace zth {

struct Resolution
{
    u32 width;
    u32 height;

    explicit operator sf::VideoMode() const { return sf::VideoMode{ width, height }; }
};

struct WindowSpec
{
    std::string_view title;
    Resolution resolution;
    bool fullscreen = false;
    u32 frame_rate_limit = 60;
};

class Window
{
public:
    Color clear_color = Color::black;
    const PrimitiveRenderer primitive_renderer = PrimitiveRenderer{ *this };

public:
    explicit Window(const WindowSpec& spec);

    // TODO: some of these functions should not be accessible to the user of the engine
    bool is_open() const { return _sf_window.isOpen(); }
    void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }
    void clear(const Color& color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    std::optional<Event> poll_event();

    void display() { _sf_window.display(); }
    void close() { _sf_window.close(); }

private:
    sf::RenderWindow _sf_window;

private:
    template<typename... Args> void draw(Args&&... args) { _sf_window.draw(std::forward<Args>(args)...); }

    friend class PrimitiveRenderer;
};

} // namespace zth
