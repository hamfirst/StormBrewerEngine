

#include "Lobby/NodeState.h"
#include "Lobby/CoordinatorState.h"
#include "Lobby/LoadBalancer.h"

#include <HurricaneDDS/DDSDatabaseSetup.h>
#include <HurricaneDDS/DDSShutdown.h>
#include <HurricaneDDS/DDSCPUUsage.h>
#include <HurricaneDDS/DDSEncoding.h>

#include "StormBootstrap/StormBootstrap.h"

#pragma comment(lib, "Bcrypt.lib")


#ifdef _LINUX
#include <unistd.h>
#endif

#include <chrono>

bool g_LoadRewards = false;
std::string g_ExternalIp;


int main(int argc, const char ** argv)
{
  StormBootstrap bootstrap(argc, argv);
  bootstrap.Set("external_ip", "127.0.0.1");

  bootstrap.RequestUrl("http://api.ipify.org", "", [&](const std::string & result)
  {
    if(!result.empty())
    {
      bootstrap.Set("external_ip", result);
    }
  });

  bootstrap.Run();

  g_ExternalIp = bootstrap.Get("external_ip");

#ifdef _LINUX
  if (bootstrap.HasValue("D") || bootstrap.HasValue("daemon"))
  {
    printf("Entering Daemon Mode");
    daemon(1, 0);
  }
#endif

  DDSDatabaseInit();
  DDSCPUUsageInit();
  //DDSSetupShutdownSignalHandler();

  bool reset = false;
  if (bootstrap.HasValue("reset"))
  {
    reset = true;
  }

  g_LoadRewards = true;

#ifdef _DEBUG
  auto coordinator = CreateCoordinatorState(true);
#else
  auto coordinator = CreateCoordinatorState(reset);
#endif
  if (reset)
  {
    DDSShutdown();
    DDSDatabaseCleanup();
    return 0;
  }

  //DDSShutdownRegisterCoordinator(coordinator.get());

  const char * html_dir = nullptr;
  if (bootstrap.GetNumArgs() > 0)
  {
    html_dir = bootstrap.GetArg(0).data();
  }

  NodeSettings node_settings;
  node_settings.m_HTMLPath = html_dir;
  auto node = CreateNodeState(node_settings);

  auto load_balancer = CreateLoadBalancer();

  //DDSShutdownRegisterNode(node.get());

  while (DDSWantsShutdown() == false)
  {
    coordinator->ProcessEvents();
    node->ProcessEvents();
    load_balancer->ProcessEvents();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  DDSShutdown();
  DDSDatabaseCleanup();
}


