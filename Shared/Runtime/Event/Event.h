#pragma once

#include "Runtime/RuntimeCommon.h"

#include <hash/Hash.h>

struct Box;

class GameContainer;
class GameWorld;

class Entity;
class ServerObject;

struct EventMetaData
{
  EventMetaData() = default;

  EventMetaData(NotNullPtr<GameContainer> world) :
    m_GameContainer(world)
  {

  }


  EventMetaData(NotNullPtr<Entity> entity_src, NotNullPtr<GameContainer> world) :
    m_SourceEntity(entity_src), 
    m_GameContainer(world)
  {

  }

  EventMetaData(NotNullPtr<ServerObject> server_object_src, NotNullPtr<GameWorld> game_logic_container) :
    m_SourceServerObject(server_object_src),
    m_GameLogicContainer(game_logic_container)
  {

  }

  EventMetaData(GameWorld & game_logic_container) :
    m_GameLogicContainer(&game_logic_container)
  {

  }

  NullOptPtr<Entity> m_SourceEntity = nullptr;
  NullOptPtr<ServerObject> m_SourceServerObject = nullptr;
  NullOptPtr<GameContainer> m_GameContainer = nullptr;
  NullOptPtr<GameWorld> m_GameLogicContainer = nullptr;
  NullOptPtr<const Box> m_ActiveAreaStart = nullptr;
  NullOptPtr<const Box> m_ActiveAreaEnd = nullptr;
};


#define DECLARE_EVENT(EventType) static const uint32_t TypeNameHash = COMPILE_TIME_CRC32_STR(#EventType);
