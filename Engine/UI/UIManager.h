#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementContainer.refl.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementTextureSlice.refl.h"
#include "Engine/UI/UIElementSpriteFrame.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/UIElementFullTexture.refl.h"
#include "Engine/UI/UIElementTextInput.refl.h"

class UIElement;
class InputState;

class UIManager
{
public:

  void Update(InputState & input_state, RenderState & render_state);
  void Render(RenderState & render_state, RenderUtil & render_util);

  UIElementPtr<UIElementContainer> AllocateContainer(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementContainerInitData & init_data = {}, const UIElementContainerData & data = {});

  UIElementPtr<UIElementGradient> AllocateGradient(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementGradientInitData & init_data = {}, const UIElementGradientData & data = {});

  UIElementPtr<UIElementTextureSlice> AllocateTextureSlice(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementTextureSliceInitData & init_data = {}, const UIElementTextureSliceData & data = {});

  UIElementPtr<UIElementSpriteFrame> AllocateSpriteFrame(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementSpriteFrameInitData & init_data = {}, const UIElementSpriteFrameData & data = {});

  UIElementPtr<UIElementText> AllocateText(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementTextInitData & init_data = {}, const UIElementTextData & data = {});

  UIElementPtr<UIElementShape> AllocateShape(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementShapeInitData & init_data = {}, const UIElementShapeData & data = {});

  UIElementPtr<UIElementFullTexture> AllocateFullTexture(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementFullTextureInitData & init_data = {}, const UIElementFullTextureData & data = {});

  UIElementPtr<UIElementTextInput> AllocateTextInput(czstr name, std::shared_ptr<TextInputContext> && input_context, NullOptPtr<UIElement> parent = nullptr,
    const UIElementTextInputInitData & init_data = {}, const UIElementTextInputData & data = {});

  

  bool HasSelectedElement() const;

protected:

  friend class UIElementHandle;
  friend class UIElement;

  template <typename ElementType, typename InitData, typename BlockData>
  NotNullPtr<ElementType> AllocateUIElement(czstr name, SkipField<ElementType> & alloc, NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data);

  template <typename ElementType, typename InitData, typename BlockData, typename Param>
  NotNullPtr<ElementType> AllocateUIElement(czstr name, SkipField<ElementType> & alloc, NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data, Param && param);

  NotNullPtr<UIElement> ResolveHandle(uint32_t type, Handle & handle);
  void UnlinkElement(NotNullPtr<UIElement> element);
  void ReleaseElement(NotNullPtr<UIElement> element);

  void SetupActiveElementsList(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, NotNullPtr<UIElement>, const Vector2 & offset);
  void ProcessActiveAreas(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, InputState & input_state, RenderState & render_state);

private:

  std::vector<NotNullPtr<UIElement>> m_RootElements;
  bool m_HasSelectedElement = false;
};

