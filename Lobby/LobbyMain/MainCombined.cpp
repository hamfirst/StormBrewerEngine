

#include "Lobby/NodeState.h"
#include "Lobby/CoordinatorState.h"
#include "Lobby/LoadBalancer.h"

#include <HurricaneDDS/DDSDatabaseSetup.h>
#include <HurricaneDDS/DDSShutdown.h>
#include <HurricaneDDS/DDSCPUUsage.h>

#pragma comment(lib, "Bcrypt.lib")


#ifdef _LINUX
#include <unistd.h>
#endif

#include <chrono>

extern bool g_LoadRewards;

int main(int argc, char ** argv)
{
#ifdef _LINUX
  if (argc >= 2 && argv[1] == std::string("-D"))
  {
    printf("Entering Daemon Mode");
    daemon(1, 0);
  }
#endif

  DDSDatabaseInit();
  DDSCPUUsageInit();
  //DDSSetupShutdownSignalHandler();

  bool reset = false;
  if (argc == 2 && argv[1] == std::string("reset"))
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
  if (argc >= 2 && argv[1][0] != '-')
  {
    html_dir = argv[1];
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


