
#include "TemplateLib/TemplateLib.h"

int main(int argc, char ** argv)
{
  if(argc < 3)
  {
    fprintf(stderr, "Usage: addcode <TemplateType> <ClassName>\n");
    return -1;
  }

  auto type = std::string(argv[1]);
  auto name = std::string(argv[2]);
  auto target_dir = fs::canonical(fs::current_path());
  auto root_dir = fs::canonical(argv[0]).parent_path();
  auto template_dir = fs::canonical(root_dir / "Tools/Wizards/Templates/");

  printf("Type: %s\n", type.data());
  printf("Name: %s\n", name.data());
  printf("Target dir: %s\n", target_dir.string().data());
  printf("Root dir: %s\n", root_dir.string().data());

  printf("Template dir %s\n", template_dir.string().data());

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

  auto class_name = std::string(name);
  auto cpp_file_ext = ".cpp";
  auto header_file_ext = ".h";
  auto cpp_refl_file_ext = ".refl.cpp";
  auto header_refl_file_ext = ".refl.h";
  auto meta_file_ext = ".refl.meta.h";
  auto reg_file_ext = ".refl.reg.cpp";

  auto cpp_file = class_name + cpp_file_ext;
  auto header_file = class_name + header_file_ext;
  auto cpp_refl_file = class_name + cpp_refl_file_ext;
  auto header_refl_file = class_name + header_refl_file_ext;
  auto meta_file = class_name + meta_file_ext;
  auto reg_file = class_name + reg_file_ext;

  auto cpp_template_file = template_dir / (type + cpp_file_ext);
  auto header_template_file = template_dir / (type + header_file_ext);
  auto cpp_refl_template_file = template_dir / (type + cpp_refl_file_ext);
  auto header_refl_template_file = template_dir / (type + header_refl_file_ext);
  auto meta_template_file = template_dir / (type + meta_file_ext);
  auto reg_template_file = template_dir / (type + reg_file_ext);

  auto rel_path = GetRelativePath(root_dir, target_dir);
  auto rel_cmake = GetRelativePath(project_file_path.value(), target_dir);

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
  template_replacements["refl_header_file"] = header_refl_file;
  template_replacements["refl_meta_file"] = meta_file;
  template_replacements["rel_path"] = rel_path;
  template_replacements["class_name_lower"] = class_name_lower;
  template_replacements["friendly_name"] = friendly_name;
  
  if(WriteTemplate(target_dir / cpp_file, cpp_template_file, template_replacements))
  {
    GitAddFile(target_dir / cpp_file, root_dir);
    auto file = GetCMakePath(rel_cmake, cpp_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kCPPFile);
  }

  if(WriteTemplate(target_dir / cpp_refl_file, cpp_refl_template_file, template_replacements))
  {
    GitAddFile(target_dir / cpp_refl_file, root_dir);
    auto file = GetCMakePath(rel_cmake, cpp_refl_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kCPPFile);
  }

  if(WriteTemplate(target_dir / header_file, header_template_file, template_replacements))
  {
    GitAddFile(target_dir / header_file, root_dir);
    auto file = GetCMakePath(rel_cmake, header_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kHeaderFile);
  }

  if(WriteTemplate(target_dir / header_refl_file, header_refl_template_file, template_replacements))
  {
    GitAddFile(target_dir / header_refl_file, root_dir);
    auto file = GetCMakePath(rel_cmake, header_refl_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kHeaderFile);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kReflFile);
  }

  if(WriteTemplate(target_dir / meta_file, meta_template_file, template_replacements))
  {
    GitAddFile(target_dir / meta_file, root_dir);
    auto file = GetCMakePath(rel_cmake, meta_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kHeaderFile);
  }

  if(WriteTemplate(target_dir / reg_file, reg_template_file, template_replacements))
  {
    GitAddFile(target_dir / reg_file, root_dir);
    auto file = GetCMakePath(rel_cmake, reg_file);
    InsertIntoCMakeFile(cmake_file, file, ProjectFileType::kCPPFile);
  }

  WriteStringToFile(cmake_file_path.string(), cmake_file);

  GitFinalize();
  return 0;
}

