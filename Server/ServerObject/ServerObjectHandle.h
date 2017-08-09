#pragma once

#include "Server/ServerCommon.h"

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

class ServerObject;
class ServerObjectManager;

class ServerObjectHandle
{
public:

  ServerObjectHandle();

  template <typename T>
  NullOptPtr<T> ResolveTo(const ServerObjectManager & object_manager);

  NullOptPtr<ServerObject> Resolve(const ServerObjectManager & object_manager);

  void Reset();

  int GetRawSlotIndex() const;

private:

  void ResetGen(const ServerObjectManager & object_manager);

  friend class ServerObjectManager;
  friend class ServerObject;

  template <typename T>
  friend struct ServerObjectResetHandle;

  template <typename Type, class NetBitReader>
  friend struct NetSerializer;

  template <typename Type, class NetBitReader>
  friend struct NetDeserializer;

  int m_SlotId;
  int m_Gen;
};


template <class NetBitWriter>
struct NetSerializer<ServerObjectHandle, NetBitWriter>
{
  void operator()(const ServerObjectHandle & val, NetBitWriter & writer)
  {
    if (val.m_SlotId >= 0)
    {
      writer.WriteBits(1, 1);
      writer.WriteBits(val.m_SlotId, writer.GetServerManager()->GetHandleBits());
    }
    else
    {
      writer.WriteBits(0, 1);
    }
  }
};

template <class NetBitReader>
struct NetDeserializer<ServerObjectHandle, NetBitReader>
{
  void operator()(ServerObjectHandle & val, NetBitReader & reader)
  {
    auto val = reader.ReadBits(1);
    if (val)
    {
      auto server_manager = reader.GetServerManager();

      val.m_ServerObjectManager = server_manager;
      val.m_Gen = 0;
      val.m_SlotId = reader.ReadBits(server_manager->GetHandleBits());
    }
    else
    {
      val.m_SlotId = -1;
      val.m_Gen = 0;
      val.m_ServerObjectManager = nullptr;
    }
  }
};



