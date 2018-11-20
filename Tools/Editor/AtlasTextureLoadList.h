#pragma once

#include <QImage>

#include "Foundation/Delegate/DelegateList.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetSync.h"

#include "Runtime/Atlas/AtlasDef.refl.h"

#include "DocumentSubValueListMirror.h"

class AtlasEditor;

class AtlasTextureLoadList
{
public:
  AtlasTextureLoadList(NotNullPtr<AtlasEditor> editor, AtlasDef & atlas);

  NullOptPtr<TextureAsset> GetTexture(std::size_t index);

  DelegateLink<void> AddUpdateCallback(Delegate<void> && del);

private:

  void HandleTextureUpdate();

private:
  NotNullPtr<AtlasEditor> m_Editor;
  AtlasDef & m_Atlas;

  DocumentSubValueListMirror m_TextureList;
  Delegate<AssetSync<TextureAsset> *, std::size_t> m_GetTexture;

  DelegateList<void> m_UpdateCallbacks;
};