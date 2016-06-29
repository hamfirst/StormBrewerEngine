
#include "StormSocketServerTypes.h"

#include <thread>

namespace StormSockets
{
  void StormSocketInitSettings::SetDefaults()
  {
    Port = 9001;
    LocalInterface = "0.0.0.0"; // Bind to all interfaces
    Protocol = NULL;

    UseMasking = true;
    ContinuationMode = StormSocketContinuationMode::Combine;

    NumIOThreads = std::thread::hardware_concurrency();
    NumSendThreads = std::thread::hardware_concurrency();
    MaxConnections = 256;

    HeapSize = 10 * 1024 * 1024; // 10 megs
    BlockSize = 4096; // The default page size

    MessageQueueSize = 128;

    MaxPendingOutgoingPacketsPerConnection = 32;
    MaxPendingFreeingPacketsPerConnection = 32;
    MaxPendingIncomingPacketsPerConnection = 32;
    MaxSendQueueElements = 32;

    CertificateFile = nullptr;
    PrivateKeyFile = nullptr;
  }

}

