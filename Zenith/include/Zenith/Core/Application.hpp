#pragma once

#include "Zenith/Core/EventDispatcher.hpp"
#include "Zenith/Core/FrameCounter.hpp"
#include "Zenith/Core/UpdateDispatcher.hpp"
#include "Zenith/Logging/Logger.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

struct ApplicationSpec
{
    WindowSpec window_spec = { .title = "Application", .resolution = { 800, 600 } };
    LoggerSpec logger_spec = { .target = LogTarget::Console };
};

class Application
{
public:
    explicit Application(const ApplicationSpec& spec = {});
    virtual ~Application() = default;
    ZTH_NO_COPY_NO_MOVE(Application)

    void run();

    auto get_fps() const { return _frame_counter.get_fps(); }

protected:
    WindowApi _window = WindowApi{ _internal_window };
    Logger _logger;
    // TODO: user shouldn't be able to call event dispatcher's dispatch function
    EventDispatcher _event_dispatcher;
    // TODO: user shouldn't be able to call update dispatcher's dispatch function
    UpdateDispatcher _update_dispatcher;

private:
    Window _internal_window;
    FrameCounter _frame_counter;

private:
    virtual void on_update([[maybe_unused]] double delta_time) {}
    virtual void on_event([[maybe_unused]] const Event& event, [[maybe_unused]] double delta_time) {}

    void handle_event(const Event& event, double delta_time);
};

} // namespace zth
