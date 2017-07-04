#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementContainer.refl.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementTextureSlice.refl.h"
#include "Engine/UI/UIElementSpriteFrame.refl.h"
#include "Engine/UI/UIElementText.refl.h"


class UIElement;

class UIManager
{
public:

  void Update();
  void Render(RenderState & render_state, RenderUtil & render_util);

  NotNullPtr<UIElementContainer> AllocateContainer(czstr name, NullOptPtr<UIElement> parent,
    const UIElementContainerInitData & init_data, const UIElementContainerData & data = {});

  NotNullPtr<UIElementGradient> AllocateGradient(czstr name, NullOptPtr<UIElement> parent,
    const UIElementGradientInitData & init_data, const UIElementGradientData & data = {});

  NotNullPtr<UIElementTextureSlice> AllocateTextureSlice(czstr name, NullOptPtr<UIElement> parent,
    const UIElementTextureSliceInitData & init_data, const UIElementTextureSliceData & data = {});

  NotNullPtr<UIElementSpriteFrame> AllocateSpriteFrame(czstr name, NullOptPtr<UIElement> parent,
    const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data = {});

  NotNullPtr<UIElementText> AllocateText(czstr name, NullOptPtr<UIElement> parent,
    const UIElementTextInitData & init_data, const UIElementTextData & data = {});

protected:

  friend class UIElementHandle;

  template <typename ElementType, typename InitData, typename BlockData>
  NotNullPtr<ElementType> AllocateUIElement(czstr name, SkipField<ElementType> & alloc, NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data);

  NotNullPtr<UIElement> ResolveHandle(uint32_t type, Handle & handle);
  void UnlinkElement(NotNullPtr<UIElement> element);
  void ReleaseElement(NotNullPtr<UIElement> element);

private:

  std::vector<NotNullPtr<UIElement>> m_RootElements;
};

