/**
 * @file Application.hpp
 * @brief Declares the main application framework for the Zenith engine, including the Application class and its specifications.
 */

#pragma once

#include "Zenith/Logging/Logger.hpp"
#include "Zenith/Platform/Event.hpp"
#include "Zenith/Platform/Window.hpp"
#include "Zenith/Utility/Utility.hpp"

/**
 * @brief Macro to implement the user-defined application creation function.
 *
 * @param user_app The user's application class which inherits from Application.
 */
#define ZTH_IMPLEMENT_APP(user_app)                                                                                    \
    namespace zth {                                                                                                    \
                                                                                                                       \
    Application* create_application()                                                                                  \
    {                                                                                                                  \
        return new user_app;                                                                                           \
    }                                                                                                                  \
    }

namespace zth {

/**
 * @struct ApplicationSpec
 * @brief Holds specifications for configuring the Application, such as window and logging options.
 */
struct ApplicationSpec
{
    /// Specifications for the application window, including title and resolution.
    WindowSpec window_spec = { .title = "Application", .resolution = { 800, 600 } };
    /// Specifications for the application logger, specifying log target and level.
    LoggerSpec logger_spec = { .target = LogTarget::Console };
};

/**
 * @class Application
 * @brief The base class for any Zenith application. Manages the main loop and event handling.
 *
 * Only one instance of Application should exist at any given time.
 */
class Application
{
public:
    /**
     * @brief Virtual destructor for the Application class.
     */
    virtual ~Application();

    /// Prevent copying and moving of Application instances.
    ZTH_NO_COPY_NO_MOVE(Application)

    /**
     * @brief Starts the main application loop.
     */
    void run();

protected:
    /**
     * @brief Constructs an Application with specified settings.
     * @param spec Configuration options for the application.
     */
    explicit Application(const ApplicationSpec& spec = {});

private:
    /**
     * @brief Called during each update cycle. Can be overridden by derived classes.
     */
    virtual void on_update() {}

    /**
     * @brief Called when an event occurs. Can be overridden by derived classes.
     * @param event The event data to handle.
     */
    virtual void on_event([[maybe_unused]] const Event& event) {}

    /**
     * @brief Internal function to handle the update logic.
     */
    void handle_update();

    /**
     * @brief Internal function to handle incoming events.
     * @param event The event data to handle.
     */
    void handle_event(const Event& event);
};

} // namespace zth
