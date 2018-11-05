#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "Runtime/ServerObject/ServerObjectManager.h"

class ServerObjectManager;

class ServerObjectNetBitWriter
{
public:
  ServerObjectNetBitWriter(NetBitWriter & writer, NotNullPtr<const ServerObjectManager> server_object_manager);

  void WriteBits(uint64_t val, int num_bits);
  void WriteSBits(int64_t val, int num_bits);

  void WriteBits(NetBitWriterCursor & cursor, uint64_t val, int num_bits);
  void WriteSBits(NetBitWriterCursor & cursor, int64_t val, int num_bits);

  void WriteBuffer(void * data, std::size_t num_bytes);

  NetBitWriterCursor Reserve(int num_bits);
  void RollBack(NetBitWriterCursor & cursor);

  NotNullPtr<const ServerObjectManager> GetServerManager();

  operator NetBitWriter & ();
  operator const NetBitWriter & () const;

  template <typename T>
  const T * GetParentObjectAs()
  {
    m_Writer.GetParentObjectAs<T>();
  }

  template <typename T>
  void SetParentObject(const T * t)
  {
    m_Writer.SetParentObject<T>(t);
  }

  void SetParentObject(const void * ptr, const void * (*cast)(std::size_t, const void *))
  {
    m_Writer.SetParentObject(ptr, cast);
  }

  auto GetParentObjectRaw() const { return m_Writer.GetParentObjectRaw(); }
  auto GetParentObjectCast() const { return m_Writer.GetParentObjectCast(); }

private:
  NetBitWriter & m_Writer;
  NotNullPtr<const ServerObjectManager> m_ServerObjectManager;
};

class ServerObjectNetBitReader
{
public:
  ServerObjectNetBitReader(NetBitReader & reader, NotNullPtr<ServerObjectManager> server_object_manager);

  uint64_t ReadUBits(int num_bits);
  int64_t ReadSBits(int num_bits);

  void ReadBuffer(void * buffer, std::size_t num_bytes);

  NotNullPtr<ServerObjectManager> GetServerManager();

  operator NetBitReader & ();
  operator const NetBitReader & () const;

  template <typename T>
  const T * GetParentObjectAs()
  {
    m_Reader.GetParentObjectAs<T>();
  }

  template <typename T>
  void SetParentObject(const T * t)
  {
    m_Reader.SetParentObject<T>(t);
  }

  void SetParentObject(const void * ptr, const void * (*cast)(std::size_t, const void *))
  {
    m_Reader.SetParentObject(ptr, cast);
  }

  auto GetParentObjectRaw() const { return m_Reader.GetParentObjectRaw(); }
  auto GetParentObjectCast() const { return m_Reader.GetParentObjectCast(); }

private:
  NetBitReader & m_Reader;
  NotNullPtr<ServerObjectManager> m_ServerObjectManager;
};


template <typename T, typename NetBitWriter>
void SerializeServerObject(const T & t, NetBitWriter & writer)
{
  NetSerializer<T, NetBitWriter> serializer;
  serializer(t, writer);
}

template <typename T, typename NetBitReader>
void DeserializeServerObject(T & t, NetBitReader & reader)
{
  NetDeserializer<T, NetBitReader> deserializer;
  deserializer(t, reader);
}

template <class NetBitWriter>
struct NetSerializer<ServerObjectManager, NetBitWriter>
{
  void operator()(const ServerObjectManager & val, NetBitWriter & writer)
  {
    val.Serialize(writer);
  }
};

template <class NetBitReader>
struct NetDeserializer<ServerObjectManager, NetBitReader>
{
  void operator()(ServerObjectManager & val, NetBitReader & reader)
  {
    val.Deserialize(reader);
  }
};

