
#include "Foundation/Common.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"

#include <cwctype>

#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)
#include <filesystem>
namespace fs = std::filesystem;
#endif

bool ConvertToCanonicalPath(std::string & path, const std::string & root_path)
{
#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)

  auto fs_path = fs::path(path);
  auto filename = fs_path.filename();
  auto parent_path = fs_path.remove_filename();

  fs::path canonical_path;
  std::error_code ec;
  canonical_path = fs::canonical(fs::path(root_path) / fs::path(parent_path), ec);

  if(ec)
  {
    canonical_path = fs::canonical(parent_path, ec);

    if(ec)
    {
      canonical_path = parent_path;
    }
  }

  auto rel_path = fs::relative(canonical_path / filename, root_path);
  path = rel_path.string();
#endif

  for (auto & c : path)
  {
    if (c == '\\')
    {
      c = '/';
    }
  }

  path = "./" + path;
  return true;
}

std::string GetCanonicalRootPath()
{
#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)
  auto canonical_path = fs::canonical(fs::current_path());
  auto root_path = canonical_path.string();

  auto asset_dir_file = FileOpen("asset_dir.txt", FileOpenMode::kRead);
  if (asset_dir_file.GetFileOpenError() == 0)
  {
    auto asset_dir_data = asset_dir_file.ReadFileFull();
    auto asset_dir = BufferToString(asset_dir_data);

    while(asset_dir.size() > 0 && iswspace(asset_dir.back()))
    {
      asset_dir.pop_back();
    }

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

std::string GetFullPath(const std::string & path, const std::string & root_path)
{
#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)
  if (fs::path(path).is_absolute())
  {
    std::error_code ec;
    auto canonical_path = fs::canonical(path, ec);

    if(ec)
    {
      return path;
    }

    return canonical_path.string();
  }
  else
  {
    std::error_code ec;
    auto combined_path = fs::path(root_path) / fs::path(path);
    auto canonical_path = fs::canonical(combined_path, ec);

    if(ec)
    {
      return combined_path.string();
    }

    return canonical_path.string();
  }
#else
  return path;
#endif
}

std::string JoinPath(const std::string & path_part1, const std::string & path_part2)
{
#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)
  return (fs::path(path_part1) / path_part2).string();
#else

  if (path_part1.size() > 0 && path_part1.back() != '/')
  {
    return path_part1 + '/' + path_part2;
  }
  else
  {
    return path_part1 + path_part2;
  }
#endif
}

bool CreateDirectory(const std::string & path)
{
#if !defined(_WEB) && !defined(_ANDROID) && !defined(_IOS)
  std::error_code ec;
  fs::create_directories(path.data(), ec);

  return !ec;
#else
  return false;
#endif
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

std::string GetFileExtensionForPath(const std::string & path)
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
