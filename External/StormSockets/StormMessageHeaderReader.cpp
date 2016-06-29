#include "StormMessageHeaderReader.h"

#include <stdexcept>

namespace StormSockets
{
	uint8_t StormMessageHeaderReader::ReadByte()
	{
		if (m_DataLength < 1)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		uint8_t v = Marshal::ReadByte(m_CurBlock, m_ReadOffset);

		m_ReadOffset += 1;
		m_DataLength -= 1;

		if (m_ReadOffset >= m_FixedBlockSize)
		{
			m_CurBlock = m_Allocator->GetNextBlock(m_CurBlock);
			m_ReadOffset = 0;
		}

		return v;
	}

	uint16_t StormMessageHeaderReader::ReadInt16()
	{
		if (m_DataLength < 2)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		if (m_ReadOffset + 2 > m_FixedBlockSize)
		{
			uint16_t v1 = ReadByte();
			uint16_t v2 = ReadByte();

			return (uint16_t)((v2 << 8) | v1);
		}

		uint16_t v = Marshal::ReadInt16(m_CurBlock, m_ReadOffset);

		m_ReadOffset += 2;
		m_DataLength -= 2;

		if (m_ReadOffset >= m_FixedBlockSize)
		{
			m_CurBlock = m_Allocator->GetNextBlock(m_CurBlock);
			m_ReadOffset = 0;
		}

		return v;
	}

	uint32_t StormMessageHeaderReader::ReadInt32()
	{
		if (m_DataLength < 4)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		if (m_ReadOffset + 4 > m_FixedBlockSize)
		{
			uint32_t v1 = ReadInt16();
			uint32_t v2 = ReadInt16();

			return (uint32_t)((v2 << 16) | v1);
		}

		uint32_t v = Marshal::ReadInt32(m_CurBlock, m_ReadOffset);

		m_ReadOffset += 4;
		m_DataLength -= 4;

		if (m_ReadOffset >= m_FixedBlockSize)
		{
			m_CurBlock = m_Allocator->GetNextBlock(m_CurBlock);
			m_ReadOffset = 0;
		}

		return v;
	}


	uint64_t StormMessageHeaderReader::ReadInt64()
	{
		if (m_DataLength < 8)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		if (m_ReadOffset + 8 > m_FixedBlockSize)
		{
			uint64_t v1 = ReadInt32();
			uint64_t v2 = ReadInt32();

			return (uint64_t)((v2 << 32) | v1);
		}

		uint64_t v = Marshal::ReadInt64(m_CurBlock, m_ReadOffset);

		m_ReadOffset += 8;
		m_DataLength -= 8;

		if (m_ReadOffset >= m_FixedBlockSize)
		{
			m_CurBlock = m_Allocator->GetNextBlock(m_CurBlock);
			m_ReadOffset = 0;
		}

		return v;
	}

	int StormMessageHeaderReader::AdvanceToNextHeader(int & full_data_length)
	{
		int num_read = 0;
		full_data_length = 0;
		while (m_DataLength > 0)
		{
			char v = ReadByte();
			full_data_length++;

			if (v == '\n')
			{
				return num_read;
			}

			if (v != '\r')
			{
				num_read++;
			}
		}

		return -1;
	}

	void StormMessageHeaderReader::Advance(int num_bytes)
	{
		if (m_DataLength < num_bytes)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		m_ReadOffset += num_bytes;
		m_DataLength -= num_bytes;

		while (m_ReadOffset >= m_FixedBlockSize)
		{
			m_CurBlock = m_Allocator->GetNextBlock(m_CurBlock);
			m_ReadOffset -= m_FixedBlockSize;
		}
	}
}