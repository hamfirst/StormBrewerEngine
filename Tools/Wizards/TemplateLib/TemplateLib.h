#pragma once


#include <cstdio>
#include <cstring>

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

std::optional<std::string> ReadFileIntoString(const std::string & file);
bool WriteStringToFile(const std::string & file, const std::string & file_data);

std::string GetRelativePath(const fs::path & root_path, const fs::path & target_dir);

std::string FormatTemplate(const std::string & templ,
  const std::unordered_map<std::string, std::string> & template_replacements);

std::optional<fs::path> FindCMakeFile(const fs::path & start_path, const fs::path & root_path);

//std::optional<std::pair<std::string, std::string>> FindVCXProjFiles(const fs::path & project_path);

enum class ProjectFileType
{
  kCPPFile,
  kHeaderFile,
  kReflFile,
};

std::string GetCMakePath(const std::string & rel_path, const std::string & file);
void InsertIntoCMakeFile(std::string & cmake_file, const std::string & file, ProjectFileType type);

//void InsertIntoVCXProjFile(std::string & vcxproj_file, const std::string & file, ProjectFileType type);

//void InsertIntoVCXProjFiltersFile(std::string & vcxproj_file, const std::string & file, ProjectFileType type);

bool WriteTemplate(const fs::path & target_file, const fs::path & template_file,
  const std::unordered_map<std::string, std::string> & template_replacements);

bool GitAddFile(const fs::path & target_file, const fs::path & root_path);
bool GitFinalize();