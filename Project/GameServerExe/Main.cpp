

#include <StormRefl/StormReflJsonStd.h>

#include "StormBootstrap/StormBootstrap.h"

#include "Foundation/Common.h"
#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Directory.h"
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

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectVersion.h"
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
#include <memdisk>

#include <net/inet>
#include <kernel/os.hpp>

int ReturnError(int err) { return err; }
void UpdateServers(GameServer & game_server, FrameClock & frame_clock);

#else
#include <thread>

int ReturnError(int err) { return err; }
#endif

double send_time;

bool g_QuitServer = false;
std::string g_ExternalIp;

extern int g_LagSim;

void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

int main(int argc, const char ** argv)
{
#ifdef _INCLUDEOS
  printf("Waiting for network configuration\n");

  auto & inet = net::Super_stack::get(0);
  bool configured = false;

  inet.on_config([&](auto & stack) { configured = true; });

  while(configured == false)
  {
    OS::block();
  }

#endif

  printf("Starting server!\n");

  StormBootstrap bootstrap(argc, argv);
  bootstrap.Set("external_ip", "127.0.0.1");

  bootstrap.RequestUrl("http://api.ipify.org", "", [&](const std::string & result)
  {
    printf("Got ip response %s\n", result.c_str());
    if(!result.empty())
    {
      bootstrap.Set("external_ip", result);
    }
  });

  auto meta_url = "http://metadata.google.internal/computeMetadata/v1/instance/attributes/";
  bootstrap.RequestUrl(meta_url, "Metadata-Flavor: Google\r\n", [&](const std::string & result)
  {
    if(!result.empty())
    {
      bootstrap.Set("meta", result);
    }
  });

  auto id_url = "http://metadata.google.internal/computeMetadata/v1/instance/id";
  bootstrap.RequestUrl(id_url, "Metadata-Flavor: Google\r\n", [&](const std::string & result)
  {
    if(!result.empty())
    {
      bootstrap.Set("id", result);
    }
  });

  auto zone_url = "http://metadata.google.internal/computeMetadata/v1/instance/zone";
  bootstrap.RequestUrl(zone_url, "Metadata-Flavor: Google\r\n", [&](const std::string & result)
  {
    if(!result.empty())
    {
      auto zone_pos = result.rfind('/');
      if(zone_pos != std::string::npos)
      {
        bootstrap.Set("zone", result.data() + zone_pos + 1);
      }
    }
  });

  auto name_url = "http://metadata.google.internal/computeMetadata/v1/instance/name";
  bootstrap.RequestUrl(name_url, "Metadata-Flavor: Google\r\n", [&](const std::string & result)
  {
    if(!result.empty())
    {
      bootstrap.Set("name", result);
    }
  });

  bootstrap.Run();
  bootstrap.PrintDebug();

  g_ExternalIp = bootstrap.Get("external_ip");

#if defined(_LINUX) && !defined(_INCLUDEOS)
  if (bootstrap.HasValue("D") || bootstrap.HasValue("daemon"))
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
