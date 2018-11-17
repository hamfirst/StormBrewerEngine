

#include "Engine/EngineCommon.h"
#include "Engine/SaveFile/SaveFile.h"

#include "Foundation/FileSystem/File.h"
#include "Foundation/FileSystem/Path.h"
#include "Foundation/Buffer/BufferUtil.h"

#include <cstdlib>
#include <cstring>

#ifdef _WEB
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>
#endif

#ifdef _ANDROID
#include "SDL2/SDL_system.h"
#endif

SaveFile::SaveFile(czstr save_file) :
  m_SaveFileName(save_file)
{
#ifdef _WEB
  ptrdiff_t ptr_val = EM_ASM_INT({
    var save_file_name = Module.UTF8ToString($0);
    var save_data = localStorage.getItem(save_file_name);
    if (save_data == null) return 0;
    var save_data_len = save_data.length;
    var ptr = Module._malloc(save_data_len * 4 + 1);
    Module.stringToUTF8(save_data, ptr, save_data_len * 4 + 1);
    return ptr;
  }, save_file);

  czstr data = reinterpret_cast<czstr>(ptr_val);
  if (data != nullptr)
  {
    m_SaveData.Emplace(data);
    free((void *)data);
    m_LoadComplete = true;
  }
  else
  {
    m_SaveData.Emplace();
  }

  m_LoadComplete = true;
#else
  m_SaveFileThread = std::thread(&SaveFile::SaveFileThreadMain, this);
#endif
}

SaveFile::~SaveFile()
{
#ifndef _WEB
  m_RequestStop = true;
  m_SaveFileSemaphore.Release();
  m_SaveFileThread.join();
#endif
}


void SaveFile::Update()
{
#ifndef _WEB
  if (m_QueuedSaveData && m_SaveActive == false)
  {
    m_PendingSaveData = std::move(m_QueuedSaveData.Value());
    m_SaveActive = true;
    m_SaveFileSemaphore.Release();
    m_QueuedSaveData.Clear();
  }
#endif
}

bool SaveFile::IsLoadComplete() const
{
  return m_LoadComplete;
}

void SaveFile::RequestSaveInternal()
{
#ifdef _WEB
  EM_ASM_({
    var data = Module.UTF8ToString($0);
    var save_file_name = Module.UTF8ToString($1);
    localStorage.setItem(save_file_name, data);
  }, m_SaveData->data(), m_SaveFileName.data());
#else
  if (m_SaveActive)
  {
    m_QueuedSaveData = m_SaveData;
  }
  else
  {
    m_PendingSaveData = m_SaveData.Value();
    m_SaveActive = true;
    m_SaveFileSemaphore.Release();
  }
#endif
}

#ifndef _WEB

std::string SaveFile::GetSaveFileLocation()
{
#ifdef _MSC_VER
  auto app_data = getenv("APPDATA");
  if (app_data == nullptr)
  {
    return ".";
  }

  std::string folder = app_data;
  folder += "\\StormBrewer";

  return folder;

#elif defined(_IOS)
  std::string path = "Documents/sb_save";
  return path;
#elif defined(_ANDROID)
  std::string path = SDL_AndroidGetExternalStoragePath();
  path += "/sb_save";
  return path;
#else
  return "~/.sb";
#endif
}

void SaveFile::SaveFileThreadMain()
{
  auto save_file_location = GetSaveFileLocation();
  CreateDirectory(save_file_location);

  auto save_file = JoinPath(save_file_location, m_SaveFileName);
  auto file = FileOpen(save_file.data(), FileOpenMode::kRead);

  if (file.GetFileOpenError() == 0)
  {
    auto buffer = file.ReadFileFull();
    auto data = BufferToString(buffer);

    m_SaveData.Emplace(std::move(data));
    FileClose(file);
  }
  else
  {
    m_SaveData.Emplace();
  }

  m_LoadComplete = true;
  std::string * volatile pending_data = &m_PendingSaveData;

  while (m_RequestStop == false)
  {
    m_SaveFileSemaphore.WaitOne();

    if (m_SaveActive)
    {
      auto file = FileOpen(save_file.data(), FileOpenMode::kWrite);
      file.Write(*pending_data);
      FileClose(file);

      m_SaveActive = false;
    }
  }
}

#endif
