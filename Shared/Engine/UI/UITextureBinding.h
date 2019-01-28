
#pragma once

#include "Engine/Asset/AssetReference.h"
#include "Engine/Asset/TextureAsset.h"

class UIManager;

class UITextureBinding
{
public:
  UITextureBinding();
  UITextureBinding(const UITextureBinding & rhs) = delete;
  UITextureBinding(UITextureBinding && rhs);

  ~UITextureBinding();

  UITextureBinding & operator = (const UITextureBinding & rhs) = delete;
  UITextureBinding & operator = (UITextureBinding && rhs);

  void SetTexture(Delegate<NullOptPtr<const Texture>> && tex);

  void Clear();
private:

  friend class UIManager;
  friend class UIScriptInterface;

  UITextureBinding(NotNullPtr<UIManager> ui_manager, int texture_id, Delegate<NullOptPtr<const Texture>> && tex);

  NotNullPtr<UIManager> m_UIManager;

  int m_TextureId;
  Delegate<NullOptPtr<const Texture>> m_TextureFetch;
};
