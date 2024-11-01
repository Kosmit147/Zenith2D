#pragma once

#include "Event.hpp"
#include "Logger.hpp"
#include "Typedefs.hpp"
#include "Utility.hpp"
#include "Window.hpp"

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

    auto get_fps() const { return _fps; }

protected:
    WindowApi _window = WindowApi{ _internal_window };
    Logger _logger;

private:
    Window _internal_window;
    u32 _fps = 0;

private:
    virtual void on_update([[maybe_unused]] u64 delta_time) {}
    virtual void on_event([[maybe_unused]] const Event& event) {}
};

} // namespace zth
