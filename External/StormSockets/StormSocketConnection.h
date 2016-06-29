#pragma once

#include <StormSockets\StormFixedBlockAllocator.h>
#include <StormSockets\StormSocketBuffer.h>
#include <StormSockets\StormMessageWriter.h>
#include <StormSockets\StormMessageReader.h>

#ifdef USE_WINSEC
#include <Windows.h>
#include <sspi.h>
#endif

#ifdef USE_MBED
#include <mbedtls\ssl.h>
#endif

namespace StormSockets
{
	namespace StormSocketDisconnectFlags
	{
		enum Index
		{
			kMainThread = 0x01,
			kRecvThread = 0x02,
			kSendThread = 0x04,
			kLocalClose = 0x08,
			kRemoteClose = 0x10,
			kThreadClose = 0x20,
			kAllFlags = kMainThread | kRecvThread | kSendThread | kLocalClose | kRemoteClose | kThreadClose,
			kCloseFlags = kRemoteClose | kLocalClose,
			kSocket = 0x40,
			kSignalClose = 0x80,
		};
	}

	namespace StormSocketServerConnectionState
	{
		enum Index
		{
			HandShake,
			SendHandshakeResponse,
			ReadHeaderAndApplyMask,
			HandleContinuations,
			HandleIncomingPacket,
			SendPong,
		};
	}

  struct SSLContext
  {
    SSLContext()
    {
      memset(this, 0, sizeof(SSLContext));
    }

#ifdef USE_WINSEC
    SecHandle m_SecHandle;
    unsigned long m_SecAttribs;
    TimeStamp m_SecTimestamp;
    SecPkgContext_StreamSizes m_StreamSizes;
#endif

#ifdef USE_MBED
    mbedtls_ssl_context m_SSLContext;
#endif

    bool m_SecHandleInitialized;
    bool m_SSLHandshakeComplete;
  };

	struct StormSocketServerConnection
	{
		volatile int m_Socket;
		StormSocketServerConnectionState::Index m_State;

		unsigned int m_RemoteIP;
		unsigned short m_RemotePort;

    StormSocketBuffer m_RecvBuffer;
    StormSocketBuffer m_DecryptBuffer;
		StormFixedBlockHandle m_ParseBlock;
		StormFixedBlockHandle m_PendingSendBlock;
		std::atomic_int m_UnparsedDataLength;
		int m_ParseOffset;
		int m_ReadOffset;
		int m_DisconnectFlags;
		std::atomic_int m_PendingPackets;
		int m_SlotGen;
		int m_PendingRemainingData;
		int m_PendingFreeData;
		std::atomic_int m_RecvCriticalSection;

    SSLContext m_SSLContext;

		StormMessageWriter m_PendingWriter;

#ifdef USE_MBED
    StormMessageWriter m_EncryptWriter;
#endif

		bool m_ReaderValid;
		bool m_InContinuation;
		StormMessageReader m_InitialReader;
		StormMessageReader m_LastReader;
		StormMessageReader m_PendingReader;
		int m_PendingReaderFullPacketLen;

		std::atomic_int m_PacketsSent;
		std::atomic_int m_PacketsRecved;

		bool m_GotGetHeader;
		bool m_GotWebsocketHeader;
		bool m_GotConnectionUpgradeHeader;
		bool m_GotWebsocketKeyHeader;
		bool m_GotWebsocketVerHeader;
		bool m_GotWebsocketProtoHeader;
		bool m_GotHeaderTerminator;

		volatile bool m_FailedConnection;
	};
}