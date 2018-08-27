
#include <cstdio>
#include <cstring>

#include <string>
#include <unordered_map>
#include <optional>

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
  auto fp = fopen(file.c_str(), "wt");
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
    return m_Index >= m_Template.size() ? 0 : m_Template[m_Index];
  }

  char Peek() const
  {
    return m_Index + 1 >= m_Template.size() ? 0 : m_Template[m_Index + 1];
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
          result += '"';
        }
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
      return fs::canonical(start_path / "CMakeLists.txt");
    }
  }

  return FindCMakeFile(start_path.parent_path(), root_path);
}

enum class CMakeFileType
{
  kCPPFile,
  kHeaderFile,
  kReflFile,
};

void InsertIntoCMakeFile(std::string & cmake_file, const std::string & file, 
    CMakeFileType type)
{
  std::string placeholder;
  switch(type)
  {
  case CMakeFileType::kCPPFile:
    placeholder = "            #CPP_PLACEHOLDER";
    break;
  case CMakeFileType::kHeaderFile: 
    placeholder = "            #HEADER_PLACEHOLDER";
    break;
  case CMakeFileType::kReflFile:
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

bool WriteTemplate(const fs::path & target_file, const fs::path & template_file,
    const std::unordered_map<std::string, std::string> & template_replacements)
{
  auto template_data = ReadFileIntoString(template_file.string());
  if(template_data.has_value())
  {
    return false;
  }

  auto formated_data = FormatTemplate(template_data.value(), template_replacements);
  return WriteStringToFile(target_file.string(), formated_data);
}

std::string GetRelativePath(const fs::path & root_path, const fs::path & target_dir)
{
  auto dir_str = target_dir.string();
  auto root_str = root_path.string();

  if(dir_str.find(root_str) != 0)
  {
    fprintf(stderr, "Could not find relative path (root: %s, target: %s)\n",
        root_path.c_str(), target_dir.c_str());
    return target_dir;
  }

  auto rel_path = target_dir.c_str() + root_str.size();
  if(rel_path[0] == '/' || rel_path[0] == '\\')
  {
    return rel_path + 1;
  }

  return rel_path;
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
      printf("CMake path: %s\n", cmake_file_path->c_str());
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
    printf("Usage addcode <type> <name> <target_dir> <project_root_dir>\n");
    return 1;
  }

  auto type = std::string(argv[1]);
  auto name = std::string(argv[2]);
  auto target_dir = fs::canonical(argv[3]);
  auto root_dir = fs::canonical(argv[4]);
  auto template_dir = fs::canonical(root_dir / "Wizards/Templates/");

  auto cmake_file_path = FindCMakeFile(target_dir, root_dir);
  if(cmake_file_path.has_value() == false)
  {
    fprintf(stderr, "Could not locate cmake file\n");
    return 3025;
  }

  auto cmake_file_data = ReadFileIntoString(cmake_file_path->string());
  if(cmake_file_data.has_value() == false)
  {
    fprintf(stderr, "Error reading cmake file\n");
    return 3025;
  }

  auto & cmake_file = cmake_file_data.value();

  auto class_name = std::string(name) + type;
  auto cpp_file_ext = ".refl.cpp";
  auto header_file_ext = ".refl.h";
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
  auto rel_cmake = GetRelativePath(cmake_file_path->parent_path(), target_dir);

  std::unordered_map<std::string, std::string> template_replacements;
  template_replacements["class_name"] = class_name;
  template_replacements["header_file"] = header_file;
  template_replacements["meta_file"] = meta_file;
  template_replacements["rel_path"] = rel_path;
  
  if(WriteTemplate(target_dir / cpp_file, cpp_template_file, template_replacements))
  {
    InsertIntoCMakeFile(cmake_file, rel_cmake + '/' + cpp_file, CMakeFileType::kCPPFile);
  }

  if(WriteTemplate(target_dir / header_file, header_template_file, template_replacements))
  {
    InsertIntoCMakeFile(cmake_file, rel_cmake + '/' + header_file, CMakeFileType::kHeaderFile);
    InsertIntoCMakeFile(cmake_file, rel_cmake + '/' + header_file, CMakeFileType::kReflFile);
  }

  if(WriteTemplate(target_dir / meta_file, meta_template_file, template_replacements))
  {
    InsertIntoCMakeFile(cmake_file, rel_cmake + '/' + meta_file, CMakeFileType::kHeaderFile);
  }

  if(WriteTemplate(target_dir / reg_file, reg_template_file, template_replacements))
  {
    InsertIntoCMakeFile(cmake_file, rel_cmake + '/' + reg_file, CMakeFileType::kCPPFile);
  }

  WriteStringToFile(cmake_file_path->string(), cmake_file);
  return 0;
}

