
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"

#include "Foundation/SkipField/SkipField.h"

#include <sb/vector.h>

SkipField<UIElementContainer> s_UIContainerAllocator;
SkipField<UIElementGradient> s_UIGradientAllocator;
SkipField<UIElementTextureSlice> s_UITextureSliceAllocator;
SkipField<UIElementSpriteFrame> s_UISpriteFrameAllocator;
SkipField<UIElementText> s_UITextAllocator;

void UIManager::Update()
{
  for (auto elem : m_RootElements)
  {
    elem->Update();
  }
}

void UIManager::Render(RenderState & render_state, RenderUtil & render_util)
{
  for (auto elem : m_RootElements)
  {
    elem->Render(render_state, render_util);
  }
}

NotNullPtr<UIElementContainer> UIManager::AllocateContainer(czstr name, NullOptPtr<UIElement> parent,
  const UIElementContainerInitData & init_data, const UIElementContainerData & data)
{
  return AllocateUIElement(name, s_UIContainerAllocator, parent, init_data, data);
}

NotNullPtr<UIElementGradient> UIManager::AllocateGradient(czstr name, NullOptPtr<UIElement> parent,
  const UIElementGradientInitData & init_data, const UIElementGradientData & data)
{
  return AllocateUIElement(name, s_UIGradientAllocator, parent, init_data, data);
}

NotNullPtr<UIElementTextureSlice> UIManager::AllocateTextureSlice(czstr name, NullOptPtr<UIElement> parent,
  const UIElementTextureSliceInitData & init_data, const UIElementTextureSliceData & data)
{
  return AllocateUIElement(name, s_UITextureSliceAllocator, parent, init_data, data);
}

NotNullPtr<UIElementSpriteFrame> UIManager::AllocateSpriteFrame(czstr name, NullOptPtr<UIElement> parent,
  const UIElementSpriteFrameInitData & init_data, const UIElementSpriteFrameData & data)
{
  return AllocateUIElement(name, s_UISpriteFrameAllocator, parent, init_data, data);
}

NotNullPtr<UIElementText> UIManager::AllocateText(czstr name, NullOptPtr<UIElement> parent,
  const UIElementTextInitData & init_data, const UIElementTextData & data)
{
  return AllocateUIElement(name, s_UITextAllocator, parent, init_data, data);
}

template <typename ElementType, typename InitData, typename BlockData>
NotNullPtr<ElementType> UIManager::AllocateUIElement(czstr name, SkipField<ElementType> & alloc,
  NullOptPtr<UIElement> parent, const InitData & init_data, const BlockData & data)
{
  auto elem = alloc.Allocate(init_data, data);
  elem->m_Name = name;
  elem->m_NameHash = crc32(name);
  elem->m_Handle.m_UIManager = this;
  elem->m_Handle.m_Type = UIElementContainer::Type;
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
    ReleaseElement(element);
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
  }
}
