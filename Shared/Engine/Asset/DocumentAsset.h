#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetLoad.h"
#include "Engine/Asset/AssetTypeMacros.h"


class ENGINE_EXPORT DocumentAsset : public Asset
{
public:

  std::string & GetAssetData();

protected:

  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;

  void CheckCompleteLoad();

protected:

  struct DocumentAssetReference
  {
    bool m_Loaded;
    bool m_Success;
    GenericAssetReference m_Reference;
    GenericLoadCallbackLink m_LoadLink;
  };

  std::vector<DocumentAssetReference> m_ReferencedAssets;
  bool m_SetupReferences = false;

  std::string m_AssetData;

public:
  ASSET_HEADER_FUNCS(DocumentAsset);
};
