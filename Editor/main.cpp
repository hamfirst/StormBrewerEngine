
#include <QtWidgets/QApplication>

#include "EditorContainer.h"

#include "Foundation/Network/Network.h"

#include <SDL2/SDL.h>
#undef main

#ifdef _MSC_VER
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#endif

int main(int argc, char *argv[])
{
  NetworkInit();
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QApplication a(argc, argv);
  EditorContainer w;
  return a.exec();
}
