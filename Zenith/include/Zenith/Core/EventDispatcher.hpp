/**
 * @file EventDispatcher.hpp
 * @brief Declares the EventDispatcher class for managing event listeners and dispatching events.
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "Zenith/Platform/Event.hpp"

namespace zth {

class EventListener;

/**
 * @class EventDispatcher
 * @brief Manages registration and dispatching of events to registered listeners.
 *
 * The EventDispatcher class allows registering, deregistering, and notifying listeners for specific event types.
 */
class EventDispatcher
{
public:
    /**
     * @brief Registers an EventListener for all event types.
     * @param listener The listener to register.
     */
    void register_listener(EventListener& listener);

    /**
     * @brief Registers an EventListener for a specific event type.
     * @param event_type The type of event to listen for.
     * @param listener The listener to register.
     */
    void register_listener(EventType event_type, EventListener& listener);

    /**
     * @brief Deregisters an EventListener from a specific event type.
     * @param event_type The type of event to stop listening for.
     * @param listener The listener to deregister.
     */
    void deregister_listener(EventType event_type, const EventListener& listener);

    /**
     * @brief Deregisters an EventListener from all event types.
     * @param listener The listener to deregister.
     */
    void deregister_listener(const EventListener& listener);

    /**
     * @brief Dispatches an event to all registered listeners for the event's type.
     * @param event The event to dispatch.
     */
    void dispatch(const Event& event);

private:
    /// A map of event types to their respective lists of listeners.
    std::unordered_map<EventType, std::vector<EventListener*>> _listeners_map;
};

} // namespace zth
