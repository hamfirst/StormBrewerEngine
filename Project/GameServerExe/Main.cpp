

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

#include "Game/State/GameFullState.refl.meta.h"
#include "Game/NetworkEvents/GameMessages.refl.meta.h"

#include "GameServer/GameServer.h"

#include "Lobby/GameServerMessages.refl.meta.h"
#include "LobbyServerConnection/LobbyServerConnection.h"

#include "ProjectSettings/ProjectName.h"
#include "ProjectSettings/ProjectVersion.h"
#include "ProjectSettings/ProjectPorts.h"
#include "ProjectSettings/ProjectNetworkSettings.h"

#ifdef _MSC_VER
#pragma comment(lib, "Winmm.lib")
#endif

#ifdef _LINUX
#include <unistd.h>
#include <sys/types.h>
#endif

#include <thread>

int ReturnError(int err) { return err; }

double send_time;

bool g_QuitServer = false;

extern int g_LagSim;

void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

int main(int argc, const char ** argv)
{
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

  if(bootstrap.HasValue("D"))
  {
    bootstrap.Set("external_ip", "127.0.0.1");
    bootstrap.Set("external_port", std::to_string(DEFAULT_GAME_PORT));
    bootstrap.Set("zone", "Debug");
    bootstrap.Set("name", "DebugServer");
    bootstrap.Set("id", "");
  }

  bootstrap.PrintDebug();

  GameServerLobbySettings lobby_server_settings;
  StormReflParseJson(lobby_server_settings, bootstrap.Get("meta"));

  GameServerInfo game_server_info;
  game_server_info.m_ServerName = bootstrap.Get("name");
  game_server_info.m_ServerZone = bootstrap.Get("zone");
  game_server_info.m_ServerResourceId = bootstrap.Get("id");
  game_server_info.m_ExternalIp = bootstrap.Get("external_ip");

  auto external_port = atoi(bootstrap.Get("external_port").c_str());
  if(external_port != 0)
  {
    game_server_info.m_ExternalPort = external_port;
  }

#if defined(_LINUX)
  FILE * fp = fopen("ServerExe.pid", "wt");
  auto pid = std::to_string(getpid());
  fprintf(fp, "%s", pid.data());
  fclose(fp);
#endif

#ifdef _DEBUG
  g_LagSim = 0;
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

  static LobbyServerConnection lobby_server_connection(lobby_server_settings, game_server_info);
  printf("  Connecting to lobby...\n");

  static GameServer game_server(256, game_server_info.m_ExternalPort, stage_manager, &lobby_server_connection);
  printf("  Server started!\n");

  static FrameClock frame_clock(1.0 / 60.0);
  frame_clock.Start();

  while (g_QuitServer == false && game_server.WantsToQuit() == false)
  {
    NetworkUpdate();
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

  return 0;
}
