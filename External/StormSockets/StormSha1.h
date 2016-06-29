#pragma once

#include <stdint.h>
#include <exception>

#include <StormSockets\StormMessageHeaderReader.h>
#include <StormSockets\StormMessageWriter.h>

namespace StormSockets
{
	class StormSha1
	{
	public:
		static void CalcHash(StormMessageHeaderReader header_reader, StormMessageWriter & writer);
	};
}
