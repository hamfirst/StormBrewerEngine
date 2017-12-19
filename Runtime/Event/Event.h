#pragma once

#include "Runtime/RuntimeCommon.h"

#include <hash/Hash.h>

struct Box;

class GameContainer;
class GameLogicContainer;

class Entity;
class ServerObject;

struct EventMetaData
{
  EventMetaData() = default;

  EventMetaData(NotNullPtr<GameContainer> game_container) :
    m_GameContainer(game_container)
  {

  }


  EventMetaData(NotNullPtr<Entity> entity_src, NotNullPtr<GameContainer> game_container) :
    m_SourceEntity(entity_src), 
    m_GameContainer(game_container)
  {

  }

  EventMetaData(NotNullPtr<ServerObject> server_object_src, NotNullPtr<GameLogicContainer> game_logic_container) :
    m_SourceServerObject(server_object_src),
    m_GameLogicContainer(game_logic_container)
  {

  }

  EventMetaData(GameLogicContainer & game_logic_container) :
    m_GameLogicContainer(&game_logic_container)
  {

  }

  NullOptPtr<Entity> m_SourceEntity = nullptr;
  NullOptPtr<ServerObject> m_SourceServerObject = nullptr;
  NullOptPtr<GameContainer> m_GameContainer = nullptr;
  NullOptPtr<GameLogicContainer> m_GameLogicContainer = nullptr;
  NullOptPtr<const Box> m_Start = nullptr;
  NullOptPtr<const Box> m_End = nullptr;
};


#define DECLARE_EVENT(EventType) static const uint32_t TypeNameHash = COMPILE_TIME_CRC32_STR(#EventType);
