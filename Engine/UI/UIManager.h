#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIClickable.h"
#include "Engine/UI/UIClickablePtr.h"
#include "Engine/UI/UIElementPtr.h"
#include "Engine/UI/UIElementContainer.refl.h"
#include "Engine/UI/UIElementGradient.refl.h"
#include "Engine/UI/UIElementTextureSlice.refl.h"
#include "Engine/UI/UIElementSpriteFrame.refl.h"
#include "Engine/UI/UIElementText.refl.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/UI/UIElementFullTexture.refl.h"
#include "Engine/UI/UIElementTextInput.refl.h"

#include "StormExpr/StormExprFunctionList.h"

class UIElement;
class InputState;
class Window;

class UIManager
{
public:

  UIManager(Window & container_window);

  void Update(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset = Vector2(0, 0));
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

  UIElementPtr<UIElementTextInput> AllocateTextInput(czstr name, NullOptPtr<UIElement> parent = nullptr,
    const UIElementTextInputInitData & init_data = {}, const UIElementTextInputData & data = {});

  UIElementHandle AllocateElementFromDef(czstr name, const UIDef & def, NullOptPtr<UIElement> parent = nullptr);

  static uint32_t GetElementTypeNameHashForEnum(UIElementType type);
  static std::vector<std::string> GetVariablesForElementType(uint32_t element_type_hash);

  UIClickablePtr AllocateClickable(const Box & active_area);

  UIElementHandle GetElementByPath(czstr path);

  bool HasSelectedElement() const;

protected:

  friend class UIElementHandle;
  friend class UIElement;
  friend class UIClickable;

  template <typename ElementType, typename InitData, typename BlockData>
  NotNullPtr<ElementType> AllocateUIElement(czstr name, SkipField<ElementType> & alloc, NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data);

  template <typename ElementType, typename InitData, typename BlockData, typename Param>
  NotNullPtr<ElementType> AllocateUIElement(czstr name, SkipField<ElementType> & alloc, NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data, Param && param);

  UIElementHandle AllocateElementFromInitData(czstr name, NullOptPtr<UIElement> parent, uint32_t type_name_hash, const UIElementDataBase * init_data);

  NotNullPtr<UIElement> ResolveHandle(UIElementType type, Handle & handle);
  void UnlinkElement(NotNullPtr<UIElement> element);
  void ReleaseElement(NotNullPtr<UIElement> element);

  void ReleaseClickable(NotNullPtr<UIClickable> clickable);

  void SetupActiveElementsList(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, NotNullPtr<UIElement>, const Vector2 & offset);
  void ProcessActiveAreas(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset);

private:
  Window & m_ContainerWindow;

  std::vector<NotNullPtr<UIElement>> m_RootElements;
  std::vector<NotNullPtr<UIClickable>> m_Clickables;
  bool m_HasSelectedElement = false;

  UIGlobalBlock m_GlobalBlock;
  StormExprFunctionList m_FuncList;
};

