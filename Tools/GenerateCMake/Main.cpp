
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;


struct DirectoryFiles
{
  std::vector<fs::path> m_Files;
  std::vector<fs::path> m_Directories;
};

struct ProjectFiles
{
  std::vector<std::string> m_CPPFiles;
  std::vector<std::string> m_HeaderFiles;
  std::vector<std::string> m_ReflFiles;
  std::vector<std::string> m_NatvisFiles;
  std::string m_PCHFile;
};

struct GenerateOptions
{
  bool m_QTProj = false;
  bool m_IncludePlatformFiles = false;
  bool m_Refl = false;
  bool m_Placeholder = false;
  bool m_PCH = false;
};


bool FindPlatformString(const std::string & file_path, const std::string & platform)
{
  return file_path.find(platform) != std::string::npos;
}

bool IsWebPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "web");
}

bool IsWindowsPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "windows");
}

bool IsWinRTPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "winrt");
}

bool IsLinuxPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "linux");
}

bool IsMacOSPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "osx");
}

bool IsAndroidOSPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "android");
}

bool IsIOSPlatformFile(const std::string & file_path)
{
  return FindPlatformString(file_path, "ios");
}

bool IsAnyPlatformFile(const std::string & file_path)
{
  return IsWebPlatformFile(file_path) ||
         IsWindowsPlatformFile(file_path) ||
         IsWinRTPlatformFile(file_path) ||
         IsLinuxPlatformFile(file_path) ||
         IsMacOSPlatformFile(file_path) ||
         IsAndroidOSPlatformFile(file_path) ||
         IsIOSPlatformFile(file_path);
}

void ProcessDirectory(const fs::path & p, DirectoryFiles & files)
{
  for (auto && itr : fs::directory_iterator(p))
  {
    auto status = itr.status();
    if (fs::is_directory(status))
    {
      files.m_Directories.emplace_back(itr.path());
    }
    else if (fs::is_regular_file(status))
    {
      files.m_Files.emplace_back(itr.path());
    }
  }
}

std::pair<bool, fs::path> HasProjectFile(DirectoryFiles & dir)
{
  for (auto & file : dir.m_Files)
  {
    auto filename = file.filename().string();
    if (filename == "CMakeLists.gen")
    {
      return std::make_pair(true, file);
    }
  }

  return std::make_pair(false, fs::path{});
}

void ProcessOption(const std::string & option, GenerateOptions & out)
{
  if (option == "qt")
  {
    out.m_QTProj = true;
  }

  if (option == "platform")
  {
    out.m_IncludePlatformFiles = true;
  }

  if (option == "refl")
  {
    out.m_Refl = true;
  }

  if (option == "placeholder")
  {
    out.m_Placeholder = true;
  }

  if (option == "pch")
  {
    out.m_PCH = true;
  }
}

GenerateOptions ReadGenerateOptions(const fs::path & path)
{
  std::ifstream options_file;
  options_file.open(path.c_str());

  GenerateOptions options;

  std::string option;
  while(!options_file.eof())
  {
    char c = options_file.get();
    if (c == std::ifstream::traits_type::eof())
    {
      break;
    }

    if(c == '\r' || c == '\n')
    {
      ProcessOption(option, options);
      option.clear();
    }
    else
    {
      option += c;
    }
  }

  ProcessOption(option, options);
  return options;
}

bool IsReservedDirectoryName(const std::string & dir_name)
{
  if (dir_name[0] == '.')
  {
    return true;
  }

  if(dir_name == "Debug" ||
     dir_name == "Release" ||
     dir_name == "x86" ||
     dir_name == "x64" ||
     dir_name == "Assets" ||
     dir_name == "Bin")
  {
    return true;
  }

  return false;
}

void GatherProjectFiles(const DirectoryFiles & dir, const std::string & base_path,
        ProjectFiles & files, const GenerateOptions & options)
{
  for (auto & file : dir.m_Files)
  {
    auto ext = file.extension().string();

    if (options.m_QTProj && file.string().find("GeneratedFiles") != std::string::npos)
    {
      continue;
    }

    auto proj_file_path = base_path.length() > 0 ? base_path + '/' + file.filename().string() : file.filename().string();
    if (ext == ".cpp" || ext == ".c" || ext == ".qrc" || ext == ".ui")
    {
      auto stem = file.stem().string();
      if (options.m_QTProj && (stem.substr(0, 4) == "moc_" || stem.substr(0, 4) == "qrc_"))
      {
        continue;
      }

      files.m_CPPFiles.push_back(proj_file_path);
    }
    else if (ext == ".h")
    {
      auto stem = file.stem().string();
      if (options.m_QTProj && (stem.substr(0, 3) == "ui_"))
      {
        continue;
      }

      files.m_HeaderFiles.push_back(proj_file_path);

      auto filename = file.filename().string();
      if (filename.length() > 7 && filename.substr(filename.length() - 7) == ".refl.h")
      {
        files.m_ReflFiles.push_back(proj_file_path);
      }

      if (filename.find("Common.h") != std::string::npos)
      {
        files.m_PCHFile = filename;
      }
    }
    else if (ext == ".natvis")
    {
      files.m_NatvisFiles.push_back(proj_file_path);
    }
  }
}

template <typename Callback>
void WritePlatformFileList(std::ofstream & cmake_file, const std::string & option, const std::string & define, const std::string & dir, 
  const std::string & project_name, const std::string & relative_root, ProjectFiles & files, bool include_freetype, Callback && callback)
{
  cmake_file << "if (" + option + ")\n";
  cmake_file << "  add_definitions(-D" + define + ")\n";
  cmake_file << "  include_directories(${PROJECT_SOURCE_DIR}/External/" + dir + ")\n";

  if (include_freetype)
  {
    cmake_file << "  include_directories(/usr/include/freetype2)\n";
  }

  cmake_file << "  set(PLATFORM_SRC_" + project_name + " \n";
  for (auto & file : files.m_CPPFiles)
  {
    if (callback(file))
    {
      cmake_file << "            " + file + "\n";
    }
  }

  cmake_file << "            )\n\n";
  cmake_file << "set(PLATFORM_HEADER_" + project_name + " \n";

  for (auto & file : files.m_HeaderFiles)
  {
    if (callback(file))
    {
      cmake_file << "            " + file + "\n";
    }
  }

  cmake_file << "            )\n";
  cmake_file << "endif()\n";
}

void FinalizeProject(const fs::path & p, const fs::path & project_file, const std::string & relative_root,
        ProjectFiles & files, const GenerateOptions & options)
{
  auto project_name = project_file.parent_path().filename().string();

  std::cout << "Project root: " << p << "\n";
  std::cout << "Project name: " << project_name << "\n";
  std::cout << "Relative root: " << relative_root << "\n";
  std::cout << "Qt Project: " << (options.m_QTProj ? "Yes" : "No") << "\n";
  std::cout << "Include Platform Files: " << (options.m_IncludePlatformFiles ? "Yes" : "No") << "\n";
  std::cout << "Include CMake Placeholder: " << (options.m_Placeholder ? "Yes" : "No") << "\n";
  std::cout << "Include Refl Options: " << (options.m_Refl ? "Yes" : "No") << "\n";
  std::cout << "Create PCH: " << (options.m_PCH ? "Yes" : "No") << "\n";

  if (options.m_PCH)
  {
    std::cout << "PCH File: " << files.m_PCHFile << "\n";
  }

  std::cout << "Project headers:\n";
  for (auto & file : files.m_HeaderFiles)
  {
    std::cout << "  " << file << "\n";
  }

  std::cout << "Project cpps:\n";
  for (auto & file : files.m_CPPFiles)
  {
    std::cout << "  " << file << "\n";
  }

  std::cout << "\n";

  auto cmake_file_path = p / "CMakeLists.txt";
  std::ofstream cmake_file;
  cmake_file.open(cmake_file_path.c_str());

  cmake_file << "cmake_minimum_required(VERSION 3.1.0)\n\n";
  cmake_file << "include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/External ${PROJECT_SOURCE_DIR}/StormTech ${PROJECT_SOURCE_DIR}/Tools ${PROJECT_SOURCE_DIR}/Shared ${PROJECT_SOURCE_DIR}/Project)\n";
  cmake_file << "set(CMAKE_CXX_STANDARD 17)\n\n";

  if (options.m_PCH && files.m_PCHFile.size() > 0)
  {
    cmake_file << "include(\"${PROJECT_SOURCE_DIR}/CMake/cotire.cmake\")\n\n";
  }

  if (options.m_QTProj)
  {
    cmake_file << "set(CMAKE_AUTOMOC ON)\n";
    cmake_file << "set(CMAKE_AUTOUIC ON)\n";
    cmake_file << "set(CMAKE_AUTORCC ON)\n";
    cmake_file << "cmake_policy(SET CMP0071 OLD)\n";
    cmake_file << "find_package(Qt5 REQUIRED COMPONENTS Core Widgets)\n";
    cmake_file << "include_directories(${Qt5Widgets_INCLUDE_DIRS})\n";
    cmake_file << "set(CMAKE_POSITION_INDEPENDENT_CODE ON)\n";
  }

  cmake_file << "set(GENERIC_SRC_" + project_name + " \n";

  for (auto & file : files.m_CPPFiles)
  {
    if (!IsAnyPlatformFile(file))
    {
      cmake_file << "            " + file + "\n";
    }
  }

  if(options.m_Placeholder)
  {
    cmake_file << "            #CPP_PLACEHOLDER\n";
  }

  cmake_file << "            )\n\n";

  cmake_file << "set(GENERIC_HEADER_" + project_name + " \n";

  for (auto & file : files.m_HeaderFiles)
  {
    if (!IsAnyPlatformFile(file))
    {
      cmake_file << "            " + file + "\n";
    }
  }

  if(options.m_Placeholder)
  {
    cmake_file << "            #HEADER_PLACEHOLDER\n";
  }

  cmake_file << "            )\n\n";

  if(options.m_Refl)
  {
    cmake_file << "set(GENERIC_REFL_" + project_name + " \n";

    for (auto &file : files.m_ReflFiles)
    {
      if (!IsAnyPlatformFile(file))
      {
        cmake_file << "            " + file + "\n";
      }
    }

    if(options.m_Placeholder)
    {
      cmake_file << "            #REFL_PLACEHOLDER\n";
    }

    cmake_file << "            )\n\n";
  }

  if(options.m_IncludePlatformFiles)
  {
    WritePlatformFileList(cmake_file, "MSVC", "_WINDOWS", "Windows", project_name, relative_root, files, false,
                          [](const std::string &file)
                          { return IsWindowsPlatformFile(file); });
    WritePlatformFileList(cmake_file, "WEB", "_WEB", "Web", project_name, relative_root, files, false,
                          [](const std::string &file)
                          { return IsWebPlatformFile(file); });
    WritePlatformFileList(cmake_file, "IOS", "_IOS", "IOS", project_name, relative_root, files, false,
                          [](const std::string &file)
                          { return IsIOSPlatformFile(file); });
    WritePlatformFileList(cmake_file, "APPLE AND NOT IOS", "_MACOS", "MacOS", project_name, relative_root, files, true,
                          [](const std::string &file)
                          { return IsMacOSPlatformFile(file); });
    WritePlatformFileList(cmake_file, "ANDROID", "_ANDROID", "Android", project_name, relative_root, files, false,
                          [](const std::string &file)
                          { return IsAndroidOSPlatformFile(file); });
    WritePlatformFileList(cmake_file, "UNIX AND NOT APPLE", "_LINUX", "Linux", project_name, relative_root, files, true,
                          [](const std::string &file)
                          { return IsLinuxPlatformFile(file); });
    cmake_file << "\n\n";
  }

  if(options.m_Refl)
  {
    cmake_file << "foreach(REFL_FILE ${GENERIC_REFL_" + project_name + "})\n";
    cmake_file << "  string(REPLACE \".refl.h\" \".refl.meta.h\" META_FILE ${REFL_FILE})\n";
    cmake_file << "  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${META_FILE}\n";
    cmake_file << "                     COMMAND stormrefl ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE} -- -DSTORM_REFL_PARSE -D_CRT_SECURE_NO_WARNINGS -std=c++17 -x c++ -Wno-pragma-once-outside-header -I${CMAKE_CURRENT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/StormTech -I${PROJECT_SOURCE_DIR}/Tools -I${PROJECT_SOURCE_DIR}/Shared -I${PROJECT_SOURCE_DIR}/Project -I${PROJECT_SOURCE_DIR}/External -I${CLANG_HEADER_PATH} -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS\n";
    cmake_file << "                     MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE}\n";
    cmake_file << "                     IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/${REFL_FILE})\n";
    cmake_file << "endforeach()\n\n";
  }

  if(options.m_IncludePlatformFiles)
  {
    cmake_file << "add_library(" + project_name + " STATIC ${GENERIC_SRC_" + project_name + "} ${PLATFORM_SRC_" + project_name + "}\n";
    cmake_file << "            ${GENERIC_HEADER_" + project_name + "} ${PLATFORM_HEADER_" + project_name + "})\n";
    cmake_file << "source_group(TREE \"${CMAKE_CURRENT_SOURCE_DIR}\" FILES ${GENERIC_SRC_" + project_name + "} ${PLATFORM_SRC_" + project_name + "}\n";
    cmake_file << "            ${GENERIC_HEADER_" + project_name + "} ${PLATFORM_HEADER_" + project_name + "})\n\n";
  }
  else
  {
    cmake_file << "add_library(" + project_name + " STATIC ${GENERIC_SRC_" + project_name + "} " "${GENERIC_HEADER_" + project_name + "})\n";
    cmake_file << "source_group(TREE \"${CMAKE_CURRENT_SOURCE_DIR}\" FILES ${GENERIC_SRC_" + project_name + "} " "${GENERIC_HEADER_" + project_name + "})\n\n";
  }

  if (files.m_NatvisFiles.size() > 0)
  {
    cmake_file << "\n";
    cmake_file << "if(MSVC)\n";
    for (auto & file : files.m_NatvisFiles)
    {
      cmake_file << "  target_sources(" + project_name + " INTERFACE $<INSTALL_INTERFACE:" + file + "> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/" + file + ">)\n";
    }

    cmake_file << "endif()\n\n";
  }


  if (options.m_PCH && files.m_PCHFile.size() > 0)
  {
    cmake_file << "set_target_properties(" + project_name + " PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT " + files.m_PCHFile + ")\n";
    cmake_file << "cotire(" + project_name + ")\n";
  }

  cmake_file.close();
}

void ProcessProjectFolder(const fs::path & p, const std::string & base_path, const std::string & relative_root,
        ProjectFiles * files, const GenerateOptions & options)
{
  if (IsReservedDirectoryName(p.filename().string()))
  {
    return;
  }

  DirectoryFiles dir_files;
  ProcessDirectory(p, dir_files);

  auto project_file = HasProjectFile(dir_files);
  if (project_file.first)
  {
    auto options = ReadGenerateOptions(project_file.second);

    ProjectFiles new_project_files;

    std::string new_base_path = "";
    GatherProjectFiles(dir_files, new_base_path, new_project_files, options);

    for (auto & sub_dir : dir_files.m_Directories)
    {
      auto new_path = base_path.length() > 0 ? base_path + "/" + sub_dir.filename().string() : sub_dir.filename().string();
      ProcessProjectFolder(sub_dir, new_path, "../" + relative_root, &new_project_files, options);
    }

    FinalizeProject(p, project_file.second, relative_root, new_project_files, options);
  }
  else if (files)
  {
    GatherProjectFiles(dir_files, base_path, *files, options);

    for (auto & sub_dir : dir_files.m_Directories)
    {
      auto new_path = base_path.length() > 0 ? base_path + "/" + sub_dir.filename().string() : sub_dir.filename().string();
      ProcessProjectFolder(sub_dir, new_path, "../" + relative_root, files, options);
    }
  }
  else
  {
    for (auto & sub_dir : dir_files.m_Directories)
    {
      ProcessProjectFolder(sub_dir, "", "../" + relative_root, nullptr, options);
    }
  }
}

int main()
{
  ProcessProjectFolder(fs::current_path(), ".", ".", nullptr, {});
  return 0;
}


