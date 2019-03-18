
#include "Foundation/Common.h"
#include "Foundation/FileSystem/Directory.h"
#include "Foundation/FileSystem/Path.h"

#if defined(_WINDOWS) || defined(_MSC_VER)
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#endif


DirectoryIterator::DirectoryIterator()
{

}

DirectoryIterator::DirectoryIterator(const char * dir)
{
#if defined(_WINDOWS) || defined(_MSC_VER)
  m_DirectoryHandle.push_back(std::make_pair(nullptr, dir));
  operator++();
#else

  auto dirent = opendir(dir);
  if(dirent == nullptr)
  {
    return;
  }

  m_DirectoryHandle.push_back(std::make_pair(dirent, dir));
  operator++();

#endif
}

bool DirectoryIterator::operator == (const DirectoryIterator & iterator) const
{
  return m_DirectoryHandle.size() == 0 && m_CurFile.size() == 0 && iterator.m_DirectoryHandle.size() == 0 && iterator.m_CurFile.size() == 0;
}

DirectoryIterator & DirectoryIterator::operator ++ ()
{
  if(m_DirectoryHandle.size() == 0)
  {
    m_CurFile.clear();
    return *this;
  }

  auto & dir_info = m_DirectoryHandle.back();

#if defined(_WINDOWS) || defined(_MSC_VER)

  WIN32_FIND_DATAA ffd;
  if(dir_info.first == nullptr)
  {
    auto hfind = FindFirstFileA(dir_info.second.c_str(), &ffd);
    if (hfind == INVALID_HANDLE_VALUE)
    {
      m_DirectoryHandle.pop_back();
      operator++();
      return *this;
    }

    dir_info.first = hfind;
  }
  else
  {;
    if (FindNextFileA(dir_info.first, &ffd) == false)
    {
      m_DirectoryHandle.pop_back();
      operator++();
      return *this;
    }
  }

  if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
  {
    auto new_dir = dir_info.second + '\\' + ffd.cFileName;
    m_DirectoryHandle.push_back(std::make_pair(nullptr, new_dir));
    operator++();
    return *this;
  }
  else if(ffd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
  {
    m_CurFile = dir_info.second + '\\' + ffd.cFileName;
  }

#else

  auto dirent = (DIR *)dir_info.first;
  auto dp = readdir(dirent);
  while (dp != NULL)
  {
    if(dp->d_type == DT_DIR)
    {
      auto new_dir = dir_info.second + '/' + dp->d_name;
      auto new_dirent = opendir(new_dir.c_str());

      if(new_dirent)
      {
        m_DirectoryHandle.push_back(std::make_pair(new_dirent, std::move(new_dir)));
        operator++();
        return *this;
      }
    }
    else if(dp->d_type == DT_REG)
    {
      m_CurFile = dir_info.second + '/' + dp->d_name;
      return *this;
    }
  }

  closedir(dirent);

  m_DirectoryHandle.pop_back();
  operator++();
#endif
  return *this;
}

const std::string & DirectoryIterator::operator *() const
{
  return m_CurFile;
}

DirectoryIteratorRequest::DirectoryIteratorRequest(const char * dir) :
  m_Dir(dir)
{

}

DirectoryIterator DirectoryIteratorRequest::begin()
{
  return DirectoryIterator(m_Dir);
}

DirectoryIterator DirectoryIteratorRequest::end()
{
  return DirectoryIterator();
}

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
