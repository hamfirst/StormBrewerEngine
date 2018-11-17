using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AddComponentWizard2017
{
	static class AddBotStateTemplate
	{
		public static void CreateTemplate(string component_name, string project_name, string root_path, string base_path, string source_file, string header_file, string meta_file)
		{
			System.IO.Directory.CreateDirectory(base_path);

			var rel_path = project_name + "/" + RelativePath.GetRelativePath(base_path, root_path);
			rel_path = rel_path.Replace('\\', '/');

			string header_data = $@"
#pragma once

#include ""StormNet/NetReflectionStruct.h""
#include ""StormNet/NetReflectionTypeDatabase.h""

#include ""Game/ServerObjects/Bot/States/BotStateBase.refl.h""

class {component_name} : public BotStateBase, public BotStateEventHandler<{component_name}>
{{
public:
  NET_REFL;

  virtual void Move(BotServerObject & Bot, GameLogicContainer & game_container) override;
  virtual void Transition(BotServerObject & Bot, GameLogicContainer & game_container) override;
  virtual void Animate(BotServerObject & Bot, GameLogicContainer & game_container) override;

public:
  // Serialized variables
}};
";

			string source_data = $@"
#include ""Game/GameCommon.h""

#include ""Game/GameLogicContainer.h""
#include ""Game/GameServerEventSender.h""
#include ""Game/GameStage.h""

#include ""Game/ServerObjects/Bot/BotServerObject.refl.h""
#include ""Game/ServerObjects/Bot/BotSettings.h""

#include ""{rel_path}/{header_file}""
#include ""{rel_path}/{meta_file}""

#include ""StormNet/NetReflectionTypeDatabase.h""

NET_REGISTER_TYPE({component_name}, BotStateBase);

void {component_name}::Move(BotServerObject & Bot, GameLogicContainer & game_container)
{{

}}

void {component_name}::Transition(BotServerObject & Bot, GameLogicContainer & game_container)
{{

}}

void {component_name}::Animate(BotServerObject & Bot, GameLogicContainer & game_container)
{{
	Bot.FrameAdvance(COMPILE_TIME_CRC32_STR(""Animation""));

    Bot.TriggerAnimationEvents(game_container, *this);
}}

";

			string meta_data = $@"
#include ""{rel_path}/{header_file}""
";

			File.WriteAllText(Path.Combine(base_path, source_file), source_data);
			File.WriteAllText(Path.Combine(base_path, meta_file), meta_data);
			File.WriteAllText(Path.Combine(base_path, header_file), header_data);

		}
	}
}
