/**
 * @file Engine.hpp
 * @brief Declares the main engine class for the Zenith engine, managing the window, input, scene, and update loop.
 */

#pragma once

#include <memory>
#include "Zenith/Core/FrameCounter.hpp"
#include "Zenith/Core/Scene.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Input/Input.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/GlobalAccessPtr.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Updatable;
class EventListener;

/**
 * @class Engine
 * @brief The core of the Zenith engine, managing the main game loop, window, input, and scene changes.
 *
 * The Engine class is responsible for handling updates, events, and scene transitions. Only one instance of Engine should exist.
 */
class Engine
{
public:
    /// The window associated with the engine.
    Window window;

    /// Handles user input for the engine.
    Input input;

    /// Pointer to the active scene in the engine.
    std::unique_ptr<Scene> scene;

public:
    /**
     * @brief Destructor for the Engine class.
     */
    ~Engine();

    /// Prevents copying and moving of Engine instances.
    ZTH_NO_COPY_NO_MOVE(Engine)

    /**
     * @brief Gets the time in seconds between the last two frames.
     * @return The delta time as a double.
     */
    auto delta_time() const { return _delta_time; }

    /**
     * @brief Gets the current frames per second (FPS).
     * @return The FPS as an integer.
     */
    auto fps() const { return _frame_counter.get_fps(); }

    /**
     * @brief Queues a new scene to replace the current scene in the next frame.
     * @param new_scene A unique pointer to the new Scene.
     */
    void change_scene(std::unique_ptr<Scene> new_scene);

    friend class GlobalAccessPtr<Engine>;
    friend class Application;

private:
    /// The time difference between frames, calculated each update.
    double _delta_time = 0.0;

    /// Manages frame counting and FPS calculation.
    FrameCounter _frame_counter;

    /// Holds the new scene to be set in the next frame update, if any.
    std::unique_ptr<Scene> _queued_scene;

private:
    /**
     * @brief Constructs the Engine with specified window settings.
     * @param window_spec Specifications for the window, such as title and resolution.
     */
    explicit Engine(const WindowSpec& window_spec);

    /**
     * @brief Called during each update cycle.
     */
    void on_update();

    /**
     * @brief Processes a general event.
     * @param event The event data to handle.
     */
    void on_event(const Event& event);

    /**
     * @brief Processes an input-specific event.
     * @param event The input event data to handle.
     */
    void on_input_event(const Event& event);
};

/**
 * @brief Global access pointer to the engine instance.
 */
inline GlobalAccessPtr<Engine> engine;

} // namespace zth
