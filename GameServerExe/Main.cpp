
#include <thread>

#include <StormRefl/StormReflJsonStd.h>

#include "Foundation/Common.h"
#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"
#include "Foundation/Time/FrameClock.h"

#include "Runtime/Runtime.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Map/MapResource.h"

#include "Game/GameFullState.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameSharedGlobalResources.h"
#include "Game/GameNetworkSettings.h"

#include "GameServer/GameServer.h"
#include "GameServer/GameServerGlobalResources.h"

#ifdef _MSC_VER
#pragma comment(lib, "Winmm.lib")
#endif

#ifdef _LINUX
#include <unistd.h>
#include <sys/types.h>
#endif

double send_time;

extern int g_LagSim;

void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

int main(int argc, char ** argv)
{
#ifdef _LINUX
  if (argc == 2 && argv[1] == std::string("-D"))
  {
    printf("Entering Daemon Mode");
    daemon(1, 0);
  }

  FILE * fp = fopen("ServerExe.pid", "wt");
  auto pid = std::to_string(getpid());
  fprintf(fp, "%s", pid.data());
  fclose(fp);
#endif

#ifdef _DEBUG
  g_LagSim = 100;
#endif

  printf("Game Server\n");

  InitServerTypes();
  RuntimeInit();

#ifdef NET_USE_WEBRTC
  StormWebrtcStaticInit();
#endif

  printf("  Loading assets...\n");

  GameLevelList level_list;
  level_list.PreloadAllLevels();

  if (level_list.IsPreloadComplete() == false)
  {
    printf("  Failed to load assets...\n");
    return 0;
  }

  GameServerGlobalResources server_global_resources;
  if (server_global_resources.IsLoaded() == false)
  {
    printf("  Failed to load assets...\n");
    return 0;
  }

  GameSharedGlobalResources shared_global_resources;
  if (shared_global_resources.IsLoaded() == false)
  {
    printf("  Failed to load assets...\n");
    return 0;
  }

  printf("  Assets loaded...\n");
  GameStageManager stage_manager(level_list);

  printf("  Starting server...\n");
  NetworkInit();

  GameServer game_server(256, 47816, stage_manager, shared_global_resources);
  printf("  Server started!\n");

  FrameClock frame_clock(1.0 / 60.0);
  frame_clock.Start();

  while (true)
  {
    game_server.Update();

    if (frame_clock.ShouldSkipFrameUpdate() == false)
    {
      frame_clock.BeginFrame();
      game_server.GetGameInstanceManager().Update();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  NetworkShutdown();

#ifdef NET_USE_WEBRTC
  StormWebrtcStaticCleanup();
#endif
}

