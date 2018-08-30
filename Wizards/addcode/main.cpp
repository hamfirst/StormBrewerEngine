
#include <cstdio>
#include <cstring>

#include <string>
#include <unordered_map>
#include <optional>
#include <algorithm>

#include <filesystem>
namespace fs = std::filesystem;

std::optional<std::string> ReadFileIntoString(const std::string & file)
{
  FILE * fp = fopen(file.c_str(), "rb");
  if(fp == nullptr)
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
  if(fp == nullptr)
  {
    return false;
  }

  fwrite(file_data.data(), file_data.size(), 1, fp);
  fclose(fp);
  return true;
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

  while(true)
  {
    auto c = itr();
    if(in_template_id)
    {
      if(c == '}')
      {
        auto repl = template_replacements.find(template_name);
        if(repl != template_replacements.end())
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
      if(c == '{')
      {
        auto n = itr.Peek();
        if(n == '{')
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
      else if(c == '"')
      {
        auto n = itr.Peek();
        if(n == '"')
        {
          itr();
        }
        result += '"';
      }
      else if(c == 0)
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
  if(start_path == root_path || start_path == start_path.root_directory())
  {
    return {};
  }

  for(auto itr : fs::directory_iterator(start_path))
  {
    auto path = itr.path();
    if(itr.is_regular_file() && path.filename() == "CMakeLists.txt")
    {
      return fs::canonical(start_path);
    }
  }

  return FindCMakeFile(start_path.parent_path(), root_path);
}

std::optional<std::pair<std::string, std::string>> FindVCXProjFiles(
    const fs::path & project_path)
{
  std::string vcxproj_file;
  std::string vcxproj_filters_file;

  for(auto itr : fs::directory_iterator(project_path))
  {
    auto path = itr.path();
    auto extension = path.extension();

    if(itr.is_regular_file() && extension == ".vcxproj")
    {
      vcxproj_file = fs::canonical(path).string();
    }
    else if(itr.is_regular_file() && extension == ".filters")
    {
      vcxproj_filters_file = fs::canonical(path).string();
    }
  }

  if(vcxproj_file.size() > 0 && vcxproj_filters_file.size() > 0)
  {
    return std::make_pair(std::move(vcxproj_file), std::move(vcxproj_filters_file));
  }

  return {};
}

enum class ProjectFileType
{
  kCPPFile,
  kHeaderFile,
  kReflFile,
};

void InsertIntoCMakeFile(std::string & cmake_file, const std::string & file, 
    ProjectFileType type)
{
  std::string placeholder;
  switch(type)
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
  if(pos == std::string::npos)
  {
    printf("Invalid cmake file (no cpp placeholder)");
    return;
  }

  cmake_file.replace(pos, placeholder.size(), 
        "            " + file + "\n" + placeholder);
}

void InsertIntoVCXProjFile(std::string & vcxproj_file, const std::string & file,
    ProjectFileType type)
{
  auto reverse_file = file;
  std::transform(reverse_file.begin(), reverse_file.end(), reverse_file.begin(),
      [](char c) { return c == '/' ? '\\' : c; });

  std::string insert;

  std::size_t pos;
  if(type == ProjectFileType::kCPPFile)
  {
    pos = vcxproj_file.find("    <ClCompile Include=\"");
    insert = "    <ClCompile Include=\"" + reverse_file + "\" />\n";
  }
  else if(type == ProjectFileType::kHeaderFile)
  {
    pos = vcxproj_file.find("    <ClInclude Include=\"");
    insert = "    <ClInclude Include=\"" + reverse_file + "\" />\n";
  }
  else
  {
    return;
  }

  if(pos == std::string::npos)
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
  if(path_end != std::string::npos)
  {
    auto filter_dir = reverse_file.substr(0, path_end);
    filter = "      <Filter>" + filter_dir + "</Filter>\n";
  }

  std::string insert;

  std::size_t pos;
  if(type == ProjectFileType::kCPPFile)
  {
    pos = vcxproj_file.find("    <ClCompile Include=\"");
    insert = "    <ClCompile Include=\"" + reverse_file + "\" ";

    if(filter.size() > 0)
    {
      insert += ">\n" + filter + "    </ClCompile>\n";
    }
    else
    {
      insert += "/>\n";
    }
  }
  else if(type == ProjectFileType::kHeaderFile)
  {
    pos = vcxproj_file.find("    <ClInclude Include=\"");
    insert = "    <ClInclude Include=\"" + reverse_file + "\" ";

    if(filter.size() > 0)
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

  if(pos == std::string::npos)
  {
    return;
  }

  vcxproj_file.replace(pos, 0, insert);
}

bool WriteTemplate(const fs::path & target_file, const fs::path & template_file,
    const std::unordered_map<std::string, std::string> & template_replacements)
{
  auto template_data = ReadFileIntoString(template_file.string());
  if(template_data.has_value() == false)
  {
    return false;
  }

  auto formated_data = FormatTemplate(template_data.value(), template_replacements);
  printf("%s\n", target_file.string().c_str());

  return WriteStringToFile(target_file.string(), formated_data);
}

std::string GetRelativePath(const fs::path & root_path, const fs::path & target_dir)
{
  auto dir_str = target_dir.string();
  auto root_str = root_path.string();

  if(dir_str.find(root_str) != 0)
  {
    fprintf(stderr, "Could not find relative path (root: %s, target: %s)\n",
        root_path.string().c_str(), target_dir.string().c_str());
    return target_dir.string();
  }

  auto target_dir_str = target_dir.string();
  auto rel_path = target_dir_str.c_str() + root_str.size();

  std::string path;
  if(rel_path[0] == '/' || rel_path[0] == '\\')
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

int main(int argc, char ** argv)
{
  if(!strcmp(argv[1], "-d"))
  {
    auto cur_dir = fs::canonical(".");
    auto cur_file = fs::canonical(argv[0]);
    printf("Current dir: %s\n", cur_dir.string().c_str());

    auto cmake_file_path = FindCMakeFile(cur_dir, cur_dir.root_directory());
    if(cmake_file_path.has_value())
    {
      printf("CMake path: %s\n", cmake_file_path->string().c_str());
      auto rel_cmake = GetRelativePath(cmake_file_path->parent_path(), cur_file);
      printf("CMake relative path %s\n", rel_cmake.c_str());
    }
    else
    {
      printf("CMake path not found\n");
    }

    return 0;
  }

  if(argc < 5)
  {
    printf("Usage addcode <type> <name> <target_dir> <project_root_dir> <options>\n");
    return 1;
  }

  auto type = std::string(argv[1]);
  auto name = std::string(argv[2]);
  auto target_dir = fs::canonical(argv[3]);
  auto root_dir = fs::canonical(argv[4]);
  auto template_dir = fs::canonical(root_dir / "Wizards/Templates/");

  auto project_file_path = FindCMakeFile(target_dir, root_dir);
  if(project_file_path.has_value() == false)
  {
    fprintf(stderr, "Could not locate cmake file\n");
    return 3025;
  }

  auto cmake_file_path = project_file_path.value() / "CMakeLists.txt";

  auto cmake_file_data = ReadFileIntoString(cmake_file_path.string());
  if(cmake_file_data.has_value() == false)
  {
    fprintf(stderr, "Error reading cmake file\n");
    return 3025;
  }

  auto & cmake_file = cmake_file_data.value();

  bool use_vcxproj = false;
  bool use_meta = false;

  for(int index = 5; index < argc; ++index)
  {
    for(char * p = argv[index]; *p != 0; ++p)
    {
      if(*p == 'm')
      {
        use_meta = true;
      }
      else if(*p == 'v')
      {
        use_vcxproj = true;
      }
    }
  }

  auto class_name = std::string(name);
  auto cpp_file_ext = use_meta ? ".refl.cpp" : ".cpp";
  auto header_file_ext = use_meta ? ".refl.h" : ".h";
  auto meta_file_ext = ".refl.meta.h";
  auto reg_file_ext = ".refl.reg.cpp";

  auto cpp_file = class_name + cpp_file_ext;
  auto header_file = class_name + header_file_ext;
  auto meta_file = class_name + meta_file_ext;
  auto reg_file = class_name + reg_file_ext;

  auto cpp_template_file = template_dir / (type + cpp_file_ext);
  auto header_template_file = template_dir / (type + header_file_ext);
  auto meta_template_file = template_dir / (type + meta_file_ext);
  auto reg_template_file = template_dir / (type + reg_file_ext);

  auto rel_path = GetRelativePath(root_dir, target_dir);
  auto rel_cmake = GetRelativePath(project_file_path.value(), target_dir);

  std::string vcxproj_file;
  std::string vcxproj_filters_file;

  auto vcxproj_file_paths = FindVCXProjFiles(project_file_path.value());
  if(use_vcxproj)
  {
    use_vcxproj = false;

    if(vcxproj_file_paths)
    {
      auto vcxproj_file_data = ReadFileIntoString(vcxproj_file_paths->first);
      auto vcxproj_filters_file_data = ReadFileIntoString(vcxproj_file_paths->second);

      if(vcxproj_file_data && vcxproj_filters_file_data)
      {
        vcxproj_file = std::move(vcxproj_file_data.value());
        vcxproj_filters_file = std::move(vcxproj_filters_file_data.value());
        use_vcxproj = true;
      }
    }
  }

  auto class_name_lower = class_name;
  std::transform(class_name_lower.begin(), class_name_lower.end(), class_name_lower.begin(),
    [](char c) { return tolower(c); });

  std::string friendly_name;
  for (auto & c : class_name)
  {
    if (c >= 'A' && c <= 'Z' && friendly_name.size() > 0)
    {
      friendly_name += ' ';
    }

    friendly_name += c;
  }

  std::unordered_map<std::string, std::string> template_replacements;
  template_replacements["class_name"] = class_name;
  template_replacements["header_file"] = header_file;
  template_replacements["meta_file"] = meta_file;
  template_replacements["rel_path"] = rel_path;
  template_replacements["class_name_lower"] = class_name_lower;
  template_replacements["friendly_name"] = friendly_name;
  
  if(WriteTemplate(target_dir / cpp_file, cpp_template_file, template_replacements))
  {
    auto file = rel_cmake + '/' + cpp_file;
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kCPPFile);

    if(use_vcxproj)
    {
      InsertIntoVCXProjFile(vcxproj_file, file, ProjectFileType::kCPPFile);
      InsertIntoVCXProjFiltersFile(vcxproj_filters_file, file, ProjectFileType::kCPPFile);
    }
  }

  if(WriteTemplate(target_dir / header_file, header_template_file, template_replacements))
  {
    auto file = rel_cmake + '/' + header_file;
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kHeaderFile);
    
    if(use_meta)
    {
      InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kReflFile);
    }

    if(use_vcxproj)
    {
      InsertIntoVCXProjFile(vcxproj_file, file, ProjectFileType::kHeaderFile);
      InsertIntoVCXProjFiltersFile(vcxproj_filters_file, file, ProjectFileType::kHeaderFile);
    }
  }

  if(WriteTemplate(target_dir / meta_file, meta_template_file, template_replacements))
  {
    auto file = rel_cmake + '/' + meta_file;
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kHeaderFile);
  
    if(use_vcxproj)
    {
      InsertIntoVCXProjFile(vcxproj_file, file, ProjectFileType::kHeaderFile);
      InsertIntoVCXProjFiltersFile(vcxproj_filters_file, file, ProjectFileType::kHeaderFile);
    }
  }

  if(WriteTemplate(target_dir / reg_file, reg_template_file, template_replacements))
  {
    auto file = rel_cmake + '/' + reg_file;
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kCPPFile);
    
    if(use_vcxproj)
    {
      InsertIntoVCXProjFile(vcxproj_file, file, ProjectFileType::kCPPFile);
      InsertIntoVCXProjFiltersFile(vcxproj_filters_file, file, ProjectFileType::kCPPFile);
    }
  }

  WriteStringToFile(cmake_file_path.string(), cmake_file);

  if(use_vcxproj)
  {
    WriteStringToFile(vcxproj_file_paths->first, vcxproj_file);
    WriteStringToFile(vcxproj_file_paths->second, vcxproj_filters_file);
  }

  return 0;
}

