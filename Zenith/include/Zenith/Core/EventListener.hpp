#pragma once

namespace zth {

class Event;

class EventListener
{
public:
    virtual ~EventListener() = default;

    virtual void on_event(const Event& event) = 0;
};

} // namespace zth
