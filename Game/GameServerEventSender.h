#pragma once

#include "Foundation/Common.h"

#include "Game/GameNetworkEvents.refl.h"

#include "Server/ServerObject/ServerObjectHandle.h"

class GameServerEventSender
{
public:

  template <typename T>
  void BroadcastEvent(const T & event)
  {
    static_assert(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<T>();
    SendGlobalEvent(class_id, &event);
  }

  template <typename T>
  void SendEventToTarget(const T & event, std::size_t connection)
  {
    static_assert(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<T>();
    SendGlobalEvent(class_id, &event, connection);
  }

  template <typename T>
  void BroadcastEntityEvent(const T & event, ServerObjectHandle object_handle)
  {
    static_assert(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<T>();
    SendEntityEvent(class_id, &event, object_handle);
  }

  template <typename T>
  void SendEntityEventToTarget(const T & event, ServerObjectHandle object_handle, std::size_t connection)
  {
    static_assert(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<T>();
    SendEntityEvent(class_id, &event, connection, object_handle);
  }

  template <typename T>
  void BroadcastServerAuthEvent(const T & event)
  {
    static_assert(std::is_base_of<ServerAuthNetworkEvent, T>::value, "Sending auth event of the wrong class");

    auto & type_db = ServerAuthNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<T>();
    SendAuthEvent(class_id, &event);
  }

  template <typename T>
  bool ReconcileEvent(uint64_t event_id = 0)
  {
    return ReconcileEvent(typeid(T).hash_code(), event_id, {});
  }

  template <typename T>
  bool ReconcileEvent(const GameNetVec2 & pos, uint64_t event_id = 0)
  {
    return ReconcileEvent(typeid(T).hash_code(), event_id, pos);
  }

  template <typename T>
  bool ReconcileEvent(const GameNetVec2 & pos, const GameNetVec2 & normal, int16_t extra = 0)
  {
    uint32_t x = (uint32_t)(normal.x.GetRawVal() & 0xFFFF8000);
    uint32_t y = (uint32_t)(normal.y.GetRawVal() & 0xFFFF8000);
    uint64_t event_id = (((uint64_t)extra) << 40) | (((uint64_t)x) << 20) | (((uint64_t)y) << 0);

    return ReconcileEvent(typeid(T).hash_code(), event_id, pos);
  }

  virtual void BlockRewind(std::size_t connection) {};

protected:
  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr) {}
  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id) {}
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle) {}
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) {}
  virtual void SendAuthEvent(std::size_t class_id, const void * event_ptr) {}
  virtual bool ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos) { return true; }
};
