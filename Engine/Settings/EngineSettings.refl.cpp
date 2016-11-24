
#include "Engine/EngineCommon.h"

#include <StormRefl/StormReflJsonStd.h>

#include "Foundation/FileSystem/File.h"
#include "EngineSettings.refl.meta.h"

EngineSettings g_EngineSettings;

void LoadEngineSettingsFile()
{
  auto file = FileOpen("engine.settings", FileOpenMode::kRead);
  if (file.GetFileOpenError())
  {
    return;
  }

  std::string sb;
  sb.resize(file.GetFileLength() + 1);
  file.Read(gsl::span<uint8_t>((uint8_t *)sb.data(), file.GetFileLength()), file.GetFileLength());

  StormReflParseJson(g_EngineSettings, sb.data());
}

