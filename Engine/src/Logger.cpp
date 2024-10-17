#include "Logger.h"

#include "FileIo.h"

Logger::Logger(LogTarget log_target, const std::filesystem::path& log_file_path = "") : log_target(log_target)
{
    if (std::filesystem::exists(log_file_path))
        this->log_file_path = log_file_path;
    else
        this->log_file_path = {};
}

void Logger::log(std::string_view message, LogSeverity severity) const
{
    if (log_target & LogTarget::Console)
    {
        switch (severity)
        {
        case LogSeverity::Notification:
            log_notification("{}", message);
            break;
        case LogSeverity::Warning:
            log_warning("{}", message);
            break;
        case LogSeverity::Error:
            log_error("{}", message);
            break;
        }
    }

    if ((log_target & LogTarget::File) && log_file_path)
        append_to_file(log_file_path.value(), message);
}
