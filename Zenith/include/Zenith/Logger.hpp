#pragma once

#include <filesystem>
#include <format>
#include <string_view>

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
    explicit Logger();
    explicit Logger(const LoggerSpec& spec);
    explicit Logger(LoggerSpec&& spec);
    explicit Logger(LogTarget log_target);
    explicit Logger(LogTarget log_target, const std::filesystem::path& log_file_path);
    explicit Logger(LogTarget log_target, std::filesystem::path&& log_file_path);

    inline void log_notification(std::string_view message) const;
    inline void log_warning(std::string_view message) const;
    inline void log_error(std::string_view message) const;
    template<typename... Args> void log_notification(std::format_string<Args...>&& format, Args&&... args) const;
    template<typename... Args> void log_warning(std::format_string<Args...>&& format, Args&&... args) const;
    template<typename... Args> void log_error(std::format_string<Args...>&& format, Args&&... args) const;

    static inline void print_notification(std::string_view message);
    static inline void print_warning(std::string_view message);
    static inline void print_error(std::string_view message);
    template<typename... Args> static void print_notification(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> static void print_warning(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> static void print_error(std::format_string<Args...>&& format, Args&&... args);

private:
    void log(LogSeverity severity, std::string_view message) const;

    template<typename... Args>
    void log(LogSeverity severity, std::format_string<Args...>&& format, Args&&... args) const;
};

} // namespace zth

#include "Logger.inl"
