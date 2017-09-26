
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIElementExprFuncs.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"
#include "Engine/Window/Window.h"

#include "Engine/UI/UIElementContainer.refl.meta.h"
#include "Engine/UI/UIElementGradient.refl.meta.h"
#include "Engine/UI/UIElementTextureSlice.refl.meta.h"
#include "Engine/UI/UIElementSpriteFrame.refl.meta.h"
#include "Engine/UI/UIElementText.refl.meta.h"
#include "Engine/UI/UIElementShape.refl.meta.h"
#include "Engine/UI/UIElementFullTexture.refl.meta.h"
#include "Engine/UI/UIElementTextInput.refl.meta.h"

#include "Foundation/SkipField/SkipField.h"

#include <sb/vector.h>

SkipField<UIElementContainer> s_UIContainerAllocator;
SkipField<UIElementGradient> s_UIGradientAllocator;
SkipField<UIElementTextureSlice> s_UITextureSliceAllocator;
SkipField<UIElementSpriteFrame> s_UISpriteFrameAllocator;
SkipField<UIElementText> s_UITextAllocator;
SkipField<UIElementShape> s_UIShapeAllocator;
SkipField<UIElementFullTexture> s_UIFullTextureAllocator;
SkipField<UIElementTextInput> s_UITextInputAllocator;
SkipField<UIClickable> s_UIClickableAllocator;


UIManager::UIManager(Window & container_window) :
  m_ContainerWindow(container_window),
  m_FuncList(UICreateFunctionList()),
  m_Paused(false)
{
  m_UpdateTimer.Start();
}

UIManager::~UIManager()
{
  while (m_RootElements.size())
  {
    m_RootElements.back()->Destroy();
  }
}

void UIManager::Update(InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset)
{
  //std::sort(m_RootElements.begin(), m_RootElements.end(), [](NotNullPtr<const UIElement> a, NotNullPtr<const UIElement> b) { return a->m_Layer > b->m_Layer; });

  m_GlobalBlock.m_Time = (float)GetTimeSeconds();
  m_GlobalBlock.m_ScreenWidth = (float)render_state.GetRenderWidth();
  m_GlobalBlock.m_ScreenHeight = (float)render_state.GetRenderHeight();

  auto update_time = m_UpdateTimer.GetTimeSinceLastCheck();
  if (m_Paused)
  {
    update_time = 0;
  }

  for (auto elem : m_RootElements)
  {
    elem->Update((float)update_time);
  }

  std::vector<std::pair<NotNullPtr<UIElement>, Box>> active_elements;
  for (auto itr = m_RootElements.rbegin(), end = m_RootElements.rend(); itr != end; ++itr)
  {
    auto & elem = *itr;
    if (elem->GetBaseData()->m_Enabled != 0.0f)
    {
      SetupActiveElementsList(active_elements, elem, {});
    }
  }

  ProcessActiveAreas(active_elements, input_state, render_state, clickable_offset);
}

void UIManager::Render(RenderState & render_state, RenderUtil & render_util)
{
  auto & shader = g_ShaderManager.GetDefaultShader();
  auto render_size = (RenderVec2)render_state.GetRenderSize();

  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_ScreenSize"), render_size);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Color"), Color(255, 255, 255, 255));
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), 1.0f, 0.0f, 0.0f, 1.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), 0.0f, 0.0f);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Texture"), 0);

  auto base_offset = render_size * -0.5f;

  for (auto elem : m_RootElements)
  {
    if (elem->GetBaseData()->m_Enabled != 0.0f)
    {
      elem->Render(render_state, render_util, base_offset);
    }
  }
}

void UIManager::Pause()
{
  m_Paused = true;
}

void UIManager::Unpause()
{
  m_Paused = false;
}

UIElementPtr<UIElementContainer> UIManager::AllocateContainer(czstr name, NullOptPtr<UIElement> parent,
  const UIElementContainerInitData & init_data, const UIElementContainerData & data)
{
  auto ptr = AllocateUIElement(name, s_UIContainerAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementContainer>(ptr) : UIElementPtr<UIElementContainer>(ptr->m_Handle);
}

UIElementPtr<UIElementGradient> UIManager::AllocateGradient(czstr name, NullOptPtr<UIElement> parent,
  const UIElementGradientInitData & init_data, const UIElementGradientData & data)
{
  auto ptr = AllocateUIElement(name, s_UIGradientAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementGradient>(ptr) : UIElementPtr<UIElementGradient>(ptr->m_Handle);
}

UIElementPtr<UIElementTextureSlice> UIManager::AllocateTextureSlice(czstr name, NullOptPtr<UIElement> parent,
  const UIElementTextureSliceInitData & init_data, const UIElementTextureSliceData & data)
{
  auto ptr = AllocateUIElement(name, s_UITextureSliceAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementTextureSlice>(ptr) : UIElementPtr<UIElementTextureSlice>(ptr->m_Handle);
}

UIElementPtr<UIElementSpriteFrame> UIManager::AllocateSpriteFrame(czstr name, NullOptPtr<UIElement> parent,
  const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data)
{
  auto ptr = AllocateUIElement(name, s_UISpriteFrameAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementSpriteFrame>(ptr) : UIElementPtr<UIElementSpriteFrame>(ptr->m_Handle);
}

UIElementPtr<UIElementText> UIManager::AllocateText(czstr name, NullOptPtr<UIElement> parent,
  const UIElementTextInitData & init_data, const UIElementTextData & data)
{
  auto ptr = AllocateUIElement(name, s_UITextAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementText>(ptr) : UIElementPtr<UIElementText>(ptr->m_Handle);
}

UIElementPtr<UIElementShape> UIManager::AllocateShape(czstr name, NullOptPtr<UIElement> parent,
  const UIElementShapeInitData & init_data, const UIElementShapeData & data)
{
  auto ptr = AllocateUIElement(name, s_UIShapeAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementShape>(ptr) : UIElementPtr<UIElementShape>(ptr->m_Handle);
}

UIElementPtr<UIElementFullTexture> UIManager::AllocateFullTexture(czstr name, NullOptPtr<UIElement> parent,
  const UIElementFullTextureInitData & init_data, const UIElementFullTextureData & data)
{
  auto ptr = AllocateUIElement(name, s_UIFullTextureAllocator, parent, init_data, data);
  return parent == nullptr ? UIElementPtr<UIElementFullTexture>(ptr) : UIElementPtr<UIElementFullTexture>(ptr->m_Handle);
}

UIElementPtr<UIElementTextInput> UIManager::AllocateTextInput(czstr name, NullOptPtr<UIElement> parent,
  const UIElementTextInputInitData & init_data, const UIElementTextInputData & data)
{
  auto ptr = AllocateUIElement(name, s_UITextInputAllocator, parent, init_data, data, m_ContainerWindow.CreateTextInputContext(true));
  return parent == nullptr ? UIElementPtr<UIElementTextInput>(ptr) : UIElementPtr<UIElementTextInput>(ptr->m_Handle);
}

UIElementHandle UIManager::AllocateElementFromDef(czstr name, const UIDef & def, NullOptPtr<UIElement> parent, bool use_default_inputs)
{
  auto handle = AllocateElementFromInitData(name, parent, def.m_InitData.GetTypeNameHash(), def.m_InitData.GetValue());
  auto elem = handle.Resolve();

  if (elem == nullptr)
  {
    return handle;
  }

  std::vector<std::string> errors;
  elem->InitializeExprBlock(def, nullptr, nullptr, nullptr, nullptr, *this, errors, use_default_inputs);
  return handle;
}

uint32_t UIManager::GetElementTypeNameHashForEnum(UIElementType type)
{
  switch (type)
  {
  default:
  case UIElementType::kContainer:
    return StormReflTypeInfo<UIElementContainerInitData>::GetNameHash();
  case UIElementType::kGradient:
    return StormReflTypeInfo<UIElementGradientInitData>::GetNameHash();
  case UIElementType::kTextureSlice:
    return StormReflTypeInfo<UIElementTextureSliceInitData>::GetNameHash();
  case UIElementType::kSpriteFrame:
    return StormReflTypeInfo<UIElementSpriteFrameInitData>::GetNameHash();
  case UIElementType::kText:
    return StormReflTypeInfo<UIElementTextInitData>::GetNameHash();
  case UIElementType::kShape:
    return StormReflTypeInfo<UIElementShapeInitData>::GetNameHash();
  case UIElementType::kFullTexture:
    return StormReflTypeInfo<UIElementFullTextureInitData>::GetNameHash();
  case UIElementType::kTextInput:
    return StormReflTypeInfo<UIElementTextInputInitData>::GetNameHash();
  }
}

std::vector<std::string> UIManager::GetVariablesForElementType(uint32_t element_type_hash)
{
  std::vector<std::string> variables;
  switch (element_type_hash)
  {
  default:
    StormReflVisitStatic<UIElementContainerData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementContainerInitData>::GetNameHash():
    StormReflVisitStatic<UIElementContainerData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementGradientInitData>::GetNameHash():
    StormReflVisitStatic<UIElementGradientData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementTextureSliceInitData>::GetNameHash():
    StormReflVisitStatic<UIElementTextureSliceData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementSpriteFrameInitData>::GetNameHash():
    StormReflVisitStatic<UIElementSpriteFrameData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementTextInitData>::GetNameHash():
    StormReflVisitStatic<UIElementTextData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementShapeInitData>::GetNameHash():
    StormReflVisitStatic<UIElementShapeData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementFullTextureInitData>::GetNameHash():
    StormReflVisitStatic<UIElementFullTextureData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  case StormReflTypeInfo<UIElementTextInputInitData>::GetNameHash():
    StormReflVisitStatic<UIElementTextInputData>::VisitEach([&](auto f) { variables.emplace_back(f.GetName()); });
    break;
  }

  return variables;
}

UIClickablePtr UIManager::AllocateClickable(const Box & active_area)
{
  UIClickable::UIClickableConstructorTag crap;

  auto ptr = s_UIClickableAllocator.Allocate(crap);
  ptr->m_ActiveArea = active_area;
  ptr->m_Manager = this;

  m_Clickables.push_back(ptr);
  return UIClickablePtr(ptr);
}

UIElementHandle UIManager::GetElementByPath(czstr path)
{
  if (*path != '.')
  {
    return UIElementHandle{};
  }

  path++;

  auto hash = crc32begin();
  while (true)
  {
    if (*path == 0 || *path == '.')
    {
      break;
    }

    hash = crc32additive(hash, *path);
    path++;
  }

  hash = crc32end(hash);

  NullOptPtr<UIElement> cur_elem = nullptr;
  for (auto elem : m_RootElements)
  {
    if (elem->m_NameHash == hash)
    {
      cur_elem = elem;
      break;
    }
  }

  if (cur_elem == nullptr)
  {
    return UIElementHandle();
  }

  while (true)
  {
    if (*path == 0)
    {
      return cur_elem->GetHandle();
    }

    if (*path != '.')
    {
      return cur_elem->GetHandle();
    }

    hash = crc32begin();
    while (true)
    {
      if (*path == 0 || *path == '.')
      {
        break;
      }

      hash = crc32additive(hash, *path);
      path++;
    }
    hash = crc32end(hash);

    cur_elem = cur_elem->GetChild(hash);
    if (cur_elem == nullptr)
    {
      return UIElementHandle();
    }
  }
}

bool UIManager::HasSelectedElement() const
{
  return m_HasSelectedElement;
}

template <typename ElementType, typename InitData, typename BlockData>
NotNullPtr<ElementType> UIManager::AllocateUIElement(czstr name, SkipField<ElementType> & alloc,
  NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data)
{
  auto elem = alloc.Allocate(init_data, data);
  elem->m_Name = name;
  elem->m_NameHash = crc32(name);
  elem->m_Handle.m_UIManager = this;
  elem->m_Handle.m_Type = ElementType::Type;
  elem->m_Parent = parent;

  if (parent)
  {
    parent->m_Children.push_back(elem);
  }
  else
  {
    m_RootElements.push_back(elem);
  }

  return elem;
}

template <typename ElementType, typename InitData, typename BlockData, typename Param>
NotNullPtr<ElementType> UIManager::AllocateUIElement(czstr name, SkipField<ElementType> & alloc,
  NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data, Param && param)
{
  auto elem = alloc.Allocate(init_data, data, std::forward<Param>(param));
  elem->m_Name = name;
  elem->m_NameHash = crc32(name);
  elem->m_Handle.m_UIManager = this;
  elem->m_Handle.m_Type = ElementType::Type;
  elem->m_Parent = parent;

  if (parent)
  {
    parent->m_Children.push_back(elem);
  }
  else
  {
    m_RootElements.push_back(elem);
  }

  return elem;
}

UIElementHandle UIManager::AllocateElementFromInitData(czstr name, NullOptPtr<UIElement> parent, uint32_t type_name_hash, const UIElementInitDataBase * init_data)
{
  UIElementHandle handle;
  switch (type_name_hash)
  {
  default:
    handle = AllocateUIElement(name, s_UIContainerAllocator, parent, UIElementContainerInitData{}, UIElementContainerData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementContainerInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UIContainerAllocator, parent, *static_cast<const UIElementContainerInitData *>(init_data), UIElementContainerData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementGradientInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UIGradientAllocator, parent, *static_cast<const UIElementGradientInitData *>(init_data), UIElementGradientData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementTextureSliceInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UITextureSliceAllocator, parent, *static_cast<const UIElementTextureSliceInitData *>(init_data), UIElementTextureSliceData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementSpriteFrameInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UISpriteFrameAllocator, parent, *static_cast<const UIElementSpriteFrameInitData *>(init_data), UIElementSpriteFrameData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementTextInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UITextAllocator, parent, *static_cast<const UIElementTextInitData *>(init_data), UIElementTextData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementShapeInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UIShapeAllocator, parent, *static_cast<const UIElementShapeInitData *>(init_data), UIElementShapeData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementFullTextureInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UIFullTextureAllocator, parent, *static_cast<const UIElementFullTextureInitData *>(init_data), UIElementFullTextureData{})->GetHandle();
    break;
  case StormReflTypeInfo<UIElementTextInputInitData>::GetNameHash():
    handle = AllocateUIElement(name, s_UITextInputAllocator, parent, *static_cast<const UIElementTextInputInitData *>(init_data), UIElementTextInputData{},
      m_ContainerWindow.CreateTextInputContext(true))->GetHandle();
    break;
  }

  return handle;
}

NotNullPtr<UIElement> UIManager::ResolveHandle(UIElementType type, const Handle & handle)
{
  switch (type)
  {
  case UIElementType::kContainer:
    return s_UIContainerAllocator.ResolveHandle(handle);
  case UIElementType::kGradient:
    return s_UIGradientAllocator.ResolveHandle(handle);
  case UIElementType::kTextureSlice:
    return s_UITextureSliceAllocator.ResolveHandle(handle);
  case UIElementType::kSpriteFrame:
    return s_UISpriteFrameAllocator.ResolveHandle(handle);
  case UIElementType::kText:
    return s_UITextAllocator.ResolveHandle(handle);
  case UIElementType::kShape:
    return s_UIShapeAllocator.ResolveHandle(handle);
  case UIElementType::kFullTexture:
    return s_UIFullTextureAllocator.ResolveHandle(handle);
  case UIElementType::kTextInput:
    return s_UITextInputAllocator.ResolveHandle(handle);
  }

  return nullptr;
}

void UIManager::UnlinkElement(NotNullPtr<UIElement> element)
{
  if (element->m_Parent)
  {
    for (auto itr = element->m_Parent->m_Children.begin(), end = element->m_Parent->m_Children.end(); itr != end; ++itr)
    {
      if (*itr == element)
      {
        element->m_Parent->m_Children.erase(itr);
        break;
      }
    }
  }
  else
  {
    for (auto itr = m_RootElements.begin(), end = m_RootElements.end(); itr != end; ++itr)
    {
      if (*itr == element)
      {
        m_RootElements.erase(itr);
        break;
      }
    }
  }

  ReleaseElement(element);
}

void UIManager::ReleaseElement(NotNullPtr<UIElement> element)
{
  for (auto child : element->m_Children)
  {
    ReleaseElement(child);
  }
  
  switch (element->m_Handle.m_Type)
  {
  case UIElementType::kContainer:
    return s_UIContainerAllocator.Release(static_cast<NotNullPtr<UIElementContainer>>(element));
  case UIElementType::kGradient:
    return s_UIGradientAllocator.Release(static_cast<NotNullPtr<UIElementGradient>>(element));
  case UIElementType::kTextureSlice:
    return s_UITextureSliceAllocator.Release(static_cast<NotNullPtr<UIElementTextureSlice>>(element));
  case UIElementType::kSpriteFrame:
    return s_UISpriteFrameAllocator.Release(static_cast<NotNullPtr<UIElementSpriteFrame>>(element));
  case UIElementType::kText:
    return s_UITextAllocator.Release(static_cast<NotNullPtr<UIElementText>>(element));
  case UIElementType::kShape:
    return s_UIShapeAllocator.Release(static_cast<NotNullPtr<UIElementShape>>(element));
  case UIElementType::kFullTexture:
    return s_UIFullTextureAllocator.Release(static_cast<NotNullPtr<UIElementFullTexture>>(element));
  case UIElementType::kTextInput:
    return s_UITextInputAllocator.Release(static_cast<NotNullPtr<UIElementTextInput>>(element));
  }
}

void UIManager::ReleaseClickable(NotNullPtr<UIClickable> clickable)
{
  s_UIClickableAllocator.Release(clickable);
}

void UIManager::SetupActiveElementsList(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, NotNullPtr<UIElement> elem, const Vector2 & offset)
{
  for (auto itr = elem->m_Children.rbegin(), end = elem->m_Children.rend(); itr != end; ++itr)
  {
    auto & child = *itr;
    if (child->GetBaseData()->m_Enabled != 0.0f)
    {
      SetupActiveElementsList(elements, child, elem->m_Offset);
    }
  }

  if (elem->m_State != UIElementState::kInactive)
  {
    Box active_area = elem->m_ActiveArea;
    active_area.m_Start += offset;
    active_area.m_End += offset;

    elements.push_back(std::make_pair(elem, active_area));
  }
}

void UIManager::ProcessActiveAreas(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, InputState & input_state, RenderState & render_state, const Vector2 & clickable_offset)
{
  m_HasSelectedElement = false;

  NullOptPtr<UIElement> cur_pressed_element = nullptr;
  for (auto elem : elements)
  {
    if (elem.first->m_State == UIElementState::kPressed)
    {
      if (cur_pressed_element)
      {
        elem.first->m_OnStateChange(elem.first->m_State, UIElementState::kActive);
        elem.first->m_State = UIElementState::kActive;
      }
      else
      {
        cur_pressed_element = elem.first;
      }
    }
  }

  NullOptPtr<UIClickable> cur_pressed_clickable = nullptr;
  for (auto elem : m_Clickables)
  {
    if (elem->m_State == UIClickableState::kPressed)
    {
      if (cur_pressed_element || cur_pressed_element)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
      else
      {
        cur_pressed_clickable = elem;
      }
    }
  }

  auto pointer_state = input_state.GetPointerState();
  auto pointer_pos = (Vector2)render_state.ScreenPixelsToRenderPixels(pointer_state.m_Pos);

  Vector2 ui_pos = pointer_pos;
  ui_pos += render_state.GetRenderSize() / 2;

  UIElement * cur_hover_element = nullptr;
  UIClickable * cur_hover_clickable = nullptr;
  if (pointer_state.m_InFocus)
  {
    for (auto elem : elements)
    {
      if (PointInBox(elem.second, ui_pos))
      {
        cur_hover_element = elem.first;
        break;
      }
    }

    for (auto elem : m_Clickables)
    {
      auto box = elem->m_ActiveArea;
      box.m_Start -= clickable_offset;
      box.m_End -= clickable_offset;

      if (PointInBox(box, pointer_pos))
      {
        cur_hover_clickable = elem;
        break;
      }
    }
  }

  if (cur_pressed_element || cur_pressed_clickable)
  {
    for (auto elem : elements)
    {
      if (elem.first->m_State == UIElementState::kHover)
      {
        elem.first->m_OnStateChange(elem.first->m_State, UIElementState::kActive);
        elem.first->m_State = UIElementState::kActive;
      }
    }

    for (auto elem : m_Clickables)
    {
      if (elem->m_State == UIClickableState::kHover)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
    }

    if (pointer_state.m_InFocus == false)
    {
      if (cur_pressed_element)
      {
        cur_pressed_element->m_OnStateChange(cur_pressed_element->m_State, UIElementState::kActive);
        cur_pressed_element->m_State = UIElementState::kActive;
      }
      else if (cur_pressed_clickable)
      {
        cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
        cur_pressed_clickable->m_State = UIClickableState::kActive;
      }
    }
    else if (input_state.GetMouseButtonState(kMouseLeftButton) == false)
    {
      if (cur_hover_element != nullptr)
      {
        if (cur_hover_element == cur_pressed_element)
        {
          cur_pressed_element->m_OnClick(cur_pressed_element);
          cur_pressed_element->m_OnStateChange(cur_pressed_element->m_State, UIElementState::kHover);
          cur_pressed_element->m_State = UIElementState::kHover;
        }
        else
        {
          cur_pressed_element->m_OnStateChange(cur_pressed_element->m_State, UIElementState::kActive);
          cur_pressed_element->m_State = UIElementState::kActive;
        }
      }
      else if(cur_pressed_element)
      {
        cur_pressed_element->m_OnStateChange(cur_pressed_element->m_State, UIElementState::kActive);
        cur_pressed_element->m_State = UIElementState::kActive;
      }
      
      if (cur_hover_clickable != nullptr)
      {
        if (cur_hover_clickable == cur_pressed_clickable)
        {
          cur_pressed_clickable->m_OnClick();
          cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kHover);
          cur_pressed_clickable->m_State = UIClickableState::kHover;
        }
        else
        {
          cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
          cur_pressed_clickable->m_State = UIClickableState::kActive;
        }
      }
      else if(cur_pressed_clickable)
      {
        cur_pressed_clickable->m_OnStateChange(cur_pressed_clickable->m_State, UIClickableState::kActive);
        cur_pressed_clickable->m_State = UIClickableState::kActive;
      }
    }
  }
  else
  {
    if (input_state.GetMouseButtonState(kMouseLeftButton) && input_state.GetMousePressedThisFrame(kMouseLeftButton) == false)
    {
      cur_hover_element = nullptr;
      cur_hover_clickable = nullptr;
    }

    for (auto elem : elements)
    {
      if (elem.first != cur_hover_element && elem.first->m_State == UIElementState::kHover)
      {
        elem.first->m_OnStateChange(elem.first->m_State, UIElementState::kActive);
        elem.first->m_State = UIElementState::kActive;
      }
    }

    for (auto elem : m_Clickables)
    {
      if (elem != cur_hover_clickable && elem->m_State == UIClickableState::kHover)
      {
        elem->m_OnStateChange(elem->m_State, UIClickableState::kActive);
        elem->m_State = UIClickableState::kActive;
      }
    }

    if (cur_hover_element != nullptr && cur_hover_element->m_State != UIElementState::kHover)
    {
      cur_hover_element->m_OnStateChange(cur_hover_element->m_State, UIElementState::kHover);
      cur_hover_element->m_State = UIElementState::kHover;
    }

    if (cur_hover_clickable != nullptr && cur_hover_clickable->m_State != UIClickableState::kHover)
    {
      cur_hover_clickable->m_OnStateChange(cur_hover_clickable->m_State, UIClickableState::kHover);
      cur_hover_clickable->m_State = UIClickableState::kHover;
    }

    if (input_state.GetMousePressedThisFrame(kMouseLeftButton))
    {
      if (cur_hover_element != nullptr)
      {
        cur_hover_element->m_OnStateChange(cur_hover_element->m_State, UIElementState::kPressed);
        cur_hover_element->m_State = UIElementState::kPressed;
      }

      if (cur_hover_clickable != nullptr)
      {
        cur_hover_clickable->m_OnStateChange(cur_hover_clickable->m_State, UIClickableState::kPressed);
        cur_hover_clickable->m_State = UIClickableState::kPressed;
      }
    }
  }

  if (cur_hover_element || cur_pressed_element || cur_hover_clickable || cur_pressed_clickable)
  {
    m_HasSelectedElement = true;
  }
}
