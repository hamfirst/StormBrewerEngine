
#include "LoadBalancer.h"

std::unique_ptr<DDSLoadBalancer> CreateLoadBalancer(const char * coordinator_host, int coordinator_port, int server_port)
{
  StormSockets::StormSocketInitSettings backend_settings;
  backend_settings.NumIOThreads = 2;
  backend_settings.NumSendThreads = 2;
  backend_settings.MaxConnections = 1024;

  StormSockets::StormSocketServerFrontendWebsocketSettings server_settings;
  server_settings.ListenSettings.Port = server_port;

  DDSLoadBalancerSettings settings;
  settings.CoordinatorIpAddr = coordinator_host;
  settings.CoordinatorPort = coordinator_port;

  return std::make_unique<DDSLoadBalancer>(backend_settings, server_settings, settings);
}
