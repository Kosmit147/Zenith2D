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

/**
 * @brief Structure representing the specifications for creating a window.
 */
struct WindowSpec
{
    std::string title; ///< The title of the window.
    Resolution resolution = { 800, 600 }; ///< The resolution of the window.
    bool fullscreen = false; ///< Whether the window should be in fullscreen mode.
    u32 frame_rate_limit = 60; ///< The maximum frame rate limit for the window.
};

/**
 * @brief A class that encapsulates a window using SFML's `RenderWindow`.
 * 
 * The `Window` class provides a simple interface for managing a window's lifecycle, including
 * event polling, rendering, and window management (open, close, resize, etc.).
 */
class Window
{
private:
    sf::RenderWindow _sf_window; ///< The underlying SFML window object.

public:
    Renderer renderer{ _sf_window }; ///< The renderer used to draw to the window.
    Color clear_color = Color::black; ///< The default color used to clear the window.

public:
    /**
     * @brief Destructor that cleans up the window resources.
     */
    ~Window() = default;

    /**
     * @brief Deleted copy constructor and assignment operator to prevent copying the window.
     */
    ZTH_NO_COPY_NO_MOVE(Window)

    /**
     * @brief Checks if the window is open.
     * 
     * @return `true` if the window is open, `false` otherwise.
     */
    bool is_open() const { return _sf_window.isOpen(); }

    /**
     * @brief Clears the window with the default clear color.
     */
    void clear() { _sf_window.clear(static_cast<sf::Color>(clear_color)); }

    /**
     * @brief Clears the window with a custom color.
     * 
     * @param color The color to clear the window with.
     */
    void clear(const Color& color) { _sf_window.clear(static_cast<sf::Color>(color)); }

    friend class Application; ///< Allows the `Application` class to create and manage a window.
    friend class Engine; ///< Allows the `Engine` class to create and manage a window.

private:
    /**
     * @brief Constructs a window with the given specifications.
     * 
     * @param spec The specifications for the window (title, resolution, etc.).
     */
    explicit Window(const WindowSpec& spec);

    /**
     * @brief Polls for events and returns them as an `Event` object.
     * 
     * @return An `optional<Event>` containing the polled event, or `nullopt` if no event is available.
     */
    std::optional<Event> poll_event();

    /**
     * @brief Displays the contents of the window.
     * This should be called after rendering to make the content visible.
     */
    void display() { _sf_window.display(); }

    /**
     * @brief Closes the window.
     */
    void close() { _sf_window.close(); }
};

} // namespace zth
