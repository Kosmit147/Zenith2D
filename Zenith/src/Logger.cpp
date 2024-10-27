#include "Logger.hpp"

#include "FileIo.hpp"

namespace zth {

Logger::Logger() : log_target(LogTarget::Console), log_file_path("") {}

Logger::Logger(const LoggerSpec& spec) : log_target(spec.target), log_file_path(spec.log_file_path) {}

Logger::Logger(LoggerSpec&& spec) : log_target(spec.target), log_file_path(std::move(spec.log_file_path)) {}

Logger::Logger(LogTarget log_target) : log_target(log_target), log_file_path("") {}

Logger::Logger(LogTarget log_target, const std::filesystem::path& log_file_path)
    : log_target(log_target), log_file_path(log_file_path)
{}

Logger::Logger(LogTarget log_target, std::filesystem::path&& log_file_path)
    : log_target(log_target), log_file_path(std::move(log_file_path))
{}

void Logger::log(LogSeverity severity, std::string_view message) const
{
    if (log_target & LogTarget::Console)
    {
        switch (severity)
        {
        case LogSeverity::Notification:
            print_notification(message);
            break;
        case LogSeverity::Warning:
            print_warning(message);
            break;
        case LogSeverity::Error:
            print_error(message);
            break;
        }
    }

    if (log_target & LogTarget::File)
    {
        if (!log_file_path.empty())
        {
            auto success = append_to_file_with_newline(log_file_path, message);

            if (!success)
                print_error("Failed to write to log file: {}.", log_file_path.string());
        }
        else
        {
            print_error("Log file path not set.");
        }
    }
}

} // namespace zth
