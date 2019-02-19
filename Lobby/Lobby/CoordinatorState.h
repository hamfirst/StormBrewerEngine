#pragma once

#include <HurricaneDDS/DDSCoordinatorState.h>

std::unique_ptr<DDSCoordinatorState> CreateCoordinatorState(bool reset_db, 
  const char * database_host_addr = "localhost", int database_port = 27017);

