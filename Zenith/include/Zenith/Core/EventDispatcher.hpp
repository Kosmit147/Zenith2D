#pragma once

#include <map>
#include <vector>

#include "Zenith/Platform/Event.hpp"

namespace zth {

class EventListener;

class EventDispatcher
{
public:
    void register_listener(EventListener& listener);
    void register_listener(EventType event_type, EventListener& listener);
    void deregister_listener(EventType event_type, const EventListener& listener);
    void deregister_listener(const EventListener& listener);
    void dispatch(const Event& event, double delta_time);

private:
    std::map<EventType, std::vector<EventListener*>> _listeners_map;
};

} // namespace zth
