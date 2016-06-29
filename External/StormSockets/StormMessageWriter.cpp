
#include "StormMessageWriter.h"
#include "StormMemOps.h"
#include "StormProfiling.h"

namespace StormSockets
{
	void StormMessageWriter::Init(StormFixedBlockAllocator * block_allocator, StormFixedBlockAllocator * sender_allocator, bool encrypt, int header_length, int trailer_length)
	{
		m_Allocator = block_allocator;
    m_SenderAllocator = sender_allocator;
    m_ReservedHeaderLength = header_length;
    m_ReservedTrailerLength = trailer_length;
    m_HeaderLength = header_length;
    m_TrailerLength = trailer_length;
    m_Encrypt = encrypt;

		StormFixedBlockHandle packet_handle = sender_allocator->AllocateBlock(StormFixedBlockType::Sender);
		StormMessageWriterData * packet_info = (StormMessageWriterData *)sender_allocator->ResolveHandle(packet_handle);

		m_PacketHandle = packet_handle;
		m_PacketInfo = packet_info;

		StormFixedBlockHandle block_handle = m_Allocator->AllocateBlock(StormFixedBlockType::BlockMem);

		m_PacketInfo->m_StartBlock = block_handle;
		m_PacketInfo->m_CurBlock = block_handle;
		m_PacketInfo->m_WriteOffset = header_length;
		m_PacketInfo->m_TotalLength = 0;
		m_PacketInfo->m_SendOffset = 0;
		m_PacketInfo->m_RefCount = 1;
	}

	void StormMessageWriter::SaveHeaderRoom()
	{
		// Save enough space for the header
		// In the worse case, the header is
		// 2 byte for opcode / length header
		// 8 bytes for the length
		// 4 bytes for the mask
		m_PacketInfo->m_WriteOffset = WebsocketMaxHeaderSize + m_ReservedHeaderLength;
	}

	void StormMessageWriter::CreateHeaderAndApplyMask(int opcode, bool fin, int mask)
	{
		StormFixedBlockHandle start_handle = m_PacketInfo->m_StartBlock;
		void * start_block = m_Allocator->ResolveHandle(start_handle);

		int packet_length = m_PacketInfo->m_TotalLength;
		int base_offset;
		int payload_bits;

		//if(packet_length == 0)
		{
			mask = 0;
		}

		if (packet_length < 126)
		{
			base_offset = 8;
			payload_bits = packet_length << 8;
		}
		else if (packet_length < 65536)
		{
			base_offset = 6;
			payload_bits = 126 << 8;
		}
		else
		{
			base_offset = 0;
			payload_bits = 127 << 8;
		}

		if (mask == 0)
		{
			base_offset += 4;
		}
		else
		{
			// Enable mask
			payload_bits |= 0x8000;
		}

		m_PacketInfo->m_SendOffset = base_offset;

		// Set the op code
		payload_bits |= opcode & 0x0F;

		// Set the fin bit
		if (fin)
		{
			payload_bits |= 0x80;
		}

    int cur_offset = base_offset + m_ReservedHeaderLength;
		Marshal::WriteInt16(start_block, cur_offset, (short)payload_bits);
    cur_offset += 2;

		if (packet_length >= 126)
		{
			if (packet_length < 65536)
			{
				Marshal::WriteInt16(start_block, cur_offset, Marshal::HostToNetworkOrder((uint16_t)packet_length));
				cur_offset += 2;
			}
			else
			{
				uint64_t pl = packet_length;
				uint64_t hpl = Marshal::HostToNetworkOrder(pl);
				Marshal::WriteInt64(start_block, cur_offset, hpl);
				cur_offset += 8;
			}
		}

		if (mask != 0)
		{
			// Write the mask
			Marshal::WriteInt32(start_block, cur_offset, mask);
			cur_offset += 4;
		}

		void * cur_block = start_block;
		int read_offset = cur_offset;
		int data_length = packet_length;

		// Include the header in the total length
    int header_size = WebsocketMaxHeaderSize - base_offset;
		m_PacketInfo->m_TotalLength = data_length + header_size;

		if (mask != 0)
		{
			// Mask out the rest of the data
			do
			{
				if (data_length >= 4 && read_offset + 4 <= m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
				{
					int val = Marshal::ReadInt32(cur_block, read_offset);
					val ^= mask;
					Marshal::WriteInt32(cur_block, read_offset, val);
					read_offset += 4;
					data_length -= 4;
				}
				else if (data_length > 0 && read_offset != m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
				{
					int val = Marshal::ReadByte(cur_block, read_offset);
					val ^= mask;
					Marshal::WriteByte(cur_block, read_offset, (uint8_t)val);
					read_offset += 1;
					data_length -= 1;

					mask = (mask << 24) | (mask >> 8);
				}

				if (read_offset == m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
				{
					cur_block = m_Allocator->GetNextBlock(cur_block);
					read_offset = m_ReservedHeaderLength;
				}
			} while (data_length > 0 && cur_block != NULL);
		}
	}

	void StormMessageWriter::WriteByte(uint8_t b)
	{
		uint64_t prof = Profiling::StartProfiler();

		StormFixedBlockHandle cur_block = m_PacketInfo->m_CurBlock;
		void * ptr = m_Allocator->ResolveHandle(cur_block);

		int write_offset = m_PacketInfo->m_WriteOffset;
		Marshal::WriteByte(ptr, write_offset, b);

		write_offset += 1;
		m_PacketInfo->m_TotalLength += 1;

		if (write_offset >= m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			// Allocate a new block
			m_PacketInfo->m_CurBlock = m_Allocator->AllocateBlock(cur_block, StormFixedBlockType::BlockMem);
			m_PacketInfo->m_WriteOffset = m_ReservedHeaderLength;
		}
		else
		{
			m_PacketInfo->m_WriteOffset = write_offset;
		}

		Profiling::EndProfiler(prof, ProfilerCategory::kWriteByte);
	}

	void StormMessageWriter::WriteUTF8Char(wchar_t c)
	{
		if (c < 0x80)
		{
			WriteByte((uint8_t)c);
			return;
		}

		if (c < 0x800)
		{
			c -= (wchar_t)0x80;
			uint8_t b1 = (uint8_t)((c >> 6) | 0xC0);
			uint8_t b2 = (uint8_t)((c & 0x3F) | 0x80);

			WriteByte(b1);
			WriteByte(b2);
			return;
		}

		c -= (wchar_t)0x880;
		uint8_t ba = (uint8_t)((c >> 12) | 0xE0);
		uint8_t bb = (uint8_t)(((c >> 6) & 0x3F) | 0x80);
		uint8_t bc = (uint8_t)((c & 0x3F) | 0x80);

		WriteByte(ba);
		WriteByte(bb);
		WriteByte(bc);
	}

	void StormMessageWriter::WriteInt16(uint16_t s)
	{
		int write_offset = m_PacketInfo->m_WriteOffset;
		if (write_offset + 2 > m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			WriteByte((uint8_t)s);
			WriteByte((uint8_t)(s >> 8));
			return;
		}

		StormFixedBlockHandle cur_block = m_PacketInfo->m_CurBlock;
		void * ptr = m_Allocator->ResolveHandle(cur_block);
		Marshal::WriteInt16(ptr, write_offset, s);

		write_offset += 2;
		m_PacketInfo->m_TotalLength += 2;

		if (write_offset >= m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			// Allocate a new block
			m_PacketInfo->m_CurBlock = m_Allocator->AllocateBlock(cur_block, StormFixedBlockType::BlockMem);
			m_PacketInfo->m_WriteOffset = m_ReservedHeaderLength;
		}
		else
		{
			m_PacketInfo->m_WriteOffset = write_offset;
		}
	}

	void StormMessageWriter::WriteInt32(uint32_t i)
	{
		int write_offset = m_PacketInfo->m_WriteOffset;
		if (write_offset + 4 > m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			WriteInt16((uint16_t)i);
			WriteInt16((uint16_t)(i >> 16));
			return;
		}

		StormFixedBlockHandle cur_block = m_PacketInfo->m_CurBlock;
		void * ptr = m_Allocator->ResolveHandle(cur_block);
		Marshal::WriteInt32(ptr, write_offset, i);

		write_offset += 4;
		m_PacketInfo->m_TotalLength += 4;

		if (write_offset >= m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			// Allocate a new block
			m_PacketInfo->m_CurBlock = m_Allocator->AllocateBlock(cur_block, StormFixedBlockType::BlockMem);
			m_PacketInfo->m_WriteOffset = m_ReservedHeaderLength;
		}
		else
		{
			m_PacketInfo->m_WriteOffset = write_offset;
		}
	}

	void StormMessageWriter::WriteInt64(uint64_t l)
	{
		int write_offset = m_PacketInfo->m_WriteOffset;
		if (write_offset + 8 > m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			WriteInt32((uint32_t)l);
			WriteInt32((uint32_t)(l >> 32));
			return;
		}

		StormFixedBlockHandle cur_block = m_PacketInfo->m_CurBlock;
		void * ptr = m_Allocator->ResolveHandle(cur_block);
		Marshal::WriteInt64(ptr, write_offset, l);

		write_offset += 8;
		m_PacketInfo->m_TotalLength += 8;

		if (write_offset >= m_Allocator->GetBlockSize() - m_ReservedTrailerLength)
		{
			// Allocate a new block
			m_PacketInfo->m_CurBlock = m_Allocator->AllocateBlock(cur_block, StormFixedBlockType::BlockMem);
			m_PacketInfo->m_WriteOffset = m_ReservedHeaderLength;
		}
		else
		{
			m_PacketInfo->m_WriteOffset = write_offset;
		}
	}

	void StormMessageWriter::WriteByteBlock(const void * buffer, int start_offset, int length)
	{
		int write_offset = m_PacketInfo->m_WriteOffset;
		StormFixedBlockHandle cur_block = m_PacketInfo->m_CurBlock;
		void * ptr = m_Allocator->ResolveHandle(cur_block);
		ptr = Marshal::MemOffset(ptr, write_offset);
		int init_length = length;

		while (length > 0)
		{
			int space_avail = m_Allocator->GetBlockSize() - m_ReservedTrailerLength - write_offset;

			int write_len = (space_avail < length ? space_avail : length);
			Marshal::Copy(ptr, start_offset, buffer, write_len);

			length -= write_len;
			space_avail -= write_len;
			write_offset += write_len;
      buffer = Marshal::MemOffset(buffer, write_len);

			if (space_avail == 0)
			{
				// Allocate a new block
				cur_block = m_Allocator->AllocateBlock(cur_block, StormFixedBlockType::BlockMem);
				ptr = m_Allocator->ResolveHandle(cur_block);

				m_PacketInfo->m_CurBlock = cur_block;
				m_PacketInfo->m_WriteOffset = m_ReservedHeaderLength;

				write_offset = m_ReservedHeaderLength;
			}
		}

		m_PacketInfo->m_TotalLength += init_length;
		m_PacketInfo->m_WriteOffset = write_offset;
	}

  StormMessageWriter StormMessageWriter::Duplicate()
  {
    StormMessageWriter writer;
    writer.m_Allocator = m_Allocator;
    writer.m_SenderAllocator = m_SenderAllocator;
    writer.m_Mode = m_Mode;
    writer.m_Final = m_Final;
    writer.m_Encrypt = m_Encrypt;
    writer.m_ReservedHeaderLength = m_ReservedHeaderLength;
    writer.m_ReservedTrailerLength = m_ReservedTrailerLength;
    writer.m_HeaderLength = m_ReservedHeaderLength;
    writer.m_TrailerLength = m_ReservedTrailerLength;

    StormFixedBlockHandle packet_handle = m_SenderAllocator->AllocateBlock(StormFixedBlockType::Sender);
    StormMessageWriterData * packet_info = (StormMessageWriterData *)m_SenderAllocator->ResolveHandle(packet_handle);

    writer.m_PacketHandle = packet_handle;
    writer.m_PacketInfo = packet_info;

    StormFixedBlockHandle dest_block = m_Allocator->AllocateBlock(StormFixedBlockType::BlockMem);

    writer.m_PacketInfo->m_StartBlock = dest_block;
    writer.m_PacketInfo->m_CurBlock = dest_block;
    writer.m_PacketInfo->m_WriteOffset = m_PacketInfo->m_WriteOffset;
    writer.m_PacketInfo->m_TotalLength = m_PacketInfo->m_TotalLength;
    writer.m_PacketInfo->m_SendOffset = m_PacketInfo->m_SendOffset;
    writer.m_PacketInfo->m_RefCount = 1;

    StormFixedBlockHandle src_block = m_PacketInfo->m_StartBlock;
    while (src_block != InvalidBlockHandle)
    {
      memcpy(m_Allocator->ResolveHandle(dest_block), m_Allocator->ResolveHandle(src_block), m_Allocator->GetBlockSize());
      src_block = m_Allocator->GetNextBlock(src_block);

      if (src_block != InvalidBlockHandle)
      {
        dest_block = m_Allocator->AllocateBlock(dest_block, StormFixedBlockType::BlockMem);
        writer.m_PacketInfo->m_CurBlock = dest_block;
      }
    }

    return writer;
  }
}

