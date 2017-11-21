
#include <QtWidgets/QApplication>

#include "StormRefl/StormReflJsonStd.h"

#include "EditorContainer.h"

#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "Game/GameNetworkSettings.h"

#include "Runtime/FrameData/FrameData.refl.meta.h"

FrameDataDef g_FrameData;

#include <SDL2/SDL.h>
#undef main

#ifdef _MSC_VER
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#endif


void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();


int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("StormBrewers");
  QCoreApplication::setOrganizationDomain("StormBrewers.com");
  QCoreApplication::setApplicationName("StormBrewerEngine");

  File settings_file = FileOpen("editor.settings", FileOpenMode::kRead);
  auto buffer = settings_file.ReadFileFull();
  auto settings = BufferToString(buffer);

  StormReflParseJson(g_FrameData, settings.data());


#ifdef NET_USE_WEBRTC
  StormWebrtcStaticInit();
#endif
  NetworkInit();
  //QApplication::setAttribute(Qt::AA_UseOpenGLES);
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QApplication a(argc, argv);
  EditorContainer w;

  auto ret = a.exec();

#ifdef NET_USE_WEBRTC
  StormWebrtcStaticCleanup();
#endif
}
