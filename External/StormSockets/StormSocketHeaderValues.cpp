
#include "StormSocketHeaderValues.h"

namespace StormSockets
{
	void StormMessageHeaderValues::Init(const char * protocol)
	{
		std::vector<std::string> strs;

		strs.push_back("GET / HTTP/1.1");
		strs.push_back("upgrade: websocket");
		strs.push_back("connection: ");
		strs.push_back("upgrade");
		strs.push_back("sec-websocket-key: ");
		strs.push_back("sec-websocket-version: 13");

		if (protocol != NULL)
		{
			strs.push_back(std::string("sec-webSocket-protocol: ") + std::string(protocol));
			strs.push_back(std::string("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Protocol: ") +
					        std::string(protocol) + std::string("\r\nSec-WebSocket-Accept: "));
		}
		else
		{
			strs.push_back("sec-websocket-protocol: ");
			strs.push_back("HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ");
		}

		strs.push_back("\r\n\r\n");

		if (strs.size() != (int)StormMessageHeaderType::Count)
		{
			throw std::runtime_error("error: header matcher array is inconsistent");
		}

		for (int index = 0; index < StormMessageHeaderType::Count; index++)
		{
			int len = (strs[index].length());
			m_DataMatch[index].m_Data = strs[index];
			m_DataMatch[index].m_InitialVal = *((int *)strs[index].c_str());
		}
	}

	bool StormMessageHeaderValues::Match(StormMessageHeaderReader & reader, int initial_value, StormMessageHeaderType::Index type)
	{
		if (reader.m_DataLength + 4 < (int)m_DataMatch[(int)type].m_Data.length())
		{
			return false;
		}

		int check_val = m_DataMatch[(int)type].m_InitialVal;
		if (initial_value != check_val)
		{
			return false;
		}

		int check_start = 4;
		int check_end = m_DataMatch[(int)type].m_Data.length();

		for (int index = check_start; index < check_end; index++)
		{
			// Lower case it
			uint8_t b = reader.ReadByte();
			if (b >= 'A' && b <= 'Z')
			{
				b += 'a' - 'A';
			}

			if (b != m_DataMatch[(int)type].m_Data[index])
			{
				return false;
			}
		}

		return true;
	}

	bool StormMessageHeaderValues::MatchExact(StormMessageHeaderReader & reader, int initial_value, int header_len, StormMessageHeaderType::Index type)
	{
		if (header_len != m_DataMatch[(int)type].m_Data.length())
		{
			return false;
		}

		int check_val = m_DataMatch[(int)type].m_InitialVal;
		if ((initial_value) != check_val)
		{
			return false;
		}

		int check_start = 4;
		int check_end = m_DataMatch[(int)type].m_Data.length();

		for (int index = check_start; index < check_end; index++)
		{
			// Lower case it
			uint8_t b = reader.ReadByte();
			if (b >= 'A' && b <= 'Z')
			{
				b += 'a' - 'A';
			}

			if (b != m_DataMatch[(int)type].m_Data[index])
			{
				return false;
			}
		}

		return true;
	}

	bool StormMessageHeaderValues::MatchExactCaseSensitive(StormMessageHeaderReader & reader, int initial_value, int header_len, StormMessageHeaderType::Index type)
	{
		if (header_len != m_DataMatch[(int)type].m_Data.length())
		{
			return false;
		}

		int check_val = m_DataMatch[(int)type].m_InitialVal;
		if ((initial_value) != check_val)
		{
			return false;
		}

		int check_start = 4;
		int check_end = m_DataMatch[(int)type].m_Data.length();

		for (int index = check_start; index < check_end; index++)
		{
			if (reader.ReadByte() != m_DataMatch[(int)type].m_Data[index])
			{
				return false;
			}
		}

		return true;
	}

	bool StormMessageHeaderValues::FindCSLValue(StormMessageHeaderReader & reader, StormMessageHeaderType::Index type)
	{
		while (reader.m_DataLength > 0)
		{
			int check_start = 0;
			int check_end = m_DataMatch[(int)type].m_Data.length();

			bool matched = true;
			for (int index = check_start; index < check_end; index++)
			{
				// Lower case it
				uint8_t b = reader.ReadByte();
				if (b >= 'A' && b <= 'Z')
				{
					b += 'a' - 'A';
				}

				if (b != m_DataMatch[(int)type].m_Data[index])
				{
					matched = false;
					break;
				}
			}

			if (matched)
			{
				if (reader.m_DataLength == 0 || reader.ReadByte() == (uint8_t)',')
				{
					return true;
				}
			}

			// Find the next comma
			while (reader.m_DataLength > 0 && reader.ReadByte() != (uint8_t)',')
			{

			}

			// Skip the whitespace
			if (reader.m_DataLength == 0 || reader.ReadByte() != (uint8_t)' ')
			{
				return false;
			}
		}

		return false;
	}

	void StormMessageHeaderValues::WriteHeader(StormMessageWriter & writer, StormMessageHeaderType::Index type)
	{
		writer.WriteByteBlock(m_DataMatch[(int)type].m_Data.c_str(), 0, m_DataMatch[(int)type].m_Data.length());
	}
}