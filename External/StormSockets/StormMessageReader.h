#pragma once

#include <StormSockets\StormFixedBlockAllocator.h>
#include <StormSockets\StormSocketServerConnectionId.h>

#include <cstdint>


namespace StormSockets
{
	namespace StormSocketDataType
	{
		enum Index
		{
			Binary,
			Text,
			Ping,
			Pong,
			Continuation,
		};
	}

	struct StormMessageReaderData
	{
		void * m_CurBlock;
		int m_DataLength;
		int m_ReadOffset;
	};

	class StormMessageReader
	{
		StormMessageReaderData * m_PacketInfo;
		StormFixedBlockHandle m_PacketHandle;
		StormFixedBlockAllocator * m_Allocator;
		StormFixedBlockAllocator * m_ReaderAllocator;
		int m_FixedBlockSize;
		int m_PacketDataLen;
		int m_FullDataLen;
		StormSocketServerConnectionId m_ConnectionId;
		StormSocketDataType::Index m_DataType;
		bool m_FinalInSequence;

		friend class StormSocketServerBase;

	public:

		StormSocketDataType::Index GetDataType();

		bool GetFinalInSequence();

		void Init(StormFixedBlockAllocator * block_allocator, StormFixedBlockAllocator * reader_allocator, StormFixedBlockHandle cur_block,
			int data_len, int parse_offset, StormSocketServerConnectionId connection_id, int fixed_block_size);

		void SetNextBlock(const StormMessageReader & next_reader);
		bool InvalidateNext(StormMessageReader & next_reader);
		void AddLength(int data_len);

		void Advance();
		void FreeChain();
		int GetDataLength();

		uint8_t ReadByte();
		wchar_t ReadUTF8Char();
		uint16_t ReadInt16();
		uint32_t ReadInt32();
		uint64_t ReadInt64();
	};
}
