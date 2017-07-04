
#include "Server/ServerCommon.h"
#include "Server/ServerObject/ServerObjectSerialzie.h"

ServerObjectNetBitWriter::ServerObjectNetBitWriter(NetBitWriter & writer, NotNullPtr<const ServerObjectManager> server_object_manager) :
  m_Writer(writer),
  m_ServerObjectManager(server_object_manager)
{

}

void ServerObjectNetBitWriter::WriteBits(uint64_t val, int num_bits)
{
  m_Writer.WriteBits(val, num_bits);
}

void ServerObjectNetBitWriter::WriteSBits(int64_t val, int num_bits)
{
  m_Writer.WriteSBits(val, num_bits);
}

void ServerObjectNetBitWriter::WriteBits(NetBitWriterCursor & cursor, uint64_t val, int num_bits)
{
  m_Writer.WriteBits(cursor, val, num_bits);
}

void ServerObjectNetBitWriter::WriteSBits(NetBitWriterCursor & cursor, int64_t val, int num_bits)
{
  m_Writer.WriteSBits(cursor, val, num_bits);
}

void ServerObjectNetBitWriter::WriteBuffer(void * data, std::size_t num_bytes)
{
  m_Writer.WriteBuffer(data, num_bytes);
}

NetBitWriterCursor ServerObjectNetBitWriter::Reserve(int num_bits)
{
  return m_Writer.Reserve(num_bits);
}

void ServerObjectNetBitWriter::RollBack(NetBitWriterCursor & cursor)
{
  m_Writer.RollBack(cursor);
}

NotNullPtr<const ServerObjectManager> ServerObjectNetBitWriter::GetServerManager()
{
  return m_ServerObjectManager;
}

ServerObjectNetBitReader::ServerObjectNetBitReader(NetBitReader & reader, NotNullPtr<ServerObjectManager> server_object_manager) :
  m_Reader(reader),
  m_ServerObjectManager(server_object_manager)
{

}

uint64_t ServerObjectNetBitReader::ReadUBits(int num_bits)
{
  return m_Reader.ReadUBits(num_bits);
}

int64_t ServerObjectNetBitReader::ReadSBits(int num_bits)
{
  return m_Reader.ReadSBits(num_bits);
}

void ServerObjectNetBitReader::ReadBuffer(void * buffer, std::size_t num_bytes)
{
  m_Reader.ReadBuffer(buffer, num_bytes);
}

NotNullPtr<ServerObjectManager> ServerObjectNetBitReader::GetServerManager()
{
  return m_ServerObjectManager;
}
