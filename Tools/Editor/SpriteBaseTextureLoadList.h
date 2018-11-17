#pragma once

#include <QImage>

#include "Foundation/Delegate/DelegateList.h"

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetSync.h"

#include "Runtime/Sprite/SpriteDef.refl.h"

#include "DocumentSubValueListMirror.h"

class SpriteBaseEditor;

class SpriteBaseTextureLoadList
{
public:
  SpriteBaseTextureLoadList(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite);

  NullOptPtr<TextureAsset> GetTexture(std::size_t index);

  DelegateLink<void> AddUpdateCallback(Delegate<void> && del);

  Optional<uint64_t> GetDefaultFrame();
  Optional<QImage> GetFrameAndImage(uint64_t frame_id, int & src_x, int & src_y, int & src_w, int & src_h);

private:

  void HandleTextureUpdate();

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;

  DocumentSubValueListMirror m_TextureList;
  Delegate<AssetSync<TextureAsset> *, std::size_t> m_GetTexture;

  DelegateList<void> m_UpdateCallbacks;
};