
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

  auto hfind = FindFirstFileA(dir_path.data(), &ffd);
  if (hfind == INVALID_HANDLE_VALUE)
  {
    return files;
  }

  while(true)
  {
    files.emplace_back(JoinPath(path, ffd.cFileName));

    if (FindNextFileA(hfind, &ffd) != 0)
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

  auto dp = readdir(dirent);
  while (dp != NULL)
  {
    files.emplace_back(dp->d_name);
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

  auto hfind = FindFirstFileA(dir_path.data(), &ffd);
  if (hfind == INVALID_HANDLE_VALUE)
  {
    return files;
  }

  while(true)
  {
    auto path = JoinPath(path, ffd.cFileName);
    if(GetFileExtensionForPath(path) == extension)
    {
      files.emplace_back(path);
    }

    if (FindNextFileA(hfind, &ffd) != 0)
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
