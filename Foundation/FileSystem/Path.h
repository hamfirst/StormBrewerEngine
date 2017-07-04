#pragma once

#include <string>

bool ConvertToCanonicalPath(std::string & path, const std::string & root_path);
std::string GetCanonicalRootPath();
std::string GetFullPath(const std::string & path, const std::string & root_path);

std::string GetFileNameForCanonicalPath(const std::string & path);
std::string GetFileStemForCanonicalPath(const std::string & path);
std::string GetFileExtensionForCanonicalPath(const std::string & path);

