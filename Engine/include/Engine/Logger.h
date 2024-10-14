#pragma once

#include <print>
#include <format>
#include <filesystem>
#include <utility>
#include <string_view>
#include <optional>

namespace ansi_colors {
static const char* red = "\x1b[31m";
static const char* yellow = "\x1b[33m";
static const char* white = "\x1b[37m";
static const char* reset = "\x1b[0m";
} // namespace ansi_colors

template<typename... Args>
inline auto log_notification(std::format_string<Args...>&& format, Args&&... args) -> void
{
    std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
};

template<typename... Args>
inline auto log_warning(std::format_string<Args...>&& format, Args&&... args) -> void
{
    std::cout << ansi_colors::yellow;
    std::println(std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    std::cout << ansi_colors::reset;
}

template<typename... Args> inline auto log_error(std::format_string<Args...>&& format, Args&&... args) -> void
{
    std::cout << ansi_colors::red;
    std::println(stderr, std::forward<std::format_string<Args...>>(format), std::forward<Args>(args)...);
    std::cout << ansi_colors::reset;
}

enum class LogSeverity
{
    Notification,
    Warning,
    Error,
};

class Logger
{
public:
    Logger(bool log_to_console, const std::filesystem::path& log_file_path = "");

    void log(std::string_view message, LogSeverity severity) const;

public:
    bool log_to_console;
    std::optional<std::filesystem::path> log_file_path;
};