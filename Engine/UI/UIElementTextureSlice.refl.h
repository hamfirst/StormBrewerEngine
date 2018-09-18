#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UICustomPropertyData.refl.h"
#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/VertexBuffer.h"

#include "Runtime/UI/UIDef.refl.h"

struct UIElementTextureSliceInitData : public UIElementInitDataBase
{
  STORM_DATA_DEFAULT_CONSTRUCTION(UIElementTextureSliceInitData);

  RString STORM_REFL_ATTR_VAL(file, image) m_SpriteFile;

  RBool m_SliceHorizontally = false;
  RBool m_SliceVertically = false;

  RInt m_StartX = 0;
  RInt m_StartY = 0;
  RInt m_EndX = 10;
  RInt m_EndY = 10;

  RInt m_StartCutX = 3;
  RInt m_StartCutY = 3;
  RInt m_EndCutX = 3;
  RInt m_EndCutY = 3;
};

struct UIElementTextureSliceData : public UIElementDataStartEnd
{
  STORM_REFL;
};

class RenderState;

class UIElementTextureSlice : public UIElement
{
public:
  UIElementTextureSlice(const UIElementTextureSliceInitData & init_data, const UIElementTextureSliceData & data = {});

  static UIElementType Type;

  void Update(float dt) override;
  void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset) override;
  void RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  const UIElementTextureSliceInitData & GetInitData();
  UIElementTextureSliceData & GetData();

  virtual NotNullPtr<UIElementDataBase> GetBaseData() override;
  virtual NullOptPtr<UIElementDataFrameCenter> GetFrameCenterData() override;
  virtual NullOptPtr<UIElementDataStartEnd> GetStartEndData() override;

  void SetCustomRenderCallback(Delegate<void, UIElementTextureSlice &, RenderState &, const Vector2 &> && render_callback);

  AssetReference<TextureAsset> & GetTextureAsset();

protected:

  virtual StormExprValueInitBlock & GetLocalInitBlock() override;
  virtual StormExprValueInitBlock & GetAsParentInitBlock() override;
  virtual StormExprBindingList & GetBindingList() override;

private:

  UIElementTextureSliceInitData m_InitData;
  UIElementTextureSliceData m_Data;

  Delegate<void, UIElementTextureSlice &, RenderState &, const Vector2 &> m_RenderDelegate;
  AssetReference<TextureAsset> m_Texture;
};

