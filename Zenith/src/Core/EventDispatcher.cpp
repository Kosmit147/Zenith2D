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
    const auto& listeners = _listeners_map[event.type()];

    for (const auto& listener : listeners)
        listener->on_event(event, delta_time);
}

} // namespace zth
