
#include <QtWidgets/QApplication>

#include "EditorContainer.h"

#include "Foundation/Network/Network.h"

#include <SDL/SDL.h>
#undef main

#ifdef _MSC_VER
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#endif

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
  {
    fprintf(stderr, "Could not start SDL");
    return 0;
  }

  NetworkInit();
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QApplication a(argc, argv);
  EditorContainer w;
  return a.exec();
}
