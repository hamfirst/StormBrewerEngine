#pragma once

#include "Foundation/Common.h"
#include "Foundation/Delegate/Delegate.h"

#include "StormData/StormDataPath.h"

class DocumentEditorWidgetBase;

class DocumentSubValueListMirror
{
public:
  DocumentSubValueListMirror(NotNullPtr<DocumentEditorWidgetBase> editor);
  ~DocumentSubValueListMirror();

  void SetList(
    czstr list_path,
    czstr sub_path,
    Delegate<void *> && list_ptr,
    Delegate<std::vector<std::size_t>, void *> && get_element_indices,
    Delegate<void *, void *, std::size_t> && get_element,
    Delegate<void *, void *> && get_sub_element,
    Delegate<void *, void *, std::size_t> && create_mirror_element,
    Delegate<void, void *, void *, std::size_t> && update_mirror_element,
    Delegate<void, void *> && destroy_mirror_element);

  void Clear();

  void * GetElement(std::size_t index);

  void SetUpdateCallback(Delegate<void, std::size_t> && callback);

protected:

  void SyncElements();
  void DesyncElements();

  void HandleParentUpdate(const ReflectionChangeNotification & change);
  void HandleDirectUpdate(const ReflectionChangeNotification & change);
  void HandleChildUpdate(const ReflectionChangeNotification & change);

private:
  NotNullPtr<DocumentEditorWidgetBase> m_Editor;
  Delegate<void *> m_ListPtr;

  uint64_t m_ChangeCallbackId;
  uint64_t m_ParentCallbackId;
  uint64_t m_ChildCallbackId;

  std::string m_Path;
  uint64_t m_PathHash;

  std::string m_SubPath;

  std::vector<std::pair<std::size_t, void *>> m_MirrorElements;

  Delegate<std::vector<std::size_t>, void *> m_GetElementIndices;
  Delegate<void *, void *, std::size_t> m_GetElement;
  Delegate<void *, void *> m_GetSubElement;
  Delegate<void *, void *, std::size_t> m_CreateMirrorElement;
  Delegate<void, void *, void *, std::size_t> m_UpdateMirrorElement;
  Delegate<void, void *> m_DestroyMirrorElement;

  Delegate<void, std::size_t> m_UpdateElementCallback;
};

template <template <typename> class ListType, typename ElementType, typename SubElementType, typename MirrorType, typename ContextType>
Delegate<NullOptPtr<MirrorType>, std::size_t> CreateMirrorList(
  DocumentSubValueListMirror & mirror_list, ListType<ElementType> & list,
  Delegate<void *> && get_list, czstr sub_path,
  SubElementType & (*GetSubElement)(ElementType & elem, NotNullPtr<ContextType> user_ptr),
  void(*InitElement)(SubElementType & elem, MirrorType & mirror_type, std::size_t index, NotNullPtr<ContextType> user_ptr),
  void(*SyncElement)(SubElementType & elem, MirrorType & mirror_type, std::size_t index, NotNullPtr<ContextType> user_ptr),
  NotNullPtr<ContextType> user_ptr)
{
  Delegate<std::vector<std::size_t>, void *> init_del = [](void * ptr) -> std::vector<std::size_t>
  {
    ListType<ElementType> * list = static_cast<ListType<ElementType> *>(ptr);

    std::vector<std::size_t> indices;
    for (auto elem : (*list))
    {
      indices.push_back(elem.first);
    }

    return indices;
  };

  Delegate<void *, void *, std::size_t> get_element_del = [](void * ptr, std::size_t index) -> void *
  {
    ListType<ElementType> * list = static_cast<ListType<ElementType> *>(ptr);
    return list->TryGet(index);
  };

  Delegate<void *, void *> get_sub_element_del = [=](void * ptr) -> void *
  {
    ElementType * elem = static_cast<ElementType *>(ptr);
    auto & sub_elem = GetSubElement(*elem, user_ptr);
    return &sub_elem;
  };

  Delegate<void *, void *, std::size_t> create_mirror_elem_del = [=](void * elem_ptr, std::size_t index) -> void *
  {
    auto elem = static_cast<SubElementType *>(elem_ptr);
    auto mirror_elem = new MirrorType();

    InitElement(*elem, *mirror_elem, index, user_ptr);
    SyncElement(*elem, *mirror_elem, index, user_ptr);

    return mirror_elem;
  };

  Delegate<void, void *, void *, std::size_t> update_mirror_elem_del = [=](void * elem_ptr, void * mirror_elem_ptr, std::size_t index)
  {
    auto elem = static_cast<SubElementType *>(elem_ptr);
    auto mirror_elem = static_cast<MirrorType *>(mirror_elem_ptr);

    SyncElement(*elem, *mirror_elem, index, user_ptr);
  };

  Delegate<void, void *> destroy_mirror_elem_del = [=](void * mirror_elem_ptr)
  {
    auto mirror_elem = static_cast<MirrorType *>(mirror_elem_ptr);
    delete mirror_elem;
  };

  Delegate<NullOptPtr<MirrorType>, std::size_t> mirror_elem_access_del = [mirror_list_ptr = &mirror_list](std::size_t index) -> NullOptPtr<MirrorType>
  {
    return static_cast<MirrorType *>(mirror_list_ptr->GetElement(index));
  };

  mirror_list.SetList(
    StormDataGetPath(list).data(),
    sub_path,
    std::move(get_list),
    std::move(init_del),
    std::move(get_element_del),
    std::move(get_sub_element_del),
    std::move(create_mirror_elem_del),
    std::move(update_mirror_elem_del),
    std::move(destroy_mirror_elem_del)
  );

  return mirror_elem_access_del;
}

template <template <typename> class ListType, typename ElementType, typename SubElementType, typename MirrorType, typename ContextType>
Delegate<NullOptPtr<MirrorType>, std::size_t> CreateMirrorList(
  DocumentSubValueListMirror & mirror_list, ListType<ElementType> & list, czstr sub_path,
  SubElementType & (*GetSubElement)(ElementType & elem, NotNullPtr<ContextType> user_ptr),
  void(*InitElement)(SubElementType & elem, MirrorType & mirror_type, std::size_t index, NotNullPtr<ContextType> user_ptr),
  void(*SyncElement)(SubElementType & elem, MirrorType & mirror_type, std::size_t index, NotNullPtr<ContextType> user_ptr),
  NotNullPtr<ContextType> user_ptr)
{
  return CreateMirrorList(mirror_list, list, [&]()->void * { return &list; }, sub_path, GetSubElement, InitElement, SyncElement, user_ptr);
}
