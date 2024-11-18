/**
 * @file EventListener.hpp
 * @brief Declares the EventListener interface for handling events.
 */

#pragma once

namespace zth {

class Event;

/**
 * @class EventListener
 * @brief Interface for classes that want to listen to and handle events.
 *
 * Classes that inherit from EventListener must implement the on_event method
 * to define their custom event handling logic.
 */
class EventListener
{
public:
    /**
     * @brief Virtual destructor for EventListener.
     */
    virtual ~EventListener() = default;

    /**
     * @brief Pure virtual function to handle events.
     * @param event The event to handle.
     */
    virtual void on_event(const Event& event) = 0;
};

} // namespace zth
