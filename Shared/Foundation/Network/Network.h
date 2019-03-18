#pragma once

void NetworkInit();
void NetworkUpdate();
void NetworkShutdown();

bool ProbePort(const char * host, int port, int timeout);