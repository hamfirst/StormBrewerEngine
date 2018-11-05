
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

#if defined(_WINDOWS) || defined(_MSC_VER)

  WIN32_FIND_DATAA ffd;

  auto hfind = FindFirstFileA(path, &ffd);
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

  auto dirent = opendir(path);
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

#if defined(_WINDOWS) || defined(_MSC_VER)

  WIN32_FIND_DATAA ffd;

  auto hfind = FindFirstFileA(path, &ffd);
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

  auto dirent = opendir(path);
  if(dirent == nullptr)
  {
    return files;
  }

  auto dp = readdir(dirent);
  while (dp != NULL)
  {
    if(GetFileExtensionForPath(dp->d_name) == extension)
    {
      files.emplace_back(dp->d_name);
    }

    dp = readdir(dirent);
  }

  closedir(dirent);

#endif

  return files;
}
