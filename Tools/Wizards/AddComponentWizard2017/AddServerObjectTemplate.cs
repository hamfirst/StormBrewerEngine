using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddServerObjectTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string source_file, string header_file, string meta_file, string reg_file,
			string init_data, bool create_init_data, string entity_binding, bool position_data)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			if(String.IsNullOrWhiteSpace(entity_binding))
			{
				entity_binding = "nullptr";
			}
			else
			{
				entity_binding = "\"" + entity_binding + "\"";
			}

			var init_data_header = create_init_data == false ? "" :
$@"struct {init_data} : public ServerObjectInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({init_data});
}};";
			var init_data_func = create_init_data == false ? "" : $@"void Init(const {init_data} & init_data);";
			var init_data_src = create_init_data == false ? "" :
$@"void {component_name}::Init(const {init_data} & init_data)
{{

}}
";

			string position_header_funcs = "";
			string position_header_data = "";
			string position_source_funcs = "";
			if(position_data)
			{
				position_header_funcs = $@"\n  virtual void InitPosition(const Vector2 & pos) override;\n  virtual Vector2 GetPosition(GameLogicContainer & game_container) const override;\n";
				position_header_data = $@"\n  GameNetVec2 m_Position = {};\n";

				position_source_funcs = $@"\nvoid {component_name}::InitPosition(const Vector2 & pos)\n{\n  m_Position = GameNetVec2(pos.x, pos.y);\n}\n\nVector2 {component_name}::GetPosition(GameLogicContainer & game_container) const\n{\n  return m_Position;\n}\n";
			}

			string header_data = $@"
#pragma once

#include ""Game/GameCommon.h""

#include ""Game/GameLogicContainer.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""
#include ""Game/Systems/GameLogicSystems.h""

#include ""Runtime/ServerObject/ServerObject.h""
#include ""Runtime/ServerObject/ServerObjectInitData.refl.h""
#include ""Runtime/ServerObject/ServerObjectRegistrationMacros.h""

{init_data_header}
class {component_name} : public ServerObject
{{
public:
  DECLARE_SERVER_OBJECT;

  {component_name}() = default;
  {component_name}(const {component_name} & rhs) = default;
  {component_name}({component_name} && rhs) = default;

  {component_name} & operator = (const {component_name} & rhs) = default;
  {component_name} & operator = ({component_name} && rhs) = default;

  {init_data_func}
  void UpdateFirst(GameLogicContainer & game_container);
  void UpdateMiddle(GameLogicContainer & game_container);
  {position_header_funcs}

  virtual czstr GetDefaultEntityBinding() const override;

public:
  // Serialized variables
  {position_header_data}
}};
";

			string source_data = $@"

#include ""Game/GameCommon.h""

#include ""Game/GameController.refl.h""
#include ""Game/GameServerEventSender.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

{init_data_src}
void {component_name}::UpdateFirst(GameLogicContainer & game_container)
{{

}}

void {component_name}::UpdateMiddle(GameLogicContainer & game_container)
{{

}}
{position_source_funcs}
czstr {component_name}::GetDefaultEntityBinding() const
{{
  return {entity_binding};
}}
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

#include ""Runtime/ServerObject/ServerTypesJson.h""
#include ""Runtime/ServerObject/ServerTypesNet.h""
#include ""Runtime/ServerObject/ServerObjectRegistrationMacros.h""
#include ""Runtime/ServerObject/ServerObjectEventRegister.h""
#include ""Runtime/ServerObject/ServerObjectMetaFuncs.h""
#include ""Runtime/ServerObject/ServerObjectSystem.h""
#include ""Runtime/ServerObject/ServerObjectUpdate.h""
#include ""Runtime/ServerObject/ServerObjectSerialize.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

REGISTER_SERVER_OBJECT_WITH_INIT_DATA({component_name}, {init_data}, ServerObject);
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({init_data});
";

			File.WriteAllText(Path.Combine(base_path, source_file), source_data);
			File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
			File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
			File.WriteAllText(Path.Combine(base_path, header_file), header_data);
		}
	}
}
