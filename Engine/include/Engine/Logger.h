#pragma once

#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <string_view>
#include <utility>

#include "LoggingOptions.h"

namespace ansi_colors {
inline auto red = "\x1b[31m";
inline auto yellow = "\x1b[33m";
inline auto white = "\x1b[37m";
inline auto reset = "\x1b[0m";
} // namespace ansi_colors

class Logger
{
public:
    LogTarget log_target;
    std::optional<std::filesystem::path> log_file_path;

public:
    Logger(LogTarget log_target, const std::filesystem::path& log_file_path = "");

    void log(std::string_view message, LogSeverity severity) const;

private:
    template<typename... Args>
    inline void log_notification(std::format_string<Args...>&& format, Args&&... args) const
    {
        std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    };

    template<typename... Args>
    inline void log_warning(std::format_string<Args...>&& format, Args&&... args) const
    {
        std::cout << ansi_colors::yellow;
        std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
        std::cout << ansi_colors::reset;
    }

    template<typename... Args>
    inline void log_error(std::format_string<Args...>&& format, Args&&... args) const
    {
        std::cout << ansi_colors::red;
        std::println(stderr, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
        std::cout << ansi_colors::reset;
    }
};
