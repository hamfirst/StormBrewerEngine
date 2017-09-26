
#include "GameClient/GameClientSave.h"
#include "GameClient/GameClientSaveFileData.refl.meta.h"

#include "Engine/SaveFile/SaveFileMetaFuncs.h"

GameClientSave::GameClientSave(czstr save_file) :
  m_SaveFile(save_file)
{

}

void GameClientSave::Update()
{
  m_SaveFile.Update();

  if (m_SaveFile.IsLoadComplete() && m_SaveData == false)
  {
    m_SaveData.Emplace();
    m_SaveFile.ParseSaveData(m_SaveData.Value());
  }
}

bool GameClientSave::IsLoaded() const
{
  return m_SaveData;
}

GameClientSaveData & GameClientSave::GetSaveData()
{
  return m_SaveData.Value();
}

void GameClientSave::RequestSave()
{
  m_SaveFile.RequestSave(m_SaveData.Value());
}
