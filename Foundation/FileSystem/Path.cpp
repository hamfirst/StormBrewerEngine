
#include "Foundation/Common.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"

#ifndef _WEB
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

bool ConvertToCanonicalPath(std::string & path, const std::string & root_path)
{
#ifndef _WEB
  auto canonical_path = fs::canonical(path);
  path = canonical_path.string();
#endif

  for (auto & c : path)
  {
    if (c == '\\')
    {
      c = '/';
    }
  }

  if (path.length() < root_path.length())
  {
    return false;
  }

  for (std::size_t index = 0, end = root_path.length(); index < end; ++index)
  {
    if (path[index] != root_path[index])
    {
      return false;
    }
  }

  path = "./" + path.substr(root_path.length());
  return true;
}

std::string GetCanonicalRootPath()
{
#ifndef _WEB
  auto canonical_path = fs::canonical(fs::current_path());
  auto root_path = canonical_path.string();

  auto asset_dir_file = FileOpen("asset_dir.txt", FileOpenMode::kRead);
  if (asset_dir_file.GetFileOpenError() == 0)
  {
    auto asset_dir_data = asset_dir_file.ReadFileFull();
    auto asset_dir = BufferToString(asset_dir_data);

    canonical_path = fs::canonical(asset_dir);
    root_path = canonical_path.string();
  }

#else
  std::string root_path = "";
#endif

  for (auto & c : root_path)
  {
    if (c == '\\')
    {
      c = '/';
    }
  }

  return root_path + "/";
}

std::string GetFileNameForCanonicalPath(const std::string & path)
{
  auto index = path.rfind('/');
  if (index == std::string::npos)
  {
    return path;
  }

  return path.substr(index + 1);
}

std::string GetFileStemForCanonicalPath(const std::string & path)
{
  auto file_name = GetFileNameForCanonicalPath(path);
  auto index = file_name.find('.');
  if (index == std::string::npos)
  {
    return file_name;
  }

  return file_name.substr(0, index);
}

std::string GetFileExtensionForCanonicalPath(const std::string & path)
{
  auto path_index = path.rfind('/');
  auto ext_index = path.rfind('.');
  if (path_index == std::string::npos)
  {
    if (ext_index == std::string::npos)
    {
      return "";
    }
    else
    {
      return path.substr(ext_index + 1);
    }
  }
  else
  {
    if (ext_index == std::string::npos || ext_index < path_index)
    {
      return "";
    }
    else
    {
      return path.substr(ext_index + 1);
    }
  }
}
