#include "FileIo.hpp"

#include <fstream>

namespace zth {

std::optional<std::stringstream> read_from_file(const std::filesystem::path& path)
{
    if (!exists(path)) [[unlikely]]
        return {};

    std::ifstream file(path);
    std::stringstream stream;

    auto file_buf = file.rdbuf();

    if (!file_buf) [[unlikely]]
        return {};

    stream << file_buf << '\0';

    if (!stream.good()) [[unlikely]]
        return {};

    return std::optional{ std::move(stream) };
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

bool append_to_file_with_newline(const std::filesystem::path& path, std::string_view content)
{
    std::ofstream file(path, std::ios::app);

    if (!file.good()) [[unlikely]]
        return false;

    file << content.data() << '\n';

    if (!file.good()) [[unlikely]]
        return false;

    return true;
}

} // namespace zth
