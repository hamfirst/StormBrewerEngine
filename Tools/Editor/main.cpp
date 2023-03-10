
#include <QApplication>
#include <QSurfaceFormat>

#include "StormRefl/StormReflJsonStd.h"

#include "EditorContainer.h"

#include "Foundation/Network/Network.h"
#include "Foundation/FileSystem/File.h"
#include "Foundation/Buffer/BufferUtil.h"

#include "ProjectSettings/ProjectNetworkSettings.h"

#include "Runtime/FrameData/FrameData.refl.meta.h"

FrameDataDef g_FrameData;

#include <SDL2/SDL.h>
#undef main

#ifdef _MSC_VER
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")

bool g_UseEGL = false;

#else

bool g_UseEGL = false;

#endif


void StormWebrtcStaticInit();
void StormWebrtcStaticCleanup();

extern const char * g_QtStyle;

int main(int argc, char *argv[])
{

  QCoreApplication::setOrganizationName("StormBrewers");
  QCoreApplication::setOrganizationDomain("StormBrewers.com");
  QCoreApplication::setApplicationName("StormBrewerEngine");

  File settings_file = FileOpen("editor_settings.txt", FileOpenMode::kRead);
  auto buffer = settings_file.ReadFileFull();
  auto settings = BufferToString(buffer);

  StormReflParseJson(g_FrameData, settings.data());


#if NET_BACKEND == NET_BACKEND_WEBRTC
  StormWebrtcStaticInit();
#endif

  if (g_UseEGL)
  {
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
  }

  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QSurfaceFormat format;
  format.setSamples(4);
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(3, 3);

#if defined(_DEBUG) || defined(QT_DEBUG)
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setOption(QSurfaceFormat::DebugContext);
#endif

  QSurfaceFormat::setDefaultFormat(format);

  QApplication a(argc, argv);
  //a.setStyleSheet(g_QtStyle);

  EditorContainer w;

  auto ret = a.exec();

  return 0;
}
