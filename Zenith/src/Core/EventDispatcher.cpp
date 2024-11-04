#include "Zenith/Core/EventDispatcher.hpp"

namespace zth {

void EventDispatcher::register_listener(EventListener& listener)
{
    for (const auto& event_type : event_type_enumerations)
        register_listener(event_type, listener);
}

void EventDispatcher::register_listener(EventType event_type, EventListener& listener)
{
    auto& listeners = _listeners_map[event_type];
    listeners.push_back(&listener);
}

void EventDispatcher::deregister_listener(EventType event_type, const EventListener& listener)
{
    auto& listeners = _listeners_map[event_type];
    std::erase(listeners, &listener);
}

void EventDispatcher::deregister_listener(const EventListener& listener)
{
    for (auto& listeners : _listeners_map | std::views::values)
        std::erase(listeners, &listener);
}

void EventDispatcher::dispatch(const Event& event, double delta_time)
{
    // TODO:
    // modifying listeners map during iterating over listeners will invalidate the iterators
    // we should probably collect all the event listeners into a vector before iterating over
    // them and calling on_event

    const auto& listeners = _listeners_map[event.type()];

    for (const auto& listener : listeners)
        listener->on_event(event, delta_time);
}

} // namespace zth
