#include "Logger.h"

#include "FileIo.h"

Logger::Logger(bool log_to_console, const std::filesystem::path& log_file_path)
	: log_to_console(log_to_console)
{
    if (std::filesystem::exists(log_file_path))
		this->log_file_path = log_file_path;
    else
        this->log_file_path = {};
}

void Logger::log(std::string_view message, LogSeverity severity) const
{
    if (log_to_console)
    {
		switch (severity)
		{
		case LogSeverity::Notification:
			log_notification(message);
			break;
		case LogSeverity::Warning:
			log_warning(message);
			break;
		case LogSeverity::Error:
			log_error(message);
			break;
		}
    }

	if (log_file_path)
		write_to_file(log_file_path.value(), message);
}

