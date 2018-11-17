
#include "Foundation/Common.h"
#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/Path.h"

#if defined(_WINDOWS) || defined(_MSC_VER)
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#endif

std::vector<std::string> GetFilesInDirectory(czstr path)
{
  std::vector<std::string> files;
  std::string dir_path = GetFullPath(path, GetCanonicalRootPath());

#if defined(_WINDOWS) || defined(_MSC_VER)

  WIN32_FIND_DATAA ffd;

  dir_path += "\\*";
  auto hfind = FindFirstFileA(dir_path.data(), &ffd);
  if (hfind == INVALID_HANDLE_VALUE)
  {
    return files;
  }

  auto root_path = GetCanonicalRootPath();

  while(true)
  {
    auto file_path = std::string(path) + '/' + ffd.cFileName;
    ConvertToCanonicalPath(file_path, root_path);

    files.emplace_back(file_path);

    if (FindNextFileA(hfind, &ffd) == 0)
    {
      break;
    }
  }

#else

  auto dirent = opendir(dir_path.data());
  if(dirent == nullptr)
  {
    return files;
  }

  auto root_path = GetCanonicalRootPath();

  auto dp = readdir(dirent);
  while (dp != NULL)
  {
    auto file_path = std::string(path) + '/' + dp->d_name;
    ConvertToCanonicalPath(file_path, root_path);

    files.emplace_back(file_path);
    dp = readdir(dirent);
  }

  closedir(dirent);

#endif

  return files;
}

std::vector<std::string> GetFilesInDirectory(czstr path, czstr extension)
{
  std::vector<std::string> files;
  std::string dir_path = GetFullPath(path, GetCanonicalRootPath());

#if defined(_WINDOWS) || defined(_MSC_VER)

  WIN32_FIND_DATAA ffd;

  dir_path += "\\*";
  auto hfind = FindFirstFileA(dir_path.data(), &ffd);
  if (hfind == INVALID_HANDLE_VALUE)
  {
    return files;
  }

  auto root_path = GetCanonicalRootPath();

  while(true)
  {
    if(GetFileExtensionForPath(ffd.cFileName) == extension)
    {
      auto file_path = std::string(path) + '/' + ffd.cFileName;
      ConvertToCanonicalPath(file_path, root_path);

      files.emplace_back(file_path);
    }

    if (FindNextFileA(hfind, &ffd) == 0)
    {
      break;
    }
  }

#else

  auto dirent = opendir(dir_path.data());
  if(dirent == nullptr)
  {
    return files;
  }

  auto root_path = GetCanonicalRootPath();

  auto dp = readdir(dirent);
  while (dp != NULL)
  {
    auto ext = GetFileExtensionForPath(dp->d_name);
    if(ext == extension)
    {
      auto file_path = std::string(path) + '/' + dp->d_name;
      ConvertToCanonicalPath(file_path, root_path);

      files.emplace_back(file_path);
    }

    dp = readdir(dirent);
  }

  closedir(dirent);

#endif

  return files;
}
