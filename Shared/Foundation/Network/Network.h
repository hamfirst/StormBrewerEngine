#pragma once

void NetworkInit();
void NetworkShutdown();

bool ProbePort(const char * host, int port, int timeout);