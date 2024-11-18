/**
 * @file Logger.hpp
 * @brief Defines the `Logger` class for managing logging to different targets (console and/or file).
 * 
 * This file provides the `Logger` class which allows logging messages with different severities 
 * (notification, warning, error). The logs can be directed to various targets, including the console 
 * and/or a file. The log file can be specified, and formatted messages can be logged.
 */

#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <optional>
#include <string_view>

#include "Zenith/Utility/EnumFlags.hpp"
#include "Zenith/Utility/GlobalAccessPtr.hpp"

namespace zth {

/**
 * @enum LogSeverity
 * @brief Represents the severity of a log message.
 * 
 * The `LogSeverity` enum defines the possible levels of severity for log messages:
 * - `Notification`: Informational messages.
 * - `Warning`: Messages indicating a potential issue.
 * - `Error`: Messages indicating a critical issue or failure.
 */
enum class LogSeverity
{
    Notification, ///< Informational message.
    Warning, ///< Warning message.
    Error, ///< Error message.
};

/**
 * @enum LogTarget
 * @brief Represents different logging targets (console, file, or both).
 * 
 * `LogTarget` defines where the log messages are sent:
 * - `None`: No logging target.
 * - `Console`: Log messages are sent to the console.
 * - `File`: Log messages are written to a file.
 * - `ConsoleAndFile`: Log messages are sent to both the console and a file.
 */
enum class LogTarget
{
    None = 0, ///< No logging target.
    Console = 1 << 0, ///< Log to console.
    File = 1 << 1, ///< Log to file.
    ConsoleAndFile = Console | File, ///< Log to both console and file.
};

/**
 * @brief Enables bitwise operations on `LogTarget`.
 * 
 * This macro allows for bitwise OR, AND, and other operations on `LogTarget` values.
 */
ZTH_MAKE_ENUM_FLAGS(LogTarget);

/**
 * @struct LoggerSpec
 * @brief Specifies the configuration for the `Logger`.
 * 
 * The `LoggerSpec` structure is used to configure the `Logger` class with options such as the log 
 * target (console, file, or both) and the file path for log storage.
 */
struct LoggerSpec
{
    LogTarget target = LogTarget::Console; ///< The target for the log messages.
    std::optional<std::filesystem::path> log_file_path = std::nullopt; ///< Optional file path for log storage.
};

/**
 * @class Logger
 * @brief Logs messages to different targets such as the console and/or a file.
 * 
 * The `Logger` class provides methods for logging messages with different severities (notification, 
 * warning, error). It supports multiple log targets, such as the console, a log file, or both.
 */
class Logger
{
public:
    LogTarget log_target; ///< The target(s) for logging.

public:
    /**
     * @brief Default constructor, initializes the `Logger` with console as the target.
     */
    explicit Logger();

    /**
     * @brief Initializes the `Logger` with the specified configuration.
     * 
     * @param spec The configuration specifying the log target and file path.
     */
    explicit Logger(const LoggerSpec& spec);

    /**
     * @brief Initializes the `Logger` with the specified log target.
     * 
     * @param log_target The target for logging (console, file, etc.).
     */
    explicit Logger(LogTarget log_target);

    /**
     * @brief Initializes the `Logger` with the specified log target and file path.
     * 
     * @param log_target The target for logging (console, file, etc.).
     * @param log_file_path The file path for storing log messages.
     */
    explicit Logger(LogTarget log_target, const std::filesystem::path& log_file_path);

    /**
     * @brief Sets the file path for storing log messages.
     * 
     * This method is used to specify a file path for logging if the target is set to file.
     * 
     * @param log_file_path The file path for the log file.
     */
    void set_log_file_path(const std::filesystem::path& log_file_path);

    /**
     * @brief Logs a notification message.
     * 
     * @param message The message to log.
     */
    inline void log_notification(std::string_view message);

    /**
     * @brief Logs a warning message.
     * 
     * @param message The message to log.
     */
    inline void log_warning(std::string_view message);

    /**
     * @brief Logs an error message.
     * 
     * @param message The message to log.
     */
    inline void log_error(std::string_view message);

    /**
     * @brief Logs a formatted notification message.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> void log_notification(std::format_string<Args...>&& format, Args&&... args);

    /**
     * @brief Logs a formatted warning message.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> void log_warning(std::format_string<Args...>&& format, Args&&... args);

    /**
     * @brief Logs a formatted error message.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> void log_error(std::format_string<Args...>&& format, Args&&... args);

    /**
     * @brief Prints a notification message to the console.
     * 
     * This method is static and logs the message directly to the console, regardless of the current 
     * `Logger` configuration.
     * 
     * @param message The message to print.
     */
    static inline void print_notification(std::string_view message);

    /**
     * @brief Prints a warning message to the console.
     * 
     * This method is static and logs the message directly to the console, regardless of the current 
     * `Logger` configuration.
     * 
     * @param message The message to print.
     */
    static inline void print_warning(std::string_view message);

    /**
     * @brief Prints an error message to the console.
     * 
     * This method is static and logs the message directly to the console, regardless of the current 
     * `Logger` configuration.
     * 
     * @param message The message to print.
     */
    static inline void print_error(std::string_view message);

    /**
     * @brief Prints a formatted notification message to the console.
     * 
     * This method is static and logs the formatted message directly to the console.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> static void print_notification(std::format_string<Args...>&& format, Args&&... args);

    /**
     * @brief Prints a formatted warning message to the console.
     * 
     * This method is static and logs the formatted message directly to the console.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> static void print_warning(std::format_string<Args...>&& format, Args&&... args);

    /**
     * @brief Prints a formatted error message to the console.
     * 
     * This method is static and logs the formatted message directly to the console.
     * 
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args> static void print_error(std::format_string<Args...>&& format, Args&&... args);

    friend class GlobalAccessPtr<Logger>; ///< Allows `GlobalAccessPtr<Logger>` to access private members.

private:
    std::ofstream _file{}; ///< The file stream for writing log messages to a file.

private:
    /**
     * @brief Logs a message with the specified severity.
     * 
     * @param severity The severity of the message.
     * @param message The message to log.
     */
    void log(LogSeverity severity, std::string_view message);

    /**
     * @brief Logs a formatted message with the specified severity.
     * 
     * @param severity The severity of the message.
     * @param format The format string.
     * @param args The arguments to format the string with.
     */
    template<typename... Args>
    void log(LogSeverity severity, std::format_string<Args...>&& format, Args&&... args);
};

/**
 * @brief Provides global access to the `Logger` instance.
 * 
 * The `logger` variable allows global access to the `Logger` instance for logging messages.
 */
inline GlobalAccessPtr<Logger> logger;

} // namespace zth
