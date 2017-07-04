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
    static_cast(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<DataType>();
    SendGlobalEvent(class_id, &event);
  }

  template <typename T>
  void SendEventToTarget(const T & event, std::size_t connection)
  {
    static_cast(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<DataType>();
    SendGlobalEvent(class_id, &event, connection);
  }

  template <typename T>
  void BroadcastEntityEvent(const T & event, ServerObjectHandle object_handle)
  {
    static_cast(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<DataType>();
    SendEntityEvent(class_id, &event, object_handle);
  }

  template <typename T>
  void SendEntityEventToTarget(const T & event, ServerObjectHandle object_handle, std::size_t connection)
  {
    static_cast(std::is_base_of<GlobalNetworkEvent, T>::value, "Sending global event of the wrong class");

    auto & type_db = GlobalNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.template GetClassId<DataType>();
    SendEntityEvent(class_id, &event, connection, object_handle);
  }

protected:
  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr) {}
  virtual void SendGlobalEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id) {}
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, ServerObjectHandle object_handle) {}
  virtual void SendEntityEvent(std::size_t class_id, void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) {}
};
