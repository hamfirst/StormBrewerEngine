
#pragma once

#include <stdint.h>
#include <atomic>

namespace StormSockets
{
	namespace ProfilerCategory
	{
		enum Index
		{
			kWriteByte,
			kReadByte,
			kSend,
			kEnqueue,
			kAllocArraySlot,
			kReleaseArraySlot,
			kPacketCopy,
			kCreatePacket,
			kFinalizePacket,
			kPrepRecv,
			kProcData,
			kCount,
		};
	}

	class Profiling
	{

	public:
		static uint64_t StartProfiler();
		static void EndProfiler(uint64_t start_val, ProfilerCategory::Index category);

		static void Print();
	};
}
