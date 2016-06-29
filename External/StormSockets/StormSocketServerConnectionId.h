
#pragma once

#include <StormSockets\StormGenIndex.h>

namespace StormSockets
{
	struct StormSocketServerConnectionId
	{
		StormGenIndex m_Index;

		StormSocketServerConnectionId();
		StormSocketServerConnectionId(int index, int gen);

		operator int();

		static StormSocketServerConnectionId InvalidConnectionId;

		int GetIndex() { return m_Index.GetIndex(); }
		int GetGen() { return m_Index.GetGen(); }
	};
}