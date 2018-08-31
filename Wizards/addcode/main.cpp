
#include "TemplateLib/TemplateLib.h"

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
    GitAddFile(target_dir / cpp_file, root_dir);
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
    GitAddFile(target_dir / header_file, root_dir);
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
    GitAddFile(target_dir / meta_file, root_dir);
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
    GitAddFile(target_dir / reg_file, root_dir);
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

  GitFinalize();
  return 0;
}

