
#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <exception>

#include <StormSockets\StormMessageHeaderReader.h>
#include <StormSockets\StormMessageWriter.h>

namespace StormSockets
{
	struct StormMessageHeaderValueMatch
	{
		int m_InitialVal;
		std::string m_Data;
	};

	namespace StormMessageHeaderType
	{
		enum Index
		{
			GetHeader,
			WebsocketHeader,
			ConnectionUpdgradeHeader,
			UpdgradePart,
			WebsocketKeyHeader,
			WebsocketVerHeader,
			WebsocketProtoHeader,
			Response,
			ResponseTerminator,
			Count,
		};
	}

	struct StormMessageHeaderValues
	{
		StormMessageHeaderValueMatch m_DataMatch[StormMessageHeaderType::Count];

		void Init(const char * protocol);

		bool Match(StormMessageHeaderReader & reader, int initial_value, StormMessageHeaderType::Index type);
		bool MatchExact(StormMessageHeaderReader & reader, int initial_value, int header_len, StormMessageHeaderType::Index type);
		bool MatchExactCaseSensitive(StormMessageHeaderReader & reader, int initial_value, int header_len, StormMessageHeaderType::Index type);

		bool FindCSLValue(StormMessageHeaderReader & reader, StormMessageHeaderType::Index type);

		void WriteHeader(StormMessageWriter & writer, StormMessageHeaderType::Index type);
	};
}
