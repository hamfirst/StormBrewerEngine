
#include "DocumentServer.h"

int main()
{
  printf("Starting document server\n");

  //try
  {
    DocumentServer server;
    server.Run();
  }
  //catch (...)
  {

  }
}

