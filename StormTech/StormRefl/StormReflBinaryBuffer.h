
#pragma once

#include <cstring>

#include "StormReflBinaryType.h"

template <int StaticSize = 128>
struct StormReflBinaryBuffer
{
public:
	StormReflBinaryBuffer()
	{

	}

	StormReflBinaryBuffer(const StormReflBinaryBuffer & rhs)
	{
		if (rhs.m_Length <= StaticSize)
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], rhs.m_Length);
		}
		else
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], StaticSize);
			m_DynamicBuffer = malloc(rhs.m_Capacity - StaticSize);
			memcpy(m_DynamicBuffer, rhs.m_DynamicBuffer, rhs.m_Length - StaticSize);
		}

		m_Length = rhs.m_Length;
		m_Capacity = rhs.m_Capacity;
	}

	StormReflBinaryBuffer(StormReflBinaryBuffer && rhs)
	{
		if (rhs.m_Length <= StaticSize)
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], rhs.m_Length);
		}
		else
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], StaticSize);
			m_DynamicBuffer = rhs.m_DynamicBuffer;
			rhs.m_DynamicBuffer = nullptr;
		}

		m_Length = rhs.m_Length;
		m_Capacity = rhs.m_Capacity;

		rhs.m_Length = 0;
		rhs.m_Capacity = StaticSize;
	}

	~StormReflBinaryBuffer()
	{
		if (m_DynamicBuffer)
		{
			free(m_DynamicBuffer);
		}
	}

	StormReflBinaryBuffer & operator =(const StormReflBinaryBuffer & rhs)
	{
		if (m_DynamicBuffer)
		{
			free(m_DynamicBuffer);
			m_DynamicBuffer = nullptr;
		}

		if (rhs.m_Length <= StaticSize)
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], rhs.m_Length);
		}
		else
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], StaticSize);
			m_DynamicBuffer = static_cast<unsigned char *>(malloc(rhs.m_Capacity - StaticSize));
			memcpy(m_DynamicBuffer, rhs.m_DynamicBuffer, rhs.m_Length - StaticSize);
		}

		m_Length = rhs.m_Length;
		m_Capacity = rhs.m_Capacity;
	}

	StormReflBinaryBuffer & operator =(StormReflBinaryBuffer && rhs)
	{
		if (m_DynamicBuffer)
		{
			free(m_DynamicBuffer);
			m_DynamicBuffer = nullptr;
		}

		if (rhs.m_Length <= StaticSize)
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], rhs.m_Length);
		}
		else
		{
			memcpy(&m_StaticBuffer[0], &rhs.m_StaticBuffer[0], StaticSize);
			m_DynamicBuffer = rhs.m_DynamicBuffer;
			rhs.m_DynamicBuffer = nullptr;
		}

		m_Length = rhs.m_Length;
		m_Capacity = rhs.m_Capacity;

		rhs.m_Length = 0;
		rhs.m_Capacity = StaticSize;
	}

	void WriteBlock(void * data, int length)
	{
		if (m_Length + length <= m_Capacity)
		{
			if (m_DynamicBuffer)
			{
				memcpy(&m_DynamicBuffer[m_Length - StaticSize], data, length);
			}
			else
			{
				memcpy(&m_StaticBuffer[m_Length], data, length);
			}
		}
		else
		{
			if (m_DynamicBuffer == nullptr)
			{
				int leftover_amount = m_Capacity - m_Length;
				memcpy(&m_StaticBuffer[m_Length], data, leftover_amount);

				unsigned char * new_src = static_cast<unsigned char *>(data) + leftover_amount;
				length -= leftover_amount;

				m_DynamicBuffer = malloc(m_Capacity);
				m_Capacity *= m_Capacity;

				memcpy(&m_DynamicBuffer[0], new_src, length);
			}
			else
			{
				int new_capacity = m_Capacity * 2;
				m_DynamicBuffer = realloc(m_DynamicBuffer, new_capacity);

				memcpy(&m_DynamicBuffer[m_Length - StaticSize], data, length);
			}
		}

		m_Length += length;
	}

	void WriteType(StormReflBinaryType type)
	{
		WriteInt8(static_cast<int8_t>(type));
	}

	void WriteInt8(int8_t val)
	{
		WriteBlock(&val, 1);
	}

	void WriteInt16(int16_t val)
	{
		WriteBlock(&val, 2);
	}

	void WriteInt32(int32_t val)
	{
		WriteBlock(&val, 4);
	}

	void WriteInt64(int64_t val)
	{
		WriteBlock(&val, 8);
	}

	void WriteUInt8(uint8_t val)
	{
		WriteBlock(&val, 1);
	}

	void WriteUInt16(uint16_t val)
	{
		WriteBlock(&val, 2);
	}

	void WriteUInt32(uint32_t val)
	{
		WriteBlock(&val, 4);
	}

	void WriteUInt64(uint64_t val)
	{
		WriteBlock(&val, 8);
	}

	void WriteFloat32(float val)
	{
		WriteBlock(&val, 4);
	}

	void WriteFloat64(double val)
	{
		WriteBlock(&val, 8);
	}

private:
	unsigned int m_Length = 0;
	unsigned int m_Capacity = StaticSize;

	unsigned char m_StaticBuffer[StaticSize];
	unsigned char * m_DynamicBuffer = nullptr;

};



