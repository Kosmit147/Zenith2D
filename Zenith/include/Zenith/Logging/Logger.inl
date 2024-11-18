#pragma once

#include <iostream>
#include <print>
#include <utility>

namespace zth {

namespace ansi_colors {
inline auto red = "\x1b[31m";
inline auto yellow = "\x1b[33m";
inline auto white = "\x1b[37m";
inline auto reset = "\x1b[0m";
} // namespace ansi_colors

inline void Logger::log_notification(std::string_view message)
{
    log(LogSeverity::Notification, message);
}

inline void Logger::log_warning(std::string_view message)
{
    log(LogSeverity::Warning, message);
}

inline void Logger::log_error(std::string_view message)
{
    log(LogSeverity::Error, message);
}

template<typename... Args> void Logger::log_notification(std::format_string<Args...>&& format, Args&&... args)
{
    log(LogSeverity::Notification, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
}

template<typename... Args> void Logger::log_warning(std::format_string<Args...>&& format, Args&&... args)
{
    log(LogSeverity::Warning, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
}

template<typename... Args> void Logger::log_error(std::format_string<Args...>&& format, Args&&... args)
{
    log(LogSeverity::Error, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
}

inline void Logger::print_notification(std::string_view message)
{
    std::cout << message.data() << '\n';
}

inline void Logger::print_warning(std::string_view message)
{
    std::cout << ansi_colors::yellow;
    std::cout << message.data() << '\n';
    std::cout << ansi_colors::reset;
}

inline void Logger::print_error(std::string_view message)
{
    std::cout << ansi_colors::red;
    std::cout << message.data() << '\n';
    std::cout << ansi_colors::reset;
}

template<typename... Args> void Logger::print_notification(std::format_string<Args...>&& format, Args&&... args)
{
    std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
}

template<typename... Args> void Logger::print_warning(std::format_string<Args...>&& format, Args&&... args)
{
    std::cout << ansi_colors::yellow;
    std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    std::cout << ansi_colors::reset;
}

template<typename... Args> void Logger::print_error(std::format_string<Args...>&& format, Args&&... args)
{
    std::cout << ansi_colors::red;
    std::println(stderr, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    std::cout << ansi_colors::reset;
}

template<typename... Args>
void Logger::log(LogSeverity severity, std::format_string<Args...>&& format, Args&&... args)
{
    auto message = std::format(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    log(severity, message);
}

} // namespace zth
