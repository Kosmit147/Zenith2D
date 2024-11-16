#pragma once

#include "Zenith/Logging/Logger.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/Utility.hpp"

#define ZTH_IMPLEMENT_APP(user_app)                                                                                    \
    namespace zth {                                                                                                    \
                                                                                                                       \
    Application* create_application()                                                                                  \
    {                                                                                                                  \
        return new user_app;                                                                                           \
    }                                                                                                                  \
    }

namespace zth {

struct ApplicationSpec
{
    WindowSpec window_spec = { .title = "Application", .resolution = { 800, 600 } };
    LoggerSpec logger_spec = { .target = LogTarget::Console };
};

// only one Application object should exist at any given time
class Application
{
public:
    virtual ~Application();
    ZTH_NO_COPY_NO_MOVE(Application)

    void run();

protected:
    explicit Application(const ApplicationSpec& spec = {});

private:
    virtual void on_update() {}
    virtual void on_event([[maybe_unused]] const Event& event) {}

    void handle_update();
    void handle_event(const Event& event);
};

} // namespace zth
