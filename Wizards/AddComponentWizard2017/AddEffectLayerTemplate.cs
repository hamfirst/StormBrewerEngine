using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddEffectLayerTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string source_file, string header_file, string meta_file, string reg_file, string init_data)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			string header_data = $@"
#pragma once

#include ""GameClient/GameClientCommon.h""
#include ""Runtime/Map/MapEffectLayerDef.refl.h""
#include ""Engine/Map/MapEffectLayerRenderer.h""

struct {init_data} : public MapEffectLayerInitData
{{
  STORM_DATA_DEFAULT_CONSTRUCTION_DERIVED({init_data});
}};

class {component_name} : public MapEffectLayerRenderer
{{
public:

  {component_name}(const {init_data} & init_data);
  virtual ~{component_name}();

  virtual void Update(GameContainer & game_container) override;
  virtual void Render(GameContainer & game_container, const Box & viewport_bounds, 
                                    const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state, RenderUtil & render_util) override;
}};
";

			string source_data = $@"

#include ""GameClient/GameClientCommon.h""

#include ""Engine/Rendering/GeometryVertexBufferBuilder.h""
#include ""Engine/Shader/ShaderManager.h""

#include ""GameClient/GameContainer.h""
#include ""GameClient/GameClientEventSender.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

{component_name}::{component_name}(const {init_data} & init_data)
{{
  
}}

{component_name}::~{component_name}()
{{
  
}}

void {component_name}::Update(GameContainer & game_container)
{{

}}

void {component_name}::Render(GameContainer & game_container, const Box & viewport_bounds, 
                              const RenderVec2 & screen_center, const Vector2 & offset, RenderState & render_state, RenderUtil & render_util)
{{

}}
";

			string meta_data = $@"
#include ""{rel_path}/{header_file}""
";

			string reg_data = $@"
#include ""GameClient/GameClientCommon.h""

#include ""Foundation/PropertyMeta/PropertyFieldMetaFuncs.h""

#include ""StormData/StormData.h""
#include ""StormData/StormDataJson.h""

#include ""Runtime/Map/MapEffectLayerTypeDatabase.h""
#include ""Runtime/Map/MapEffectLayerTypeRegister.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

REGISTER_EFFECT_LAYER_DATA({component_name}, {init_data});
STORM_DATA_DEFAULT_CONSTRUCTION_IMPL({init_data});
";

			File.WriteAllText(Path.Combine(base_path, source_file), source_data);
			File.WriteAllText(Path.Combine(base_path, reg_file), reg_data);
			File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
			File.WriteAllText(Path.Combine(base_path, header_file), header_data);
		}
	}
}
