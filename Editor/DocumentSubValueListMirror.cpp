
#include "DocumentSubValueListMirror.h"
#include "DocumentEditorWidgetBase.h"

#include <StormData/StormDataPath.h>

#include <sb/vector.h>


DocumentSubValueListMirror::DocumentSubValueListMirror(NotNullPtr<DocumentEditorWidgetBase> editor) :
  m_Editor(editor),
  m_ChangeCallbackId(0),
  m_ParentCallbackId(0),
  m_ChildCallbackId(0)
{

}

DocumentSubValueListMirror::~DocumentSubValueListMirror()
{
  Clear();
}

void DocumentSubValueListMirror::SetList(
  czstr list_path,
  czstr sub_path,
  Delegate<void *> && list_ptr,
  Delegate<std::vector<std::size_t>, void *> && get_element_indices,
  Delegate<void *, void *, std::size_t> && get_element,
  Delegate<void *, void *> && get_sub_element,
  Delegate<void *, void *, std::size_t> && create_mirror_element,
  Delegate<void, void *, void *, std::size_t> && update_mirror_element,
  Delegate<void, void *> && destroy_mirror_element)
{
  m_ListPtr = std::move(list_ptr);
  m_GetElementIndices = std::move(get_element_indices);
  m_GetElement = std::move(get_element);
  m_GetSubElement = std::move(get_sub_element);
  m_CreateMirrorElement = std::move(create_mirror_element);
  m_UpdateMirrorElement = std::move(update_mirror_element);
  m_DestroyMirrorElement = std::move(destroy_mirror_element);

  m_Path = list_path;
  m_PathHash = crc64(list_path);

  m_SubPath = sub_path;

  m_ChangeCallbackId = m_Editor->AddChangeCallback(m_PathHash, DocumentExternalChangeCallback(&DocumentSubValueListMirror::HandleDirectUpdate, this));
  m_ParentCallbackId = m_Editor->AddParentChangeCallback(list_path, DocumentExternalChangeCallback(&DocumentSubValueListMirror::HandleParentUpdate, this));
  m_ChildCallbackId = m_Editor->AddChildChangeCallback(list_path, DocumentExternalChangeCallback(&DocumentSubValueListMirror::HandleChildUpdate, this));

  SyncElements();
}

void DocumentSubValueListMirror::Clear()
{
  DesyncElements();

  if (m_ChangeCallbackId != 0)
  {
    m_Editor->RemoveChangeCallback(m_PathHash, m_ChangeCallbackId);
    m_ChangeCallbackId = 0;
  }

  if (m_ParentCallbackId != 0)
  {
    m_Editor->RemovParentChangeCallback(m_ParentCallbackId);
    m_ParentCallbackId = 0;
  }

  if (m_ChildCallbackId != 0)
  {
    m_Editor->RemoveChildChangeCallback(m_ChildCallbackId);
    m_ChildCallbackId = 0;
  }
}

void * DocumentSubValueListMirror::GetElement(std::size_t index)
{
  for (auto & elem : m_MirrorElements)
  {
    if (elem.first == index)
    {
      return elem.second;
    }
  }

  return nullptr;
}

void DocumentSubValueListMirror::SetUpdateCallback(Delegate<void, std::size_t> && callback)
{
  m_UpdateElementCallback = std::move(callback);
}

void DocumentSubValueListMirror::SyncElements()
{
  auto list = m_ListPtr();
  if (list == nullptr)
  {
    return;
  }

  auto indices = m_GetElementIndices(list);
  for (auto index : indices)
  {
    auto element = m_GetElement(list, index);
    auto sub_elem = m_GetSubElement(element);

    auto mirror_elem = m_CreateMirrorElement(sub_elem, index);
    m_MirrorElements.emplace_back(std::make_pair(index, mirror_elem));
    m_UpdateElementCallback(index);
  }
}

void DocumentSubValueListMirror::DesyncElements()
{
  for (auto & elem : m_MirrorElements)
  {
    m_DestroyMirrorElement(elem.second);
    m_UpdateElementCallback(elem.first);
  }

  m_MirrorElements.clear();
}

void DocumentSubValueListMirror::HandleParentUpdate(const ReflectionChangeNotification & change)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  DesyncElements();
  SyncElements();
}


void DocumentSubValueListMirror::HandleDirectUpdate(const ReflectionChangeNotification & change)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  if (change.m_Type == ReflectionNotifyChangeType::kInsert)
  {
    auto element = m_GetElement(list_ptr, change.m_SubIndex);
    auto sub_elem = m_GetSubElement(element);

    auto mirror_elem = m_CreateMirrorElement(sub_elem, change.m_SubIndex);
    m_MirrorElements.emplace_back(std::make_pair(change.m_SubIndex, mirror_elem));
    m_UpdateElementCallback(change.m_SubIndex);
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
  {
    for (std::size_t index = 0, end = m_MirrorElements.size(); index < end; ++index)
    {
      if (m_MirrorElements[index].first == change.m_SubIndex)
      {
        m_DestroyMirrorElement(m_MirrorElements[index].second);
        vremove_index_quick(m_MirrorElements, index);
        m_UpdateElementCallback(change.m_SubIndex);
        return;
      }
    }
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kSet || change.m_Type == ReflectionNotifyChangeType::kCompress)
  {
    DesyncElements();
    SyncElements();
  }
  else if (change.m_Type == ReflectionNotifyChangeType::kClear)
  {
    DesyncElements();
  }
}

void DocumentSubValueListMirror::HandleChildUpdate(const ReflectionChangeNotification & change)
{
  auto list_ptr = m_ListPtr();
  if (list_ptr == nullptr)
  {
    return;
  }

  auto path_ptr = change.m_Path.data();
  path_ptr += m_Path.size();

  if (*path_ptr != '[')
  {
    return;
  }

  path_ptr++;
  if (*path_ptr < '0' || *path_ptr > '9')
  {
    return;
  }

  std::size_t child_index =  *path_ptr - '0';
  path_ptr++;

  while (*path_ptr != ']')
  {
    if (*path_ptr < '0' || *path_ptr > '9')
    {
      return;
    }

    child_index *= 10;
    child_index += *path_ptr - '0';
    path_ptr++;
  }

  path_ptr++;

  if (StormDataMatchPathPartial(m_SubPath.data(), path_ptr) == false)
  {
    return;
  }

  for (std::size_t index = 0, end = m_MirrorElements.size(); index < end; ++index)
  {
    if (m_MirrorElements[index].first == child_index)
    {
      auto elem = m_GetElement(list_ptr, child_index);
      auto sub_elem = m_GetSubElement(elem);

      m_UpdateMirrorElement(sub_elem, m_MirrorElements[index].second, child_index);
      m_UpdateElementCallback(index);
    }
  }
}

