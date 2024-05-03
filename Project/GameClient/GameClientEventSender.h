#pragma once

#include "Game/NetworkEvents/GameNetworkEvents.refl.h"

class GameClientEventSender
{
public:

  template <typename EventType>
  void SendClientEvent(const EventType & event, std::size_t client_index)
  {
    static_assert(std::is_base_of<ClientNetworkEvent, EventType>::value, "Sending client event of the wrong type");

    auto & type_db = ClientNetworkEvent::__s_TypeDatabase;
    auto class_id = type_db.GetClassId<EventType>();

    SendClientEvent(class_id, &event, client_index);
  }

protected:

  virtual void SendClientEvent(std::size_t class_id, const void * event_ptr, std::size_t client_index) { };
};

