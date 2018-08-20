using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddComponentTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string source_file, string header_file, string meta_file, string reg_file, 
			string init_data, bool create_init_data, bool sync_to_server_object)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			var init_data_header = create_init_data == false ? "" :
$@"struct {init_data} : public ComponentInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({init_data});
}};
";

			var init_data_source = create_init_data == false ? "" : $@"{init_data} && init_data";
			var init_data_reg = create_init_data == false ? $@"REGISTER_COMPONENT({component_name}, Component);" :
$@"REGISTER_COMPONENT_WITH_INIT_DATA({component_name}, {init_data}, Component);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({init_data});";

			string server_obj_source = "";
			if(sync_to_server_object)
			{
				server_obj_source = $@"
  auto server_obj = GetEntity()->GetServerObjectAs();
  auto game_container = GetEntity()->GetGameContainer()->GetInstanceData()->GetLogicContainer();

  if (server_obj)
  {{
    auto position = server_obj->GetPosition(game_container);
    GetEntity()->SetPosition(position);
  }}
";
			}

			string header_data = $@"
#pragma once

#include ""GameClient/GameClientCommon.h""
#include ""Runtime/Component/ComponentInitData.refl.h""
#include ""Engine/Component/Component.h""

{init_data_header}
class {component_name} : public Component
{{
public:
  DECLARE_COMPONENT;

  {component_name}({init_data_source});
  virtual ~{component_name}();

  void UpdateFirst();
}};
";

			string source_data = $@"
#include ""GameClient/GameClientCommon.h""
#include ""GameClient/GameContainer.h""

#include ""Runtime/ServerObject/ServerObject.h""
#include ""Runtime/Entity/EntityResource.h""
#include ""Runtime/VisualEffect/VisualEffectResource.h""
#include ""Runtime/Asset/Asset.h""

#include ""Engine/Entity/Entity.h""
#include ""Engine/Asset/AudioAsset.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

{component_name}::{component_name}({init_data_source})
{{
  
}}

{component_name}::~{component_name}()
{{
  
}}

void {component_name}::UpdateFirst()
{{
{server_obj_source}
}}
";

			string meta_data = $@"
#include ""{rel_path}/{header_file}""
";

			string reg_data = $@"
#include ""GameClient/GameClientCommon.h""

#include ""Engine/Component/ComponentSystem.h""
#include ""Engine/Component/ComponentList.h""
#include ""Engine/Component/ComponentUpdateRegistrationTemplates.h""
#include ""Runtime/Component/ComponentInitDataTypeDatabase.h""
#include ""Runtime/Component/ComponentInitDataTypeDatabaseRegister.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

{init_data_reg}
";

			File.WriteAllText(Path.Combine(base_path, source_file), source_data);
			File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
			File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
			File.WriteAllText(Path.Combine(base_path, header_file), header_data);
		}
	}
}
