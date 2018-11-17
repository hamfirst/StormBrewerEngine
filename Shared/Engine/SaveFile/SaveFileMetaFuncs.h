#pragma once

#include "Engine/SaveFile/SaveFile.h"
#include "StormRefl/StormReflJsonStd.h"

template <typename DataType>
bool SaveFile::ParseSaveData(DataType & data_type)
{
  return StormReflParseJson(data_type, m_SaveData->data());
}

template <typename DataType>
void SaveFile::RequestSave(const DataType & data_type)
{
  m_SaveData = StormReflEncodeJson(data_type);
  RequestSaveInternal();
}
