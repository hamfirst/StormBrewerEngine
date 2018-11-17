using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddPathTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string header_file, string meta_file, string reg_file)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			string header_data = $@"
#pragma once

#include ""Game/GameCommon.h""

#include ""Runtime/Path/PathDef.refl.h""

struct {component_name} : public PathDataBase
{{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({component_name});

  // Serialized variables
}};
";

			string meta_data = $@"
#include ""{rel_path}/{header_file}""
";

			string reg_data = $@"
#include ""Game/GameCommon.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataTypeDatabase.h""
#include ""StormData/StormDataParent.h""

#include ""Runtime/Path/PathTypeDatabase.h""
#include ""Runtime/Path/PathTypeRegister.h""

#include ""Foundation/PropertyMeta/PropertyFieldMetaFuncs.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({component_name});
REGISTER_PATH_DATA({component_name});
";

				File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
				File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
				File.WriteAllText(Path.Combine(base_path, header_file), header_data);
			
		}
	}
}
