using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddAnimationEventTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string header_file, string meta_file, string reg_file)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			string header_data = $@"
#pragma once

#include ""Game/GameCommon.h""

#include ""Runtime/SpriteBase/SpriteAnimationEventDef.refl.h""

struct {component_name} : public SpriteAnimationEventDataBase
{{
public:
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({component_name});
  static uint32_t TypeNameHash;
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

#include ""Runtime/SpriteBase/SpriteAnimationEventTypeDatabase.h""
#include ""Runtime/SpriteBase/SpriteAnimationEventRegister.h""

#include ""Foundation/PropertyMeta/PropertyFieldMetaFuncs.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({component_name});
REGISTER_SPRITE_ANIM_EVENT_DATA({component_name});

uint32_t {component_name}::TypeNameHash = StormReflTypeInfo<{component_name}>::GetNameHash();
";

				File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
				File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
				File.WriteAllText(Path.Combine(base_path, header_file), header_data);
			
		}
	}
}
