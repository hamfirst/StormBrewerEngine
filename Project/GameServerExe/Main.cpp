

#include <StormRefl/StormReflJsonStd.h>

#include "Foundation/Common.h"
#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"
#include "Foundation/Time/FrameClock.h"

#include "Runtime/Runtime.h"
#include "Runtime/Entity/EntityResource.h"
#include "Runtime/Map/MapResource.h"
#include "Runtime/Asset/Asset.h"

#include "Game/GameFullState.refl.meta.h"
#include "Game/GameMessages.refl.meta.h"
#include "Game/GameNetworkSettings.h"

#include "GameServer/GameServer.h"

#include "ProjectSettings/ProjectPorts.h"

#ifdef _MSC_VER
#pragma comment(lib, "Winmm.lib")
#endif

#ifdef _LINUX
#include <unistd.h>
#include <sys/types.h>
#endif

#ifdef _INCLUDEOS
#include <service>
#include <chrono>
#include <timers>
#include <debug>

int ReturnError(int err) { return 0; }
void UpdateServers(GameServer & game_server, FrameClock & frame_clock);

#else
#include <thread>

int ReturnError(int err) { return err; }
#endif

double send_time;

bool g_QuitServer = false;
extern int g_LagSim;

void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

int main(int argc, const char ** argv)
{
#if defined(_LINUX) && !defined(_INCLUDEOS)
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
  g_LagSim = 0;

#ifdef _INCLUDEOS
  GDB_ENTRY;
#endif
#endif

  // Get external ip http://api.ipify.org?format=json
  // Get meta data http://metadata.google.internal/computeMetadata/v1/instance/attributes/ -H "Metadata-Flavor: Google"


  printf("Game Server\n");

  InitServerTypes();
  RuntimeInit();

#if NET_BACKEND == NET_BACKEND_WEBRTC
  StormWebrtcStaticInit();
#endif

  printf("  Loading assets...\n");

  static GameLevelList level_list;
  level_list.PreloadAllLevels();

  if (level_list.IsPreloadComplete() == false)
  {
    printf("  Failed to load assets...\n");
    return ReturnError(0);
  }

  static ClientAssetLoader stub_loader;
  g_GlobalAssetList.BeginAssetLoad(&stub_loader);

  printf("  Assets loaded...\n");
  static GameStageManager stage_manager(level_list);

  printf("  Starting server...\n");
  NetworkInit();

  static GameServer game_server(256, GAME_PORT, stage_manager);
  printf("  Server started!\n");

  static FrameClock frame_clock(1.0 / 60.0);
  frame_clock.Start();

#ifndef _INCLUDEOS

  while (g_QuitServer == false)
  {
    game_server.Update();

    if (frame_clock.ShouldSkipFrameUpdate() == false)
    {
      frame_clock.BeginFrame();
      game_server.GetGameInstanceManager().Update();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  g_GlobalAssetList.UnloadAllAssets();

  NetworkShutdown();

#if NET_BACKEND == NET_BACKEND_WEBRTC
  StormWebrtcStaticCleanup();
#endif

#else

  UpdateServers(game_server, frame_clock);
  printf("Server update loop started\n");
#endif

  return 0;
}


#ifdef _INCLUDEOS

void UpdateServers(GameServer & game_server, FrameClock & frame_clock)
{
  if(g_QuitServer)
  {
    return;
  }

  game_server.Update();

  if (frame_clock.ShouldSkipFrameUpdate() == false)
  {
    frame_clock.BeginFrame();
    game_server.GetGameInstanceManager().Update();
  }

  Timers::oneshot(
		std::chrono::milliseconds(1),
		[&](auto)
		{
		  UpdateServers(game_server, frame_clock);
		}
  );
}

#endif
