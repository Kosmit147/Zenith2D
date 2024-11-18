#pragma once

#include <filesystem>
#include <format>
#include <fstream>
#include <optional>
#include <string_view>

#include "Zenith/Utility/EnumFlags.hpp"
#include "Zenith/Utility/GlobalAccessPtr.hpp"

namespace zth {

enum class LogSeverity
{
    Notification,
    Warning,
    Error,
};

enum class LogTarget
{
    None = 0,
    Console = 1 << 0,
    File = 1 << 1,
    ConsoleAndFile = Console | File,
};

ZTH_MAKE_ENUM_FLAGS(LogTarget);

struct LoggerSpec
{
    LogTarget target = LogTarget::Console;
    std::optional<std::filesystem::path> log_file_path = std::nullopt;
};

class Logger
{
public:
    LogTarget log_target;

public:
    explicit Logger();
    explicit Logger(const LoggerSpec& spec);
    explicit Logger(LogTarget log_target);
    explicit Logger(LogTarget log_target, const std::filesystem::path& log_file_path);

    void set_log_file_path(const std::filesystem::path& log_file_path);

    inline void log_notification(std::string_view message);
    inline void log_warning(std::string_view message);
    inline void log_error(std::string_view message);
    template<typename... Args> void log_notification(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> void log_warning(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> void log_error(std::format_string<Args...>&& format, Args&&... args);

    static inline void print_notification(std::string_view message);
    static inline void print_warning(std::string_view message);
    static inline void print_error(std::string_view message);
    template<typename... Args> static void print_notification(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> static void print_warning(std::format_string<Args...>&& format, Args&&... args);
    template<typename... Args> static void print_error(std::format_string<Args...>&& format, Args&&... args);

    friend class GlobalAccessPtr<Logger>;

private:
    std::ofstream _file{};

private:
    void log(LogSeverity severity, std::string_view message);

    template<typename... Args>
    void log(LogSeverity severity, std::format_string<Args...>&& format, Args&&... args);
};

inline GlobalAccessPtr<Logger> logger;

} // namespace zth

#include "Logger.inl"
