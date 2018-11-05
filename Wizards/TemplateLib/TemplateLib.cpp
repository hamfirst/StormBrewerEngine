
#include "TemplateLib.h"

extern "C"
{
#include "git2.h"
}

static git_repository * s_GitRepo = nullptr;
static git_index * s_GitIndex = nullptr;

std::optional<std::string> ReadFileIntoString(const std::string & file)
{
  FILE * fp = fopen(file.c_str(), "rb");
  if (fp == nullptr)
  {
    return {};
  }

  fseek(fp, 0, SEEK_END);
  auto length = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::string file_data(length, ' ');
  fread((void *)file_data.data(), length, 1, fp);
  fclose(fp);

  return file_data;
}

bool WriteStringToFile(const std::string & file, const std::string & file_data)
{
  auto fp = fopen(file.c_str(), "wb");
  if (fp == nullptr)
  {
    return false;
  }

  fwrite(file_data.data(), file_data.size(), 1, fp);
  fclose(fp);
  return true;
}

std::string GetRelativePath(const fs::path & root_path, const fs::path & target_dir)
{
  auto dir_str = target_dir.string();
  auto root_str = root_path.string();

  if (dir_str.find(root_str) != 0)
  {
    fprintf(stderr, "Could not find relative path (root: %s, target: %s)\n",
      root_path.string().c_str(), target_dir.string().c_str());
    return target_dir.string();
  }

  auto target_dir_str = target_dir.string();
  auto rel_path = target_dir_str.c_str() + root_str.size();

  std::string path;
  if (rel_path[0] == '/' || rel_path[0] == '\\')
  {
    path = rel_path + 1;
  }
  else
  {
    path = rel_path;
  }

  std::transform(path.begin(), path.end(), path.begin(),
    [](char c) { return c == '\\' ? '/' : c; });

  return path;
}


struct TemplateIterator
{
  TemplateIterator(const std::string & templ) : m_Template(templ) {}

  char operator ()()
  {
    auto c = Peek();
    m_Index++;
    return c;
  }

  char Peek() const
  {
    auto c = m_Index >= m_Template.size() ? 0 : m_Template[m_Index];
    return c;
  }

  const std::string & m_Template;
  std::size_t m_Index = 0;
};

std::string FormatTemplate(const std::string & templ,
  const std::unordered_map<std::string, std::string> & template_replacements)
{
  std::string result;
  result.reserve(templ.size());

  bool in_template_id = false;
  std::string template_name;

  TemplateIterator itr(templ);

  while (true)
  {
    auto c = itr();
    if (in_template_id)
    {
      if (c == '}')
      {
        auto repl = template_replacements.find(template_name);
        if (repl != template_replacements.end())
        {
          result += repl->second;
        }
        else
        {
          result += '{';
          result += template_name;
          result += '}';
        }

        in_template_id = false;
      }
      else if (c == 0)
      {
        result += '{';
        result += template_name;
        break;
      }
      else
      {
        template_name += c;
      }
    }
    else
    {
      if (c == '{')
      {
        auto n = itr.Peek();
        if (n == '{')
        {
          itr();
          result += '{';
        }
        else
        {
          in_template_id = true;
          template_name.clear();
        }
      }
      else if(c == '}')
      {
        auto n = itr.Peek();
        if (n == '}')
        {
          itr();
          result += '}';
        }
      }
      else if (c == '"')
      {
        auto n = itr.Peek();
        if (n == '"')
        {
          itr();
        }
        result += '"';
      }
      else if (c == 0)
      {
        break;
      }
      else
      {
        result += c;
      }
    }
  }

  return result;
}

std::optional<fs::path> FindCMakeFile(const fs::path & start_path,
  const fs::path & root_path)
{
  if (start_path == root_path || start_path == start_path.root_directory())
  {
    return {};
  }

  for (auto itr : fs::directory_iterator(start_path))
  {
    auto path = itr.path();
    if (path.filename() == "CMakeLists.txt")
    {
      return fs::canonical(start_path);
    }
  }

  return FindCMakeFile(start_path.parent_path(), root_path);
}

/*
std::optional<std::pair<std::string, std::string>> FindVCXProjFiles(
  const fs::path & project_path)
{
  std::string vcxproj_file;
  std::string vcxproj_filters_file;

  for (auto itr : fs::directory_iterator(project_path))
  {
    auto path = itr.path();
    auto extension = path.extension();

    if (extension == ".vcxproj")
    {
      vcxproj_file = fs::canonical(path).string();
    }
    else if (extension == ".filters")
    {
      vcxproj_filters_file = fs::canonical(path).string();
    }
  }

  if (vcxproj_file.size() > 0 && vcxproj_filters_file.size() > 0)
  {
    return std::make_pair(std::move(vcxproj_file), std::move(vcxproj_filters_file));
  }

  return {};
}
*/

void InsertIntoCMakeFile(std::string & cmake_file, const std::string & file,
  ProjectFileType type)
{
  if(file.length() == 0)
  {
    return;
  }

  std::string placeholder;
  switch (type)
  {
  case ProjectFileType::kCPPFile:
    placeholder = "            #CPP_PLACEHOLDER";
    break;
  case ProjectFileType::kHeaderFile:
    placeholder = "            #HEADER_PLACEHOLDER";
    break;
  case ProjectFileType::kReflFile:
    placeholder = "            #REFL_PLACEHOLDER";
    break;
  }

  auto pos = cmake_file.find(placeholder);
  if (pos == std::string::npos)
  {
    printf("Invalid cmake file (no cpp placeholder)");
    return;
  }

  auto sanitized_file = file;
  cmake_file.replace(pos, placeholder.size(),
    "            " + sanitized_file + "\n" + placeholder);
}

/*
void InsertIntoVCXProjFile(std::string & vcxproj_file, const std::string & file,
  ProjectFileType type)
{
  auto reverse_file = file;
  std::transform(reverse_file.begin(), reverse_file.end(), reverse_file.begin(),
    [](char c) { return c == '/' ? '\\' : c; });

  std::string insert;

  std::size_t pos;
  if (type == ProjectFileType::kCPPFile)
  {
    pos = vcxproj_file.find("    <ClCompile Include=\"");
    insert = "    <ClCompile Include=\"" + reverse_file + "\" />\n";
  }
  else if (type == ProjectFileType::kHeaderFile)
  {
    pos = vcxproj_file.find("    <ClInclude Include=\"");
    insert = "    <ClInclude Include=\"" + reverse_file + "\" />\n";
  }
  else
  {
    return;
  }

  if (pos == std::string::npos)
  {
    return;
  }

  vcxproj_file.replace(pos, 0, insert);
}

void InsertIntoVCXProjFiltersFile(std::string & vcxproj_file, const std::string & file,
  ProjectFileType type)
{
  auto reverse_file = file;
  std::transform(reverse_file.begin(), reverse_file.end(), reverse_file.begin(),
    [](char c) { return c == '/' ? '\\' : c; });

  auto path_end = reverse_file.rfind('\\');
  std::string filter;
  if (path_end != std::string::npos)
  {
    auto filter_dir = reverse_file.substr(0, path_end);
    filter = "      <Filter>" + filter_dir + "</Filter>\n";
  }

  std::string insert;

  std::size_t pos;
  if (type == ProjectFileType::kCPPFile)
  {
    pos = vcxproj_file.find("    <ClCompile Include=\"");
    insert = "    <ClCompile Include=\"" + reverse_file + "\" ";

    if (filter.size() > 0)
    {
      insert += ">\n" + filter + "    </ClCompile>\n";
    }
    else
    {
      insert += "/>\n";
    }
  }
  else if (type == ProjectFileType::kHeaderFile)
  {
    pos = vcxproj_file.find("    <ClInclude Include=\"");
    insert = "    <ClInclude Include=\"" + reverse_file + "\" ";

    if (filter.size() > 0)
    {
      insert += ">\n" + filter + "    </ClInclude>\n";
    }
    else
    {
      insert += "/>\n";
    }
  }
  else
  {
    return;
  }

  if (pos == std::string::npos)
  {
    return;
  }

  vcxproj_file.replace(pos, 0, insert);
}
 */

bool WriteTemplate(const fs::path & target_file, const fs::path & template_file,
  const std::unordered_map<std::string, std::string> & template_replacements)
{
  auto template_data = ReadFileIntoString(template_file.string());
  if (template_data.has_value() == false)
  {
    return false;
  }

  auto formated_data = FormatTemplate(template_data.value(), template_replacements);
  printf("%s\n", target_file.string().c_str());

  return WriteStringToFile(target_file.string(), formated_data);
}

bool GitAddFile(const fs::path & target_file, const fs::path & root_path)
{
  int error;
  if (s_GitRepo == nullptr)
  {
    error = git_libgit2_init();
    if (error < 0)
    {
      return false;
    }

    error = git_repository_open(&s_GitRepo, root_path.string().c_str());
    if (error < 0)
    {
      return false;
    }

    error = git_repository_index(&s_GitIndex, s_GitRepo);
    if (error < 0)
    {
      return false;
    }
  }

  auto target_path = GetRelativePath(root_path, target_file);

  error = git_index_add_bypath(s_GitIndex, target_path.c_str());
  if (error < 0)
  {
    return false;
  }

  return true;
}

bool GitFinalize()
{
  if (s_GitIndex)
  {
    auto error = git_index_write(s_GitIndex);
    if (error < 0)
    {
      return false;
    }
  }

  return true;
}
