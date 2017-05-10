
#include "Engine/EngineCommon.h"
#include "Engine/Asset/DocumentAsset.h"
#include "Engine/Asset/AssetManager.h"

#include "Foundation/Buffer/BufferUtil.h"

#include "StormRefl/StormReflJson.h"
#include "StormRefl/StormReflJsonStd.h"

ASSET_SOURCE_FUNCS(DocumentAsset)

struct DocumentData
{
  std::string m_JsonData;
  std::vector<std::string> m_AssetRefs;
};


bool DocumentRefParseOverValue(const char * str, const char *& result, std::vector<std::string> & asset_refs);

bool DocumentRefParseOverObject(const char * str, const char *& result, std::vector<std::string> & asset_refs)
{
  if (*str != '{')
  {
    return false;
  }

  str++;
  while (true)
  {
    StormReflJsonAdvanceWhiteSpace(str);
    if (*str == '}')
    {
      str++;
      result = str;
      return true;
    }

    if (StormReflJsonParseOverString(str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ':')
    {
      return false;
    }

    str++;

    StormReflJsonAdvanceWhiteSpace(str);
    if (DocumentRefParseOverValue(str, str, asset_refs) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != '}')
    {
      if (*str != ',')
      {
        return false;
      }
      else
      {
        str++;
      }
    }
  }
}

inline bool DocumentJsonParseOverArray(const char * str, const char *& result, std::vector<std::string> & asset_refs)
{
  if (*str != '[')
  {
    return false;
  }

  str++;
  StormReflJsonAdvanceWhiteSpace(str);

  while (true)
  {
    if (*str == ']')
    {
      str++;
      result = str;
      return true;
    }

    if (DocumentRefParseOverValue(str, str, asset_refs) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (*str != ']')
    {
      if (*str != ',')
      {
        return false;
      }
      else
      {
        str++;
        StormReflJsonAdvanceWhiteSpace(str);
      }
    }
  }
}

bool DocumentRefParseOverString(const char * str, const char *& result, std::vector<std::string> & asset_refs)
{
  if (StormReflJsonParseOverString(str, result) == false)
  {
    return false;
  }

  if (str[1] == '.')
  {
    std::string asset_ref;
    StormReflParseJson(asset_ref, str);

    if (asset_ref[1] == '/')
    {
      asset_refs.emplace_back(std::move(asset_ref));
    }
  }

  return true;
}

bool DocumentRefParseOverValue(const char * str, const char *& result, std::vector<std::string> & asset_refs)
{
  StormReflJsonAdvanceWhiteSpace(str);
  if (StormReflJsonParseOverNumber(str, result))
  {
    return true;
  }
  if (DocumentRefParseOverString(str, result, asset_refs))
  {
    return true;
  }
  if (StormReflJsonParseOverTrue(str, result))
  {
    return true;
  }
  if (StormReflJsonParseOverFalse(str, result))
  {
    return true;
  }
  if (StormReflJsonParseOverNull(str, result))
  {
    return true;
  }
  if (DocumentRefParseOverObject(str, result, asset_refs))
  {
    return true;
  }
  if (DocumentJsonParseOverArray(str, result, asset_refs))
  {
    return true;
  }

  return false;
}

int DocumentAsset::PreProcessLoadedData(Buffer & buffer)
{
  DocumentData data;

  data.m_JsonData = BufferToString(buffer);
  const char * ptr = data.m_JsonData.data();
  if (DocumentRefParseOverValue(ptr, ptr, data.m_AssetRefs) == false)
  {
    return 1;
  }

  buffer = MoveToBuffer(std::move(data));
  return 0;
}

void DocumentAsset::OnDataLoadComplete(Buffer & buffer)
{
  m_ReferencedAssets.clear();
  m_SetupReferences = false;

  DocumentData data = MoveFromBuffer<DocumentData>(buffer);


  m_ReferencedAssets.reserve(data.m_AssetRefs.size());
  for (auto & ref : data.m_AssetRefs)
  {
    m_ReferencedAssets.emplace_back(DocumentAssetReference{ false, false, LoadAsset(ref.data()) });
  }

  for(std::size_t index = 0, end = m_ReferencedAssets.size(); index < end; ++index)
  {
    auto asset = m_ReferencedAssets[index].m_Reference.Resolve();
    if (asset)
    {
      m_ReferencedAssets[index].m_LoadLink = asset->AddLoadCallback([this, index](Asset * asset) 
        { 
          m_ReferencedAssets[index].m_Loaded = true; 
          m_ReferencedAssets[index].m_Success = asset->IsLoaded(); 
          CheckCompleteLoad();
        });
    }
  }

  m_AssetData = std::move(data.m_JsonData);

  m_SetupReferences = true;
  CheckCompleteLoad();
}

void DocumentAsset::CheckCompleteLoad()
{
  if (m_SetupReferences == false)
  {
    return;
  }

  bool all_complete = true;
  bool all_success = true;

  for (auto & ref : m_ReferencedAssets)
  {
    if (ref.m_Success == false)
    {
      all_success = false;
    }

    if (ref.m_Loaded == false)
    {
      all_complete = false;
    }
  }

  if (all_complete)
  {
    if (all_success)
    {
      FinalizeAssetLoad();
    }
    else if(m_State != AssetState::kLoadError)
    {
      CallAssetLoadCallbacksWithFailure();
    }
  }
}

std::string & DocumentAsset::GetAssetData()
{
  return m_AssetData;
}
