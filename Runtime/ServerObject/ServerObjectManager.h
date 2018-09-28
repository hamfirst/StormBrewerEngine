#pragma once

#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectUpdate.h"
#include "Runtime/ServerObject/ServerObjectDef.refl.h"

#include "Foundation/SparseList/SparseList.h"

class ServerObject;
class ServerObjectInitData;
class ServerObjectHandle;

struct MapServerObjectHandle;

struct ServerObjectStaticInitData
{
  std::size_t m_TypeIndex;
  ServerObjectInitDataPolyType m_InitData;
  Vector2 m_InitPosition;
  uint32_t m_GUID;
};

class ServerObjectManager
{
public:

  ServerObjectManager(const std::vector<ServerObjectStaticInitData> & static_objects, 
                      const std::vector<ServerObjectStaticInitData> & dynamic_objects,
                      int max_dynamic_objects, int num_reserved_slots);
  ServerObjectManager(const ServerObjectManager & rhs);

  ~ServerObjectManager();

  ServerObjectManager & operator = (const ServerObjectManager & rhs);

  template <typename T>
  NullOptPtr<T> CreateDynamicObject(NullOptPtr<ServerObjectInitData> init_data = nullptr)
  {
    auto ptr = CreateDynamicObjectInternal((int)T::TypeIndex, init_data, false);
    return static_cast<T *>(ptr);
  }

  template <typename T>
  NullOptPtr<T> CreateDynamicObject(std::size_t reserved_slot, NullOptPtr<ServerObjectInitData> init_data = nullptr)
  {
    auto ptr = CreateDynamicObjectInternal((int)T::TypeIndex, (int)reserved_slot, init_data, false);
    return static_cast<T *>(ptr);
  }

  template <typename Visitor>
  void VisitObjects(Visitor && visitor)
  {
    std::size_t object_index = 0;
    for (std::size_t end = m_StaticObjects.size(); object_index < end; ++object_index)
    {
      visitor(object_index, m_StaticObjects[object_index]);
    }

    for (auto elem : m_DynamicObjects)
    {
      visitor(elem.first + object_index, elem.second.m_ServerObject);
    }
  }

  NullOptPtr<ServerObject> GetReservedSlotObject(std::size_t slot_index);

  template <typename T>
  NullOptPtr<T> GetReservedSlotObjectAs(std::size_t slot_index)
  {
    static_assert(std::is_base_of<ServerObject, T>::value, "Must resolve to server object type");
    return static_cast<NullOptPtr<T>>(GetReservedSlotObjectInternal(slot_index, T::TypeIndex));
  }

  NullOptPtr<ServerObject> ResolveMapHandle(const MapServerObjectHandle & handle);

  template <typename T>
  NullOptPtr<T> ResolveMapHandleAs(const MapServerObjectHandle & handle)
  {
    static_assert(std::is_base_of<ServerObject, T>::value, "Must resolve to server object type");
    auto ptr = ResolveMapHandle(handle);

    if(ptr)
    {
      return ptr->CastTo<T>();
    }

    return nullptr;
  }

  void IncrementTimeAlive();
  void CreateUpdateList(ServerObjectUpdateList & update_list);

  int GetHandleBits() const;
  int GetMaxDynamicObjects() const;

  void Serialize(NetBitWriter & writer) const;
  void Deserialize(NetBitReader & reader);

protected:

  friend class ServerObject;
  friend class ServerObjectHandle;

  friend class GameStage;

  int GetNewDynamicObjectId();
  NullOptPtr<ServerObject> CreateDynamicObjectInternal(int type_index,
          NullOptPtr<const ServerObjectInitData> init_data, bool orignal);
  NullOptPtr<ServerObject> CreateDynamicObjectInternal(int type_index, int slot_index,
          NullOptPtr<const ServerObjectInitData> init_data, bool original);
  void DestroyDynamicObjectInternal(NotNullPtr<ServerObject> ptr);

  void FinalizeHandles();
  NullOptPtr<ServerObject> ResolveHandle(int slot_index, int gen) const;
  NullOptPtr<ServerObject> GetReservedSlotObjectInternal(std::size_t slot_index, std::size_t type_index);

  struct DynamicObjectInfo
  {
    NullOptPtr<ServerObject> m_ServerObject;
    std::size_t m_TypeIndex;
    bool m_Original;
  };

private:

  std::vector<NotNullPtr<ServerObject>> m_StaticObjects;
  std::vector<int> m_DynamicObjectGen;
  SparseList<DynamicObjectInfo> m_DynamicObjects;
  int m_ReservedSlots;
  int m_MaxDynamicObjects;

  std::shared_ptr<uint32_t[]> m_GUIDs;
  int m_NumGUIDS;
};

