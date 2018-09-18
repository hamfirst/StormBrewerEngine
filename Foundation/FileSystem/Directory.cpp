
#include "Foundation/Common.h"
#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/Path.h"

#if defined(_WINDOWS) || defined(_MSC_VER)
#include <windows.h>
#else

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

#endif

  return files;
}
