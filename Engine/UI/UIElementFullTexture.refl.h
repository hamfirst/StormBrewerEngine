#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementFullTextureInitData : public UIElementDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementFullTextureInitData);

  RString STORM_REFL_ATTR_VAL(file, image) m_TextureFile;
};

struct UIElementFullTextureData
{
  STORM_REFL;

  float m_CenterX = 0.0f;
  float m_CenterY = 0.0f;
  float m_ScaleX = 1.0f;
  float m_ScaleY = 1.0f;
  float m_Angle = 0.0f;
  float m_Enabled = 1.0f;

  float m_ColorR = 1.0f;
  float m_ColorG = 1.0f;
  float m_ColorB = 1.0f;
  float m_ColorA = 1.0f;

  float m_Active = 0.0f;
};

class RenderState;

class UIElementFullTexture : public UIElement
{
public:
  UIElementFullTexture(const UIElementFullTextureInitData & init_data, const UIElementFullTextureData & data = {});

  static UIElementType Type;

  void Update() override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementFullTextureInitData & GetInitData();
  UIElementFullTextureData & GetData();

  void SetCustomRenderCallback(Delegate<void, UIElementFullTexture &, RenderState &, const Vector2 &> && render_callback);

  AssetReference<TextureAsset> & GetTextureAsset();

protected:

  virtual StormExprValueInitBlock GetLocalBlock() override;
  virtual StormExprValueInitBlock GetAsParentBlock() override;
  virtual UIElementExprBindingList CreateBindingList() override;

private:

  UIElementFullTextureInitData m_InitData;
  UIElementFullTextureData m_Data;

  Delegate<void, UIElementFullTexture &, RenderState &, const Vector2 &> m_RenderDelegate;
  AssetReference<TextureAsset> m_Texture;
};

