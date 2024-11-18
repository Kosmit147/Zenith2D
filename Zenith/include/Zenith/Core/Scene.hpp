/**
 * @file Scene.hpp
 * @brief Declares the Scene class, which serves as a base class for managing objects and behaviors within a game scene.
 */

#pragma once

#include "Zenith/Core/EventDispatcher.hpp"
#include "Zenith/Core/Updater.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Drawable;
class Animatable;

/**
 * @class Scene
 * @brief The base class for a scene, managing updatable, event-listening, drawable, and animatable objects.
 *
 * The Scene class provides methods to register and deregister objects of various types (e.g., updatable, drawable).
 * It also contains event dispatching and updating mechanisms for objects within the scene.
 */
class Scene
{
public:
    /**
     * @brief Virtual destructor for Scene.
     */
    virtual ~Scene() = default;

    /// Prevents copying and moving of Scene instances.
    ZTH_NO_COPY_NO_MOVE(Scene)

    friend class Engine;

protected:
    /**
     * @brief Protected default constructor for Scene.
     */
    explicit Scene() = default;

    /**
     * @brief Registers an updatable object with the scene.
     * @param updatable The updatable object to register.
     */
    void register_updatable(Updatable& updatable);

    /**
     * @brief Deregisters an updatable object from the scene.
     * @param updatable The updatable object to deregister.
     */
    void deregister_updatable(const Updatable& updatable);

    /**
     * @brief Registers an event listener for all event types.
     * @param listener The event listener to register.
     */
    void register_event_listener(EventListener& listener);

    /**
     * @brief Registers an event listener for a specific event type.
     * @param event_type The event type to listen for.
     * @param listener The event listener to register.
     */
    void register_event_listener(EventType event_type, EventListener& listener);

    /**
     * @brief Deregisters an event listener from a specific event type.
     * @param event_type The event type to stop listening for.
     * @param listener The event listener to deregister.
     */
    void deregister_event_listener(EventType event_type, const EventListener& listener);

    /**
     * @brief Deregisters an event listener from all event types.
     * @param listener The event listener to deregister.
     */
    void deregister_event_listener(const EventListener& listener);

    /**
     * @brief Registers a drawable object with the scene.
     * @param drawable The drawable object to register.
     */
    void register_drawable(Drawable& drawable);

    /**
     * @brief Deregisters a drawable object from the scene.
     * @param drawable The drawable object to deregister.
     */
    void deregister_drawable(Drawable& drawable);

    /**
     * @brief Registers an animatable object with the scene.
     * @param animatable The animatable object to register.
     */
    void register_animatable(Animatable& animatable);

    /**
     * @brief Deregisters an animatable object from the scene.
     * @param animatable The animatable object to deregister.
     */
    void deregister_animatable(Animatable& animatable);

private:
    /// Updates all registered updatable objects.
    Updater _updater;

    /// Manages event listeners and dispatching of events.
    EventDispatcher _event_dispatcher;

    /// Stores registered drawable objects for rendering.
    std::vector<Drawable*> _drawables;

    /// Stores registered animatable objects.
    std::vector<Animatable*> _animatables;

private:
    /**
     * @brief Updates the scene, called once per frame.
     */
    void update();

    /**
     * @brief Dispatches an event to all registered listeners.
     * @param event The event to dispatch.
     */
    void dispatch_event(const Event& event);

    /**
     * @brief Called when the scene is loaded. Can be overridden by derived classes.
     */
    virtual void on_load() {}

    /**
     * @brief Called during each update cycle. Can be overridden by derived classes.
     */
    virtual void on_update() {}

    /**
     * @brief Called when an event occurs. Can be overridden by derived classes.
     * @param event The event to handle.
     */
    virtual void on_event([[maybe_unused]] const Event& event) {}
};

} // namespace zth
