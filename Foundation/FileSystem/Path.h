#pragma once

#include <string>

bool ConvertToCanonicalPath(std::string & path, const std::string & root_path);
std::string GetCanonicalRootPath();
std::string GetFullPath(const std::string & path, const std::string & root_path);

std::string JoinPath(const std::string & path_part1, const std::string & path_part2);
bool CreateDirectory(const std::string & path);

std::string GetFileNameForCanonicalPath(const std::string & path);
std::string GetFileStemForCanonicalPath(const std::string & path);
std::string GetFileExtensionForCanonicalPath(const std::string & path);

