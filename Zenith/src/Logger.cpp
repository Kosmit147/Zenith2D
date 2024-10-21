#include "Logger.hpp"

#include "FileIo.hpp"

namespace zth {

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
