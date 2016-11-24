#pragma once

#include "Engine/Asset/Asset.h"
#include "Engine/Asset/AssetTypeMacros.h"
#include "Engine/Audio/AudioFormat.h"


class FontAsset : public Asset
{
protected:

  virtual void PreProcessLoadedData(Buffer & buffer) override;
  virtual bool OnDataLoadComplete(Buffer & buffer) override;

protected:
  friend class TextRenderer;

  Buffer m_FontBuffer;

public:
  ASSET_HEADER_FUNCS(FontAsset);
};
