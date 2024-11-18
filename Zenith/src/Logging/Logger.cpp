#include "Zenith/Logging/Logger.hpp"

#include "Zenith/Filesystem/FileIo.hpp"

namespace zth {

Logger::Logger() : log_target(LogTarget::Console) {}

Logger::Logger(const LoggerSpec& spec) : log_target(spec.target)
{
    if (spec.log_file_path)
        set_log_file_path(spec.log_file_path.value());
}

Logger::Logger(LogTarget log_target) : log_target(log_target) {}

Logger::Logger(LogTarget log_target, const std::filesystem::path& log_file_path) : log_target(log_target)
{
    set_log_file_path(log_file_path);
}

void Logger::set_log_file_path(const std::filesystem::path& log_file_path)
{
    _file.open(log_file_path);
}

void Logger::log(LogSeverity severity, std::string_view message)
{
    if (has_flag(log_target, LogTarget::Console))
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

    if (has_flag(log_target, LogTarget::File))
    {
        if (_file.is_open())
            _file << message << '\n';
        else
            print_error("Failed to log to file. Log file is not opened.");
    }
}

} // namespace zth
