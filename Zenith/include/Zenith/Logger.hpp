#pragma once

#include <filesystem>
#include <format>
#include <iostream>
#include <print>
#include <string_view>
#include <utility>

#include "LoggingOptions.hpp"

namespace zth {

namespace ansi_colors {
inline auto red = "\x1b[31m";
inline auto yellow = "\x1b[33m";
inline auto white = "\x1b[37m";
inline auto reset = "\x1b[0m";
} // namespace ansi_colors

struct LoggerSpec
{
    LogTarget target = LogTarget::Console;
    std::filesystem::path log_file_path = "";
};

class Logger
{
public:
    LogTarget log_target;
    std::filesystem::path log_file_path;

public:
    inline Logger() : log_target(LogTarget::Console), log_file_path("") {}
    inline Logger(const LoggerSpec& spec) : log_target(spec.target), log_file_path(spec.log_file_path) {}
    inline Logger(LoggerSpec&& spec) : log_target(spec.target), log_file_path(std::move(spec.log_file_path)) {}
    inline Logger(LogTarget log_target) : log_target(log_target), log_file_path("") {}
    inline Logger(LogTarget log_target, const std::filesystem::path& log_file_path)
        : log_target(log_target), log_file_path(log_file_path)
    {}
    inline Logger(LogTarget log_target, std::filesystem::path&& log_file_path)
        : log_target(log_target), log_file_path(std::move(log_file_path))
    {}

    inline void log_notification(std::string_view message) const { log(LogSeverity::Notification, message); }

    template<typename... Args> inline void log_notification(std::format_string<Args...>&& format, Args&&... args) const
    {
        log(LogSeverity::Notification, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    }

    inline void log_warning(std::string_view message) const { log(LogSeverity::Warning, message); }

    template<typename... Args> inline void log_warning(std::format_string<Args...>&& format, Args&&... args) const
    {
        log(LogSeverity::Warning, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    }

    inline void log_error(std::string_view message) const { log(LogSeverity::Error, message); }

    template<typename... Args> inline void log_error(std::format_string<Args...>&& format, Args&&... args) const
    {
        log(LogSeverity::Error, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    }

    static inline void print_notification(std::string_view message) { std::cout << message.data() << '\n'; }

    template<typename... Args>
    static inline void print_notification(std::format_string<Args...>&& format, Args&&... args)
    {
        std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    };

    static inline void print_warning(std::string_view message)
    {
        std::cout << ansi_colors::yellow;
        std::cout << message.data() << '\n';
        std::cout << ansi_colors::reset;
    }

    template<typename... Args> static inline void print_warning(std::format_string<Args...>&& format, Args&&... args)
    {
        std::cout << ansi_colors::yellow;
        std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
        std::cout << ansi_colors::reset;
    }

    static inline void print_error(std::string_view message)
    {
        std::cout << ansi_colors::red;
        std::cout << message.data() << '\n';
        std::cout << ansi_colors::reset;
    }

    template<typename... Args> static inline void print_error(std::format_string<Args...>&& format, Args&&... args)
    {
        std::cout << ansi_colors::red;
        std::println(stderr, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
        std::cout << ansi_colors::reset;
    }

private:
    void log(LogSeverity severity, std::string_view message) const;

    template<typename... Args>
    inline void log(LogSeverity severity, std::format_string<Args...>&& format, Args&&... args) const
    {
        auto message = std::format(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);

        log(severity, message);
    }
};

} // namespace zth
