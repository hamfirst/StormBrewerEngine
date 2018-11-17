#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class ENGINE_EXPORT FontAsset : public Asset
{
protected:

  virtual int PreProcessLoadedData(Buffer & buffer, bool load_deps) override;
  virtual void OnDataLoadComplete(Buffer & buffer, bool load_deps) override;

protected:
  friend class TextRenderer;

  Buffer m_FontBuffer;

public:
  ASSET_HEADER_FUNCS(FontAsset);
};
