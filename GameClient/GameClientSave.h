#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/SaveFile/SaveFile.h"

#include "GameClient/GameClientSaveFileData.refl.h"

class GameClientSave
{
public:
  GameClientSave(czstr save_file = "save");

  void Update();
  bool IsLoaded() const;

  GameClientSaveData & GetSaveData();
  void RequestSave();

private:

  SaveFile m_SaveFile;
  Optional<GameClientSaveData> m_SaveData;
};

