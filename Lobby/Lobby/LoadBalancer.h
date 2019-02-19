#pragma once

#include <HurricaneDDS/DDSLoadBalancer.h>

std::unique_ptr<DDSLoadBalancer> CreateLoadBalancer(
  const char * coordinator_host = "localhost", int coordinator_port = 9002, int server_port = 9050);