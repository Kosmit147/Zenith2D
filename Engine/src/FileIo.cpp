#include "FileIo.h"

#include <fstream>
#include <utility>

std::optional<std::stringstream> read_from_file(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) [[unlikely]]
        return {};

    std::ifstream file(path);
    std::stringstream stream;

    auto file_buf = file.rdbuf();

    if (!file_buf) [[unlikely]]
        return {};

    stream << file_buf << '\0';

    if (!stream.good()) [[unlikely]]
        return {};

    return std::optional<std::stringstream>{ std::move(stream) };
}

bool write_to_file(const std::filesystem::path& path, std::string_view content)
{
    std::ofstream file(path);

    if (!file.good()) [[unlikely]]
        return false;

    file << content.data();

    if (!file.good()) [[unlikely]]
        return false;

    return true;
}

bool append_to_file(const std::filesystem::path& path, std::string_view content)
{
    std::ofstream file(path, std::ios::app);

    if (!file.good()) [[unlikely]]
        return false;

    file << content.data();

    if (!file.good()) [[unlikely]]
        return false;

    return true;
}
