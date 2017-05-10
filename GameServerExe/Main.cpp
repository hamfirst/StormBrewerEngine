
#include <thread>

#include <StormRefl/StormReflJsonStd.h>

#include "Foundation/Common.h"
#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"
#include "Foundation/Time/FrameClock.h"

#include "Shared/AssetBundle/AssetBundle.h"

#include "Runtime/Runtime.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Map/MapResource.h"

#include "Game/GameSimulation.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"

#include "GameServer/GameServer.h"

#ifdef _MSC_VER
#pragma comment(lib, "Winmm.lib")
#endif

#ifdef _LINUX
#include <unistd.h>
#endif

double send_time;

extern int g_LagSim;

int main(int argc, char ** argv)
{
#ifdef _LINUX
  if (argc == 2 && argv[1] == std::string("-D"))
  {
    printf("Entering Daemon Mode");
    daemon(1, 0);
  }
#endif

  printf("Game Server\n");

  RuntimeInit();

  printf("  Loading assets...\n");

  AssetBundle bundle;
  bundle.LoadAsset<EntityResource>("./Entities/Hero.entity");
  bundle.LoadAsset<EntityResource>("./Entities/HeadIcon.entity");
  bundle.LoadAsset<EntityResource>("./Entities/Tile.entity");
  bundle.LoadAsset<MapResource>("./Maps/Map.map");

  if (bundle.AllLoadedSuccessfully() == false)
  {
    printf("  Failed to load assets...\n");
    return 0;
  }

  printf("  Assets loaded...\n");

  GameStageManager stage_manager;

  printf("  Starting server...\n");
  NetworkInit();

  GameServer game_server(256, 47815, stage_manager);
  printf("  Server started!\n");

  FrameClock frame_clock(1.0 / 60.0);
  frame_clock.Start();

  while (true)
  {
    game_server.Update();

    if (frame_clock.ShouldStartFrame())
    {
      frame_clock.BeginFrame();
      game_server.GetGameInstanceManager().Update();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  NetworkShutdown();
}

