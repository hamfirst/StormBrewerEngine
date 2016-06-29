
#pragma once

#include <thread>

#include <StormSockets\StormFixedBlockAllocator.h>
#include <StormSockets\StormMessageQueue.h>
#include <StormSockets\StormSemaphore.h>
#include <StormSockets\StormSocketConnection.h>
#include <StormSockets\StormMessageHeaderReader.h>
#include <StormSockets\StormSocketHeaderValues.h>
#include <StormSockets\StormSocketServerConnectionId.h>
#include <StormSockets\StormMessageWriter.h>
#include <StormSockets\StormMessageReader.h>
#include <StormSockets\StormSha1.h>
#include <StormSockets\StormSocketServerTypes.h>


namespace StormSockets
{
	namespace StormSocketIOOperationType
	{
		enum Index
		{
			SendPacket,
			FreePacket,
			ClearQueue,
			Close,
		};
	}

	struct StormSocketIOOperation
	{
		StormSocketIOOperationType::Index m_Type;
		StormSocketServerConnectionId m_ConnectionId;
		int m_Size;
	};

	struct StormSocketFreeQueueElement
	{
		StormMessageWriter m_Writer;
	};


	class StormSocketServerBase
	{
	protected:
		// Allocator for send and recv buffers.  These buffers interact directly with the low level api
		StormFixedBlockAllocator m_Allocator;

		// Signals all threads to shutdown when set to true
		volatile bool m_ThreadStopRequested;

		// How big our send/recv blocks are
		int m_FixedBlockSize;

		// Allocator for message senders.  These store data about packets as they are being built by external code
		StormFixedBlockAllocator m_MessageSenders;

		// Allocator for message readers.  These store data about packets as they are being read by external code
		StormFixedBlockAllocator m_MessageReaders;

		// Output queue that stores packets waiting to be sent on a per connection basis.
		int m_MaxConnections;
		std::unique_ptr<StormSocketServerConnection[]> m_Connections;
		std::unique_ptr<StormMessageMegaQueue<StormMessageWriter>[]> m_OutputQueue;
    std::unique_ptr<StormMessageMegaContainer<StormMessageWriter>[]> m_OutputQueueArray;
    std::unique_ptr<StormGenIndex[]> m_OutputQueueIncdices;

		// Queue that stores which connections have pending data.  Each send thread has its own queue
		int m_NumSendThreads;
		int m_NumIOThreads;
    std::unique_ptr<StormMessageMegaQueue<StormSocketIOOperation>[]> m_SendQueue;
    std::unique_ptr<StormMessageMegaContainer<StormSocketIOOperation>[]> m_SendQueueArray;
    std::unique_ptr<StormGenIndex[]> m_SendQueueIncdices;
    std::unique_ptr<StormSemaphore[]> m_SendThreadSemaphores;

		// Queue that stores packets waiting to be freed
    std::unique_ptr<StormMessageMegaQueue<StormSocketFreeQueueElement>[]> m_FreeQueue;
    std::unique_ptr<StormMessageMegaContainer<StormSocketFreeQueueElement>[]> m_FreeQueueArray;
    std::unique_ptr<StormGenIndex[]> m_FreeQueueIncdices;
		int m_MaxPendingFrees;

		// Queue that stores event data which is consumed by external code.  Events tell the user there was a connect or disconnect or new packet
		StormMessageQueue<StormSocketEventInfo> m_EventQueue;

		// Queue that stores which connections need to be closed
		StormMessageQueue<StormSocketServerConnectionId> m_ClosingConnectionQueue;
		std::thread m_CloseConnectionThread;
		StormSemaphore m_CloseConnectionSemaphore;

		// Data for processing and writing out headers
		StormMessageHeaderValues m_HeaderValues;
		bool m_HasProtocol;
		bool m_UseMasking;
    bool m_UseSSL;
		StormSocketContinuationMode::Index m_ContinuationMode;

		static const int InvalidSocketId = -1;

	public:
    StormSocketServerBase(StormSocketInitSettings & settings);
		~StormSocketServerBase();

		virtual void Start();

		bool GetEvent(StormSocketEventInfo & message);

		StormMessageWriter CreateOutgoingPacket(StormSocketDataType::Index type, bool final);

		void FinalizeOutgoingPacket(StormMessageWriter & writer);

		bool SendPacketToConnection(StormMessageWriter & writer, StormSocketServerConnectionId id);

		void SendPacketToConnectionBlocking(StormMessageWriter & writer, StormSocketServerConnectionId id);

		void FreeOutgoingPacket(StormMessageWriter & writer);


		void FreeIncomingPacket(StormMessageReader & reader);

		void FinalizeConnection(StormSocketServerConnectionId id);

		void ForceDisconnect(StormSocketServerConnectionId id);

	protected:
		StormSocketServerConnectionId AllocateConnection(int socket, uint32_t remote_ip, uint16_t remote_port);

		bool ProcessData(StormSocketServerConnectionId connection_id);

		void DiscardParserData(StormSocketServerConnectionId connection_id, int amount);

		void DiscardReaderData(StormSocketServerConnectionId connection_id, int amount);

		bool ReservePacketSlot(StormSocketServerConnectionId id);
		void ReleasePacketSlot(StormSocketServerConnectionId id);

		virtual StormMessageWriter CreateWriterInternal();

		StormMessageWriter CreateOutgoingPacket(StormWebsocketOp::Index mode, bool final);

		void ReleaseOutgoingPacket(StormMessageWriter & writer);
		void SignalOutgoingSocket(StormSocketServerConnectionId id, StormSocketIOOperationType::Index type, int size = 0);
		void SetSocketDisconnected(StormSocketServerConnectionId id);

		virtual void CloseSocket(StormSocketServerConnectionId id);
    virtual void FreeConnectionResources(StormSocketServerConnectionId id);

		void CloseSocketThread();

		void SignalCloseThread(StormSocketServerConnectionId id);
		void SetDisconnectFlag(StormSocketServerConnectionId id, StormSocketDisconnectFlags::Index flags);
		bool CheckDisconnectFlags(StormSocketServerConnectionId id, StormSocketDisconnectFlags::Index new_flags);
	};
}