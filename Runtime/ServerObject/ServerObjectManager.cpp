
#include "Runtime/RuntimeCommon.h"
#include "Runtime/ServerObject/ServerObjectManager.h"
#include "Runtime/ServerObject/ServerObjectSystem.h"
#include "Runtime/ServerObject/ServerObject.h"
#include "Runtime/ServerObject/ServerObjectSerialize.h"
#include "Runtime/Map/MapHandles.refl.h"

#include "StormNet/NetBitUtil.h"

ServerObjectManager::ServerObjectManager(const std::vector<ServerObjectStaticInitData> & static_objects,
                                         const std::vector<ServerObjectStaticInitData> & dynamic_objects,
                                         int max_dynamic_objects, int num_reserved_slots)
{
  m_NumGUIDS = static_objects.size() + max_dynamic_objects;
  m_GUIDs = std::shared_ptr<uint32_t[]>(new uint32_t[m_NumGUIDS]);

  int slot_index = 0;
  for (auto & obj : static_objects)
  {
    auto ptr = g_ServerObjectSystem.AllocateObject(obj.m_TypeIndex);
    ptr->m_IsStatic = true;
    ptr->m_TypeIndex = (int)obj.m_TypeIndex;
    ptr->m_SlotIndex = -1;
    ptr->m_FramesAlive = 0;
    ptr->m_ServerObjectHandle.m_SlotId = slot_index;
    ptr->m_ServerObjectHandle.m_Gen = 0;
    ptr->m_EventDispatch = ptr->GetEventDispatch();      
    ptr->InitPosition(obj.m_InitPosition);
    m_StaticObjects.emplace_back(ptr);

    m_GUIDs[slot_index] = obj.m_GUID;

    ++slot_index;
  }

  m_ReservedSlots = num_reserved_slots;
  m_MaxDynamicObjects = max_dynamic_objects;

  m_DynamicObjectGen.resize(max_dynamic_objects);
  m_DynamicObjects.Reserve(max_dynamic_objects);

  for (auto & obj : dynamic_objects)
  {
    auto ptr = CreateDynamicObjectInternal((int)obj.m_TypeIndex, obj.m_InitData.GetValue(), true);
    if (ptr)
    {
      ptr->InitPosition(obj.m_InitPosition);

      auto dynamic_slot_index = ptr->m_SlotIndex + slot_index;
      m_GUIDs[dynamic_slot_index] = obj.m_GUID;
    }
  }
}

ServerObjectManager::ServerObjectManager(const ServerObjectManager & rhs)
{
  m_StaticObjects.reserve(rhs.m_StaticObjects.size());

  for (auto & obj : rhs.m_StaticObjects)
  {
    auto ptr = g_ServerObjectSystem.DuplicateObject(obj);
    ptr->m_SlotIndex = -1;
    m_StaticObjects.emplace_back(ptr);
  }

  m_DynamicObjectGen = rhs.m_DynamicObjectGen;
  m_DynamicObjects.Reserve(rhs.m_DynamicObjects.Size());

  for (auto obj : rhs.m_DynamicObjects)
  {
    auto ptr = g_ServerObjectSystem.DuplicateObject(obj.second.m_ServerObject);
    ptr->m_SlotIndex = (int)obj.first;
    m_DynamicObjects.EmplaceAt(obj.first, DynamicObjectInfo{ ptr, obj.second.m_TypeIndex, obj.second.m_Original });
  }

  m_ReservedSlots = rhs.m_ReservedSlots;
  m_MaxDynamicObjects = rhs.m_MaxDynamicObjects;

  m_GUIDs = rhs.m_GUIDs;
  m_NumGUIDS = rhs.m_NumGUIDS;
}

ServerObjectManager::~ServerObjectManager()
{
  for (auto & obj : m_StaticObjects)
  {
    g_ServerObjectSystem.FreeObject(obj);
  }

  for (auto obj : m_DynamicObjects)
  {
    g_ServerObjectSystem.FreeObject(obj.second.m_ServerObject);
  }
}

ServerObjectManager & ServerObjectManager::operator = (const ServerObjectManager & rhs)
{
  ASSERT(m_StaticObjects.size() == rhs.m_StaticObjects.size(), "Bad copy of ServerObjectManager");
  ASSERT(m_MaxDynamicObjects == rhs.m_MaxDynamicObjects, "Bad copy of ServerObjectManager");
  ASSERT(m_ReservedSlots == rhs.m_ReservedSlots, "Bad copy of ServerObjectManager");

  for(std::size_t index = 0, end = m_StaticObjects.size(); index < end; ++index)
  {
    g_ServerObjectSystem.CopyObject(m_StaticObjects[index], rhs.m_StaticObjects[index]);
  }

  for (std::size_t index = 0, end = m_MaxDynamicObjects; index < end; ++index)
  {
    if (rhs.m_DynamicObjects.HasAt(index))
    {
      if (m_DynamicObjects.HasAt(index))
      {
        if (m_DynamicObjects[index].m_TypeIndex == rhs.m_DynamicObjects[index].m_TypeIndex)
        {
          g_ServerObjectSystem.CopyObject(m_DynamicObjects[index].m_ServerObject, rhs.m_DynamicObjects[index].m_ServerObject);
          continue;
        }

        m_DynamicObjects[index].m_ServerObject->Destroy(*this);
      }

      auto ptr = g_ServerObjectSystem.DuplicateObject(rhs.m_DynamicObjects[index].m_ServerObject);
      ptr->m_SlotIndex = (int)index;
      m_DynamicObjects.EmplaceAt(index, DynamicObjectInfo{ ptr, rhs.m_DynamicObjects[index].m_TypeIndex });
    }
    else
    {
      if (m_DynamicObjects.HasAt(index))
      {
        m_DynamicObjects[index].m_ServerObject->Destroy(*this);
      }
    }
  }

  m_ReservedSlots = rhs.m_ReservedSlots;
  m_MaxDynamicObjects = rhs.m_MaxDynamicObjects;

  return *this;
}

NullOptPtr<ServerObject> ServerObjectManager::GetReservedSlotObject(std::size_t slot_index)
{
  if (slot_index >= m_ReservedSlots)
  {
    return nullptr;
  }

  auto dynamic_object_info = m_DynamicObjects.TryGet(slot_index);
  return dynamic_object_info ? dynamic_object_info->m_ServerObject : nullptr;
}

NullOptPtr<ServerObject> ServerObjectManager::ResolveMapHandle(const MapServerObjectHandle & handle)
{
  uint32_t guid = handle.m_GUID;

  int slot_index = -1;
  for(int index = 0; index < m_NumGUIDS; ++index)
  {
    if(m_GUIDs[index] == guid)
    {
      slot_index = index;
      break;
    }
  }

  if(slot_index < 0)
  {
    return nullptr;
  }

  if (slot_index < (int)m_StaticObjects.size())
  {
    return const_cast<ServerObject *>(m_StaticObjects[slot_index]);
  }

  slot_index -= (int)m_StaticObjects.size();
  if (m_DynamicObjects[slot_index].m_Original == false)
  {
    return nullptr;
  }

  auto ptr = m_DynamicObjects.TryGet(slot_index);
  return ptr ? const_cast<ServerObject *>(ptr->m_ServerObject) : nullptr;
}

void ServerObjectManager::IncrementTimeAlive()
{
  for (auto & obj : m_StaticObjects)
  {
    obj->m_FramesAlive++;
  }

  for (auto obj : m_DynamicObjects)
  {
    obj.second.m_ServerObject->m_FramesAlive++;
  }
}

void ServerObjectManager::CreateUpdateList(ServerObjectUpdateList & update_list)
{
  std::vector<std::pair<int, NotNullPtr<ServerObject>>> update_objs;
  update_objs.reserve(m_StaticObjects.size() + m_DynamicObjects.Size());

  for (auto & obj : m_StaticObjects)
  {
    update_objs.emplace_back(std::make_pair(obj->m_TypeIndex, obj));
  }

  for (auto obj : m_DynamicObjects)
  {
    auto ptr = obj.second.m_ServerObject;
    update_objs.emplace_back(std::make_pair(ptr->m_TypeIndex, ptr));
  }

  std::sort(update_objs.begin(), update_objs.end(), 
    [](const std::pair<int, NotNullPtr<ServerObject>> & a, std::pair<int, NotNullPtr<ServerObject>> & b) 
    {
      return a.first < b.first;
    });

  for (auto & elem : update_objs)
  {
    g_ServerObjectSystem.m_ObjectTypes[elem.first].m_AddToUpdateList(elem.second, update_list);
  }
}

int ServerObjectManager::GetHandleBits() const
{
  return GetRequiredBits(m_StaticObjects.size() + m_DynamicObjects.Size());
}

int ServerObjectManager::GetMaxDynamicObjects() const
{
  return m_MaxDynamicObjects;
}

void ServerObjectManager::Serialize(NetBitWriter & writer) const
{
  ServerObjectNetBitWriter so_writer(writer, this);
  for (auto & obj : m_StaticObjects)
  {
    auto type_index = obj->m_TypeIndex;
    g_ServerObjectSystem.m_ObjectTypes[type_index].m_ObjectSerialize(obj, so_writer);
  }

  for (std::size_t index = 0; index < m_MaxDynamicObjects; ++index)
  {
    auto obj = m_DynamicObjects.TryGet(index);

    if (obj)
    {
      so_writer.WriteBits(1, 1);

      auto type_index = obj->m_TypeIndex;
      so_writer.WriteBits(type_index, GetRequiredBits(g_ServerObjectSystem.m_ObjectTypes.size() - 1));

      auto original = obj->m_Original;
      so_writer.WriteBits(original ? 1 : 0, 1);

      auto lifetime = std::min(7, obj->m_ServerObject->m_FramesAlive);
      so_writer.WriteBits((uint64_t)lifetime, 3);

      g_ServerObjectSystem.m_ObjectTypes[type_index].m_ObjectSerialize(obj->m_ServerObject, so_writer);
    }
    else
    {
      so_writer.WriteBits(0, 1);
    }
  }
}

void ServerObjectManager::Deserialize(NetBitReader & reader)
{
  ServerObjectNetBitReader so_reader(reader, this);
  for (auto & obj : m_StaticObjects)
  {
    auto type_index = obj->m_TypeIndex;
    g_ServerObjectSystem.m_ObjectTypes[type_index].m_ObjectDeserialize(obj, so_reader);
  }

  for (std::size_t index = 0; index < m_MaxDynamicObjects; ++index)
  {
    auto valid = so_reader.ReadUBits(1);
    auto obj = m_DynamicObjects.TryGet(index);

    if (valid)
    {
      auto type_index = so_reader.ReadUBits(GetRequiredBits(g_ServerObjectSystem.m_ObjectTypes.size() - 1));
      auto original = so_reader.ReadUBits(1) != 0;
      auto lifetime = so_reader.ReadUBits(3);

      if (obj)
      {
        if (obj->m_TypeIndex == type_index)
        {
          g_ServerObjectSystem.m_ObjectTypes[type_index].m_ObjectDeserialize(obj->m_ServerObject, so_reader);
          obj->m_ServerObject->m_FramesAlive = (int)lifetime;
          obj->m_Original = original;
          continue;
        }
        
        obj->m_ServerObject->Destroy(*this);
      }

      auto ptr = CreateDynamicObjectInternal((int)type_index, (int)index, nullptr, original);
      g_ServerObjectSystem.m_ObjectTypes[type_index].m_ObjectDeserialize(ptr, so_reader);
      ptr->m_FramesAlive = (int)lifetime;
    }
    else if(obj)
    {
      obj->m_ServerObject->Destroy(*this);
    }
  }
}

int ServerObjectManager::GetNewDynamicObjectId()
{
  for (std::size_t index = m_ReservedSlots, end = m_MaxDynamicObjects; index < end; index++)
  {
    if (m_DynamicObjects.HasAt(index) == false)
    {
      return (int)index;
    }
  }

  return -1;
}

NullOptPtr<ServerObject> ServerObjectManager::CreateDynamicObjectInternal(int type_index,
        NullOptPtr<const ServerObjectInitData> init_data, bool original)
{
  auto slot_index = GetNewDynamicObjectId();
  if (slot_index == -1)
  {
    return nullptr;
  }

  return CreateDynamicObjectInternal(type_index, slot_index, init_data, original);
}

NullOptPtr<ServerObject> ServerObjectManager::CreateDynamicObjectInternal(int type_index, int slot_index,
        NullOptPtr<const ServerObjectInitData> init_data, bool original)
{
  auto ptr = g_ServerObjectSystem.AllocateObject(type_index, init_data);
  ptr->m_IsStatic = false;
  ptr->m_TypeIndex = type_index;
  ptr->m_SlotIndex = slot_index;
  ptr->m_ServerObjectHandle.m_SlotId = slot_index + (int)m_StaticObjects.size();
  ptr->m_ServerObjectHandle.m_Gen = m_DynamicObjectGen[slot_index];
  ptr->m_EventDispatch = ptr->GetEventDispatch();

  m_DynamicObjects.EmplaceAt((std::size_t)slot_index, DynamicObjectInfo{ptr, (std::size_t)type_index, original});
  return ptr;
}

void ServerObjectManager::DestroyDynamicObjectInternal(NotNullPtr<ServerObject> ptr)
{
  auto slot_index = ptr->m_ServerObjectHandle.m_SlotId - m_StaticObjects.size();
  ASSERT(slot_index >= 0, "Attempting to free a static object");

  if (m_DynamicObjects.HasAt(slot_index) == false)
  {
    ASSERT(slot_index >= 0, "Attempting to free an already freed object");
    return;
  }

  m_DynamicObjectGen[slot_index]++;
  
  g_ServerObjectSystem.FreeObject(m_DynamicObjects[slot_index].m_ServerObject);
  m_DynamicObjects.RemoveAt(slot_index);
}

void ServerObjectManager::FinalizeHandles()
{
  for (auto & obj : m_StaticObjects)
  {
    g_ServerObjectSystem.ResetObjectHandles(obj, *this);
  }

  for (auto obj : m_DynamicObjects)
  {
    g_ServerObjectSystem.ResetObjectHandles(obj.second.m_ServerObject, *this);
  }

  for (auto & gen : m_DynamicObjectGen)
  {
    gen = 0;
  }
}

NullOptPtr<ServerObject> ServerObjectManager::ResolveHandle(int slot_index, int gen) const
{
  if (slot_index < 0)
  {
    return nullptr;
  }

  if (slot_index < (int)m_StaticObjects.size())
  {
    if (gen != 0)
    {
      return nullptr;
    }

    return const_cast<ServerObject *>(m_StaticObjects[slot_index]);
  }

  slot_index -= (int)m_StaticObjects.size();
  if (m_DynamicObjectGen[slot_index] != gen)
  {
    return nullptr;
  }

  auto ptr = m_DynamicObjects.TryGet(slot_index);
  return ptr ? const_cast<ServerObject *>(ptr->m_ServerObject) : nullptr;
}

NullOptPtr<ServerObject> ServerObjectManager::GetReservedSlotObjectInternal(std::size_t slot_index, std::size_t type_index)
{
  if (slot_index >= m_ReservedSlots)
  {
    return nullptr;
  }

  auto dynamic_object_info = m_DynamicObjects.TryGet(slot_index);
  return dynamic_object_info && dynamic_object_info->m_TypeIndex == type_index ? dynamic_object_info->m_ServerObject : nullptr;
}
