#pragma once

#include "Engine/EngineCommon.h"

#ifndef _WEB
#include "Foundation/Thread/Semaphore.h"
#endif

#include <thread>

class SaveFile
{
public:

  SaveFile(czstr save_file = "save");
  ~SaveFile();

  void Update();
  bool IsLoadComplete() const;

  template <typename DataType>
  bool ParseSaveData(DataType & data_type);

  template <typename DataType>
  void RequestSave(const DataType & data_type);

private:

  void RequestSaveInternal();

private:

  std::string m_SaveFileName;
  Optional<std::string> m_SaveData;

  volatile bool m_LoadComplete = false;

#ifndef _WEB

  std::thread m_SaveFileThread;
  Semaphore m_SaveFileSemaphore;
  volatile bool m_RequestStop = false;

  std::string m_PendingSaveData;
  volatile bool m_SaveActive = false;

  Optional<std::string> m_QueuedSaveData;
  
  static std::string GetSaveFileLocation();
  void SaveFileThreadMain();

#endif
};


