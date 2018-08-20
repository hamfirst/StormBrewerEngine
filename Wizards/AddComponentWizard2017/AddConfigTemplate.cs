using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace AddComponentWizard2017
{
	static class AddConfigTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string header_file, string meta_file, string reg_file)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			var friendly_name = Regex.Replace(component_name, "(\\B[A-Z])", " $1");

			string header_data = $@"
#pragma once

#include ""Game/GameCommon.h""
#include ""Game/GameServerTypes.h""

struct {component_name}
{{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION({component_name});

  // Serialized variables
}};
";

			string meta_data = $@"
#include ""{rel_path}/{header_file}""
";

			string reg_data = $@"
#include ""Game/GameCommon.h""
#include ""Foundation/SkipField/SkipField.h""

#include ""StormRefl/StormReflMetaFuncs.h""
#include ""StormRefl/StormReflJsonStd.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""Runtime/Config/ConfigRegistrationMacros.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

REGISTER_CONFIG_TYPE({component_name}, ""{friendly_name}"", ""{component_name.ToLower()}"", ""Configs"");
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({component_name});
";

			File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
			File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
			File.WriteAllText(Path.Combine(base_path, header_file), header_data);
			
		}
	}
}
