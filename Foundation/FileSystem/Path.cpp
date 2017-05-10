
#include <Foundation/Common.h>
#include <Foundation/FileSystem/Path.h>

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

bool ConvertToCanonicalPath(std::string & path, const std::string & root_path)
{
  auto canonical_path = fs::canonical(path);
  path = canonical_path.string();

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
  auto canonical_path = fs::canonical(fs::current_path());
  auto root_path = canonical_path.string();

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
  if (path_index = std::string::npos)
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
