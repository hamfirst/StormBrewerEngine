#pragma once

#include <StormSockets\StormFixedBlockAllocator.h>
#include <StormSockets\StormMemOps.h>

#include <stdint.h>
#include <atomic>
#include <exception>

namespace StormSockets
{
	struct StormMessageHeaderReader
	{
	public:
		StormFixedBlockAllocator * m_Allocator;
		void * m_CurBlock;
		int m_DataLength;
		int m_ReadOffset;
		int m_FixedBlockSize;

	public:
		uint8_t ReadByte();
		uint16_t ReadInt16();
		uint32_t ReadInt32();
		uint64_t ReadInt64();

		int AdvanceToNextHeader(int & full_data_length);
		void Advance(int num_bytes);
	};
}
