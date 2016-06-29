
#include "StormSocketServerConnectionId.h"

namespace StormSockets
{
	StormSocketServerConnectionId StormSocketServerConnectionId::InvalidConnectionId = StormSocketServerConnectionId(-1, 0);

	StormSocketServerConnectionId::StormSocketServerConnectionId()
	{
		m_Index.Raw = 0;
	}

	StormSocketServerConnectionId::StormSocketServerConnectionId(int index, int gen)
	{
		m_Index = StormGenIndex(index, gen);
	}

	StormSocketServerConnectionId::operator int()
	{
		return m_Index.GetIndex();
	}
}
