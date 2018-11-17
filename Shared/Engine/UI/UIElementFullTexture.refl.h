#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/UI/UICustomPropertyData.refl.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementFullTextureInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementFullTextureInitData);

  RString STORM_REFL_ATTR_VAL(file, image) m_TextureFile;
};

struct UIElementFullTextureData : public UIElementDataFrameCenter
{
  STORM_REFL;

  float m_ScaleX = 1.0f;
  float m_ScaleY = 1.0f;
};

class RenderState;

class UIElementFullTexture : public UIElement
{
public:
  UIElementFullTexture(const UIElementFullTextureInitData & init_data, const UIElementFullTextureData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementFullTextureInitData & GetInitData();
  UIElementFullTextureData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementFullTexture &, RenderState &, const Vector2 &> && render_callback);

  AssetReference<TextureAsset> & GetTextureAsset();

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementFullTextureInitData m_InitData;
  UIElementFullTextureData m_Data;

  Delegate<void, UIElementFullTexture &, RenderState &, const Vector2 &> m_RenderDelegate;
  AssetReference<TextureAsset> m_Texture;
};

