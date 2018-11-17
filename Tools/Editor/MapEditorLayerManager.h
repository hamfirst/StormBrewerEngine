#pragma once

#include "Foundation/Common.h"
#include "Foundation/SparseList/SparseList.h"
#include "Runtime/Map/MapDef.refl.h"

#include "MapEditor.h"
#include "DocumentListValueWatcher.h"
#include "DocumentSubValueListMirror.h"

class MapEditor;

template <typename LayerType, typename ManagerType>
class MapEditorLayerManager
{
public:
  MapEditorLayerManager(czstr path, NotNullPtr<MapEditor> editor, MapDef & map, RMergeList<LayerType> & layer_list) :
    m_Editor(editor),
    m_Map(map),
    m_LayerList(layer_list),
    m_Watcher(m_Editor)
  {
    m_Watcher.SetPath(path, false, false, [] {return true; });
    m_Watcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { HandleListChange(change); });

    Resync();
  }

  ~MapEditorLayerManager()
  {

  }

  NullOptPtr<ManagerType> GetLayerManager(int layer_index)
  {
    if (m_Managers.HasAt((std::size_t)layer_index) == false)
    {
      return nullptr;
    }

    return m_Managers[layer_index].get();
  }

  template <typename Visitor>
  void VisitLayers(Visitor && visitor)
  {
    for (auto elem : m_Managers)
    {
      visitor(elem.first, elem.second);
    }
  }

protected:
  void Resync()
  {
    SparseList<std::unique_ptr<ManagerType>> old_layers = std::move(m_Managers);

    for (auto elem : m_LayerList)
    {
      m_Managers.EmplaceAt(elem.first, std::make_unique<ManagerType>(m_Editor, m_Map, (int)elem.first));
    }
  }

  void HandleListChange(const ReflectionChangeNotification & change)
  {
    if (change.m_Type == ReflectionNotifyChangeType::kInsert)
    {
      if (m_LayerList.HasAt(change.m_SubIndex))
      {
        m_Managers.EmplaceAt(change.m_SubIndex, std::make_unique<ManagerType>(m_Editor, m_Map, (int)change.m_SubIndex));
      }
    }
    else if (change.m_Type == ReflectionNotifyChangeType::kRemove)
    {
      m_Managers.RemoveAt(change.m_SubIndex);
    }
    else
    {
      Resync();
    }
  }

private:
  NotNullPtr<MapEditor> m_Editor;

  MapDef & m_Map;
  RMergeList<LayerType> & m_LayerList;

  using ManagerPtr = std::unique_ptr<ManagerType>;
  using ManagerPtrList = SparseList<ManagerPtr>;

  ManagerPtrList m_Managers;
  DocumentListValueWatcher m_Watcher;
};

