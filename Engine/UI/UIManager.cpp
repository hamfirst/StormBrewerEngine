
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/Input/InputState.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Shader/ShaderManager.h"

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

void UIManager::Update(InputState & input_state, RenderState & render_state)
{
  //std::sort(m_RootElements.begin(), m_RootElements.end(), [](NotNullPtr<const UIElement> a, NotNullPtr<const UIElement> b) { return a->m_Layer > b->m_Layer; });

  for (auto elem : m_RootElements)
  {
    elem->Update();
  }

  std::vector<std::pair<NotNullPtr<UIElement>, Box>> active_elements;
  for (auto itr = m_RootElements.rbegin(), end = m_RootElements.rend(); itr != end; ++itr)
  {
    auto & elem = *itr;
    if (elem->m_Enabled)
    {
      SetupActiveElementsList(active_elements, elem, {});
    }
  }

  ProcessActiveAreas(active_elements, input_state, render_state);
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
    if (elem->m_Enabled)
    {
      elem->Render(render_state, render_util, base_offset);
    }
  }
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

UIElementPtr<UIElementTextInput> UIManager::AllocateTextInput(czstr name, std::shared_ptr<TextInputContext> && input_context, NullOptPtr<UIElement> parent,
  const UIElementTextInputInitData & init_data, const UIElementTextInputData & data)
{
  auto ptr = AllocateUIElement(name, s_UITextInputAllocator, parent, init_data, data, std::move(input_context));
  return parent == nullptr ? UIElementPtr<UIElementTextInput>(ptr) : UIElementPtr<UIElementTextInput>(ptr->m_Handle);
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

NotNullPtr<UIElement> UIManager::ResolveHandle(uint32_t type, Handle & handle)
{
  switch (type)
  {
  case 1:
    return s_UIContainerAllocator.ResolveHandle(handle);
  case 2:
    return s_UIGradientAllocator.ResolveHandle(handle);
  case 3:
    return s_UITextureSliceAllocator.ResolveHandle(handle);
  case 4:
    return s_UISpriteFrameAllocator.ResolveHandle(handle);
  case 5:
    return s_UITextAllocator.ResolveHandle(handle);
  case 6:
    return s_UIShapeAllocator.ResolveHandle(handle);
  case 7:
    return s_UIFullTextureAllocator.ResolveHandle(handle);
  case 8:
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
  case 1:
    return s_UIContainerAllocator.Release(static_cast<NotNullPtr<UIElementContainer>>(element));
  case 2:
    return s_UIGradientAllocator.Release(static_cast<NotNullPtr<UIElementGradient>>(element));
  case 3:
    return s_UITextureSliceAllocator.Release(static_cast<NotNullPtr<UIElementTextureSlice>>(element));
  case 4:
    return s_UISpriteFrameAllocator.Release(static_cast<NotNullPtr<UIElementSpriteFrame>>(element));
  case 5:
    return s_UITextAllocator.Release(static_cast<NotNullPtr<UIElementText>>(element));
  case 6:
    return s_UIShapeAllocator.Release(static_cast<NotNullPtr<UIElementShape>>(element));
  case 7:
    return s_UIFullTextureAllocator.Release(static_cast<NotNullPtr<UIElementFullTexture>>(element));
  case 8:
    return s_UITextInputAllocator.Release(static_cast<NotNullPtr<UIElementTextInput>>(element));
  }
}

void UIManager::SetupActiveElementsList(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, NotNullPtr<UIElement> elem, const Vector2 & offset)
{
  for (auto itr = elem->m_Children.rbegin(), end = elem->m_Children.rend(); itr != end; ++itr)
  {
    auto & child = *itr;
    if (child->m_Enabled)
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

void UIManager::ProcessActiveAreas(std::vector<std::pair<NotNullPtr<UIElement>, Box>> & elements, InputState & input_state, RenderState & render_state)
{
  m_HasSelectedElement = false;

  UIElement * cur_pressed = nullptr;
  for (auto elem : elements)
  {
    if (elem.first->m_State == UIElementState::kPressed)
    {
      if (cur_pressed)
      {
        elem.first->m_OnStateChange(elem.first->m_State, UIElementState::kActive);
        elem.first->m_State = UIElementState::kActive;
      }
      else
      {
        cur_pressed = elem.first;
      }
    }
  }

  auto pointer_state = input_state.GetPointerState();
  if (pointer_state.m_InFocus == false)
  {
    if (cur_pressed)
    {
      cur_pressed->m_OnStateChange(cur_pressed->m_State, UIElementState::kActive);
      cur_pressed->m_State = UIElementState::kActive;
      cur_pressed = nullptr;
    }
  }

  auto pointer_pos = (Vector2)render_state.ScreenPixelsToRenderPixels(pointer_state.m_Pos);

  UIElement * cur_hover = nullptr;
  for (auto elem : elements)
  {
    if (PointInBox(elem.second, pointer_pos) && pointer_state.m_InFocus)
    {
      cur_hover = elem.first;
      break;
    }
  }

  if (input_state.GetMousePressedThisFrame(kMouseLeftButton))
  {
    if (cur_hover)
    {
      cur_hover->m_OnStateChange(cur_hover->m_State, UIElementState::kPressed);
      cur_hover->m_State = UIElementState::kPressed;
    }
  }
  else if (input_state.GetMouseButtonState(kMouseLeftButton))
  {
    cur_hover = nullptr;
  }
  else
  {
    if (cur_pressed && cur_pressed == cur_hover)
    {
      cur_pressed->m_OnClick(cur_pressed);

      cur_pressed->m_OnStateChange(cur_pressed->m_State, UIElementState::kHover);
      cur_pressed->m_State = UIElementState::kHover;
    }
    else
    {
      if (cur_hover)
      {
        if (cur_hover->m_State != UIElementState::kHover)
        {
          cur_hover->m_OnStateChange(cur_hover->m_State, UIElementState::kHover);
          cur_hover->m_State = UIElementState::kHover;
        }
      }

      if (cur_pressed)
      {
        cur_pressed->m_OnStateChange(cur_pressed->m_State, UIElementState::kActive);
        cur_pressed->m_State = UIElementState::kActive;
      }
    }
  }

  for (auto elem : elements)
  {
    if (elem.first->m_State == UIElementState::kHover && elem.first != cur_hover)
    {
      elem.first->m_OnStateChange(elem.first->m_State, UIElementState::kActive);
      elem.first->m_State = UIElementState::kActive;
    }
  }

  if (cur_hover || cur_pressed)
  {
    m_HasSelectedElement = true;
  }
}
