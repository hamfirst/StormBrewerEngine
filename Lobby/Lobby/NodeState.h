#pragma once

#include <HurricaneDDS/DDSNodeState.h>

std::unique_ptr<DDSNodeState> CreateNodeState(const char * html_path,
  const char * coordinator_host_addr = "localhost", int coordinator_port = 9001, 
  const char * database_host_addr = "localhost", int database_port = 27017,
  int node_network_port = 8000, int user_port = 7999, int game_server_port = 8001, int bot_endpoint_port = 8002,
  int http_port = 80, int http_ticket_port = 8080);

