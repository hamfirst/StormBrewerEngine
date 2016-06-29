
#include "StormSocketServerBase.h"

namespace StormSockets
{
	StormSocketServerBase::StormSocketServerBase(StormSocketInitSettings & settings) :
		m_Allocator(settings.HeapSize, settings.BlockSize, true),
		m_MessageReaders(settings.MaxPendingOutgoingPacketsPerConnection * sizeof(StormMessageReaderData) * settings.MaxConnections, sizeof(StormMessageReaderData), false),
		m_MessageSenders(settings.MaxPendingOutgoingPacketsPerConnection * sizeof(StormMessageWriterData) * settings.MaxConnections, sizeof(StormMessageWriterData), false),
		m_EventQueue(settings.MessageQueueSize),
		m_ClosingConnectionQueue(settings.MaxConnections)
	{
		m_MaxConnections = settings.MaxConnections;
		m_Connections = std::make_unique<StormSocketServerConnection[]>(settings.MaxConnections);

		for (int index = 0; index < settings.MaxConnections; index++)
		{
			m_Connections[index].m_Socket = InvalidSocketId;
			m_Connections[index].m_SlotGen = 0;
		}

		m_OutputQueue = std::make_unique<StormMessageMegaQueue<StormMessageWriter>[]>(settings.MaxConnections);
		m_OutputQueueArray = std::make_unique<StormMessageMegaContainer<StormMessageWriter>[]>(settings.MaxConnections * settings.MaxPendingOutgoingPacketsPerConnection);
		m_OutputQueueIncdices = std::make_unique<StormGenIndex[]>(settings.MaxConnections * settings.MaxPendingOutgoingPacketsPerConnection);

		m_FreeQueue = std::make_unique<StormMessageMegaQueue<StormSocketFreeQueueElement>[]>(settings.MaxConnections);
		m_FreeQueueArray = std::make_unique<StormMessageMegaContainer<StormSocketFreeQueueElement>[]>(settings.MaxConnections * settings.MaxPendingFreeingPacketsPerConnection * 2);
		m_FreeQueueIncdices = std::make_unique<StormGenIndex[]>(settings.MaxConnections * settings.MaxPendingFreeingPacketsPerConnection * 2);
		m_MaxPendingFrees = settings.MaxPendingFreeingPacketsPerConnection * 2;

		m_FixedBlockSize = settings.BlockSize;

		for (int index = 0; index < settings.MaxConnections; index++)
		{
			m_OutputQueue[index].Init(m_OutputQueueIncdices.get(), m_OutputQueueArray.get(),
				index * settings.MaxPendingOutgoingPacketsPerConnection, settings.MaxPendingOutgoingPacketsPerConnection);

			m_FreeQueue[index].Init(m_FreeQueueIncdices.get(), m_FreeQueueArray.get(),
				index * settings.MaxPendingFreeingPacketsPerConnection * 2, settings.MaxPendingFreeingPacketsPerConnection * 2);

			m_Connections[index].m_Socket = InvalidSocketId;
		}

		m_NumSendThreads = settings.NumSendThreads;
		m_NumIOThreads = settings.NumIOThreads;
		m_SendThreadSemaphores = std::make_unique<StormSemaphore[]>(settings.NumSendThreads);
		m_SendQueue = std::make_unique<StormMessageMegaQueue<StormSocketIOOperation>[]>(settings.NumSendThreads);
		m_SendQueueArray = std::make_unique<StormMessageMegaContainer<StormSocketIOOperation>[]>(settings.NumSendThreads * settings.MaxSendQueueElements);
		m_SendQueueIncdices = std::make_unique<StormGenIndex[]>(settings.NumSendThreads * settings.MaxSendQueueElements);

		for (int index = 0; index < settings.NumSendThreads; index++)
		{
			m_SendQueue[index].Init(m_SendQueueIncdices.get(), m_SendQueueArray.get(),
				index * settings.MaxSendQueueElements, settings.MaxSendQueueElements);

			int semaphore_max = settings.MaxSendQueueElements + (settings.MaxConnections * settings.MaxPendingFreeingPacketsPerConnection) / settings.NumSendThreads;
			m_SendThreadSemaphores[index].Init(semaphore_max * 2);
		}

		m_CloseConnectionSemaphore.Init(settings.MaxConnections);
		m_CloseConnectionThread = std::thread(&StormSocketServerBase::CloseSocketThread, this);

		m_HeaderValues.Init(settings.Protocol);
		m_HasProtocol = settings.Protocol != NULL;
		m_UseMasking = settings.UseMasking;
		m_ContinuationMode = settings.ContinuationMode;
	}

	StormSocketServerBase::~StormSocketServerBase()
	{
		m_ThreadStopRequested = true;
		m_CloseConnectionSemaphore.Release();
		m_CloseConnectionThread.join();

		for (int index = 0; index < m_MaxConnections; index++)
		{
			if (m_Connections[index].m_Socket != InvalidSocketId)
			{
        FreeConnectionResources(StormSocketServerConnectionId(index, m_Connections[index].m_SlotGen));
			}
		}
	}

	void StormSocketServerBase::Start()
	{
	}

	bool StormSocketServerBase::GetEvent(StormSocketEventInfo & message)
	{
		if (m_EventQueue.TryDequeue(message))
		{
			return true;
		}

		return false;
	}

	StormMessageWriter StormSocketServerBase::CreateOutgoingPacket(StormSocketDataType::Index type, bool final)
	{
		StormWebsocketOp::Index mode;
		switch (type)
		{
		case StormSocketDataType::Binary:
		default:
			mode = StormWebsocketOp::BinaryFrame;
			break;
		case StormSocketDataType::Text:
			mode = StormWebsocketOp::TextFrame;
			break;
		case StormSocketDataType::Ping:
			mode = StormWebsocketOp::Ping;
			break;
		case StormSocketDataType::Pong:
			throw std::runtime_error("not supported"); // Users cannot create Pong messages, they are created automatically in response to a ping
		case StormSocketDataType::Continuation:
			mode = StormWebsocketOp::Continuation;
			break;
		}

		return CreateOutgoingPacket(mode, final);
	}

	void StormSocketServerBase::FinalizeOutgoingPacket(StormMessageWriter & writer)
	{
		uint64_t prof = Profiling::StartProfiler();
		writer.CreateHeaderAndApplyMask((int)writer.m_Mode, writer.m_Final, m_UseMasking ? rand() : 0);
		Profiling::EndProfiler(prof, ProfilerCategory::kFinalizePacket);
	}

	bool StormSocketServerBase::SendPacketToConnection(StormMessageWriter & writer, StormSocketServerConnectionId id)
	{
		if (writer.m_PacketInfo->m_TotalLength == 0)
		{
			return false;
		}

		if (m_Connections[id].m_SlotGen != id.GetGen())
		{
			return false;
		}

		if (!ReservePacketSlot(id))
		{
			return false;
		}

		writer.m_PacketInfo->m_RefCount.fetch_add(1);
		if (m_OutputQueue[id].Enqueue(writer, id.GetGen(), m_OutputQueueIncdices.get(), m_OutputQueueArray.get()) == false)
		{
			ReleasePacketSlot(id);
			writer.m_PacketInfo->m_RefCount.fetch_sub(1);
			return false;
		}

		m_Connections[id].m_PacketsSent.fetch_add(1);
		SignalOutgoingSocket(id, StormSocketIOOperationType::SendPacket);
		return true;
	}

	void StormSocketServerBase::SendPacketToConnectionBlocking(StormMessageWriter & writer, StormSocketServerConnectionId id)
	{
		while (!ReservePacketSlot(id))
		{
			std::this_thread::yield();
		}

		writer.m_PacketInfo->m_RefCount.fetch_add(1);
		while (m_OutputQueue[id].Enqueue(writer, id.GetGen(), m_OutputQueueIncdices.get(), m_OutputQueueArray.get()) == false)
		{
			if (m_Connections[id].m_SlotGen != id.GetGen())
			{
				ReleasePacketSlot(id);
				writer.m_PacketInfo->m_RefCount.fetch_sub(1);
				return;
			}

			if (m_Connections[id].m_DisconnectFlags != 0)
			{
				ReleasePacketSlot(id);
				writer.m_PacketInfo->m_RefCount.fetch_sub(1);
				return;
			}

			std::this_thread::yield();
		}

		SignalOutgoingSocket(id, StormSocketIOOperationType::SendPacket);
	}

	void StormSocketServerBase::FreeOutgoingPacket(StormMessageWriter & writer)
	{
		if (writer.m_PacketInfo->m_RefCount.fetch_sub(1) == 1)
		{
			ReleaseOutgoingPacket(writer);
		}
	}


	void StormSocketServerBase::FreeIncomingPacket(StormMessageReader & reader)
	{
		reader.FreeChain();
		DiscardReaderData(reader.m_ConnectionId, reader.m_PacketDataLen);
	}

	void StormSocketServerBase::FinalizeConnection(StormSocketServerConnectionId id)
	{
		SetDisconnectFlag(id, StormSocketDisconnectFlags::kMainThread);
	}

	void StormSocketServerBase::ForceDisconnect(StormSocketServerConnectionId id)
	{
		SetDisconnectFlag(id, StormSocketDisconnectFlags::kLocalClose);
	}

	StormSocketServerConnectionId StormSocketServerBase::AllocateConnection(int socket, uint32_t remote_ip, uint16_t remote_port)
	{
		for (int index = 0; index < m_MaxConnections; index++)
		{
			int inv_socket = InvalidSocketId;
			if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Connections[index].m_Socket, &inv_socket, socket))
			{
				// Set up the connection
				m_Connections[index].m_Socket = socket;
        m_Connections[index].m_State = StormSocketServerConnectionState::HandShake;
        m_Connections[index].m_DecryptBuffer = StormSocketBuffer(&m_Allocator, m_FixedBlockSize);
        m_Connections[index].m_RecvBuffer = StormSocketBuffer(&m_Allocator, m_FixedBlockSize);
				m_Connections[index].m_ParseBlock = InvalidBlockHandle;
				m_Connections[index].m_PendingSendBlock = InvalidBlockHandle;
				m_Connections[index].m_UnparsedDataLength = 0;
				m_Connections[index].m_ParseOffset = 0;
				m_Connections[index].m_ReadOffset = 0;
				m_Connections[index].m_RemoteIP = remote_ip;
				m_Connections[index].m_RemotePort = remote_port;
				m_Connections[index].m_PendingPackets = 0;
				m_Connections[index].m_PendingRemainingData = 0;
				m_Connections[index].m_PendingFreeData = 0;
				m_Connections[index].m_DisconnectFlags = 0;
        m_Connections[index].m_RecvCriticalSection = 0;

        m_Connections[index].m_SSLContext = SSLContext();

				m_Connections[index].m_ReaderValid = false;
				m_Connections[index].m_InContinuation = false;
				m_Connections[index].m_PendingReaderFullPacketLen = 0;
				m_Connections[index].m_RecvCriticalSection = 0;

				m_Connections[index].m_PacketsRecved = 0;
				m_Connections[index].m_PacketsSent = 0;

				m_Connections[index].m_GotGetHeader = false;
				m_Connections[index].m_GotWebsocketHeader = false;
				m_Connections[index].m_GotConnectionUpgradeHeader = false;
				m_Connections[index].m_GotWebsocketVerHeader = false;
				m_Connections[index].m_GotWebsocketKeyHeader = false;
				m_Connections[index].m_GotWebsocketProtoHeader = false;
				m_Connections[index].m_GotHeaderTerminator = false;

				m_Connections[index].m_FailedConnection = false;

				// Set up the handshake response
				m_Connections[index].m_PendingWriter = CreateWriterInternal();
				m_HeaderValues.WriteHeader(m_Connections[index].m_PendingWriter, StormMessageHeaderType::Response);

#ifdef USE_MBED
        m_Connections[index].m_EncryptWriter = CreateWriterInternal();
        m_Connections[index].m_EncryptWriter.m_Encrypt = false;
#endif

				// Queue up the information about the new connection
				StormSocketEventInfo connect_message;
				connect_message.ConnectionId = StormSocketServerConnectionId(index, m_Connections[index].m_SlotGen);
				connect_message.Type = StormSocketEventType::ClientConnected;
				connect_message.RemoteIP = remote_ip;
				connect_message.RemotePort = remote_port;
				while (m_EventQueue.Enqueue(connect_message) == false)
				{
					std::this_thread::yield();
				}

				return connect_message.ConnectionId;
			}
		}

		return StormSocketServerConnectionId::InvalidConnectionId;
	}

	bool StormSocketServerBase::ProcessData(StormSocketServerConnectionId connection_id)
	{
		while (true)
		{ 
			// If we've already closed the connection, just ignore everything
			if ((m_Connections[connection_id].m_DisconnectFlags & (int)StormSocketDisconnectFlags::kRemoteClose) != 0 ||
				(m_Connections[connection_id].m_DisconnectFlags & (int)StormSocketDisconnectFlags::kSignalClose) != 0 ||
				m_Connections[connection_id].m_FailedConnection)
			{
				DiscardParserData(connection_id, m_Connections[connection_id].m_UnparsedDataLength);
				return true;
			}

			if (m_Connections[connection_id].m_ParseBlock == InvalidBlockHandle)
			{
				m_Connections[connection_id].m_ParseBlock = m_Connections[connection_id].m_RecvBuffer.m_BlockStart;
			}

			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::HandShake)
			{
				StormMessageHeaderReader cur_header;
				cur_header.m_Allocator = &m_Allocator;
				cur_header.m_FixedBlockSize = m_FixedBlockSize;
				cur_header.m_CurBlock = m_Allocator.ResolveHandle(m_Connections[connection_id].m_ParseBlock);
				cur_header.m_DataLength = m_Connections[connection_id].m_UnparsedDataLength;
				cur_header.m_ReadOffset = m_Connections[connection_id].m_ParseOffset;

				StormMessageHeaderReader next_header = cur_header;
				int full_data_len = 0;
				int next_header_len = next_header.AdvanceToNextHeader(full_data_len);

        if (next_header_len == -1)
        {
          return true;
        }

				while (next_header_len != -1)
				{
					// Process header data
					StormMessageHeaderReader processer = cur_header;
					processer.m_DataLength = next_header_len;

					//for (int index = 0; index < next_header_len; index++)
					//{
					//    byte b = cur_header.ReadByte();
					//    Console.Write((char)b);
					//}
					//Console.WriteLine();


					if (next_header_len == 0)
					{
						m_Connections[connection_id].m_GotHeaderTerminator = true;
					}
					else
					{
						int header_val = processer.ReadInt32();
						int header_val_lowercase = 0;

						for (int index = 0; index < 4; index++)
						{
							int b = (header_val >> (index * 8)) & 0xFF;

							// Lower case it
							if (b >= 'A' && b <= 'Z')
							{
								b += 'a' - 'A';
							}

							header_val_lowercase |= b << (index * 8);
						}

						if (m_Connections[connection_id].m_GotGetHeader == false &&
							m_HeaderValues.MatchExactCaseSensitive(processer, header_val, next_header_len, StormMessageHeaderType::GetHeader))
						{
							m_Connections[connection_id].m_GotGetHeader = true;
						}
						else if (m_Connections[connection_id].m_GotWebsocketHeader == false &&
							m_HeaderValues.MatchExact(processer, header_val_lowercase, next_header_len, StormMessageHeaderType::WebsocketHeader))
						{
							m_Connections[connection_id].m_GotWebsocketHeader = true;
						}
						else if (m_Connections[connection_id].m_GotConnectionUpgradeHeader == false &&
							m_HeaderValues.Match(processer, header_val_lowercase, StormMessageHeaderType::ConnectionUpdgradeHeader))
						{
							if (m_HeaderValues.FindCSLValue(processer, StormMessageHeaderType::UpdgradePart))
							{
								m_Connections[connection_id].m_GotConnectionUpgradeHeader = true;
							}
						}
						else if (m_Connections[connection_id].m_GotWebsocketVerHeader == false &&
							m_HeaderValues.MatchExact(processer, header_val_lowercase, next_header_len, StormMessageHeaderType::WebsocketVerHeader))
						{
							m_Connections[connection_id].m_GotWebsocketVerHeader = true;
						}
						else if (m_HasProtocol == false && m_Connections[connection_id].m_GotWebsocketProtoHeader == false &&
							m_HeaderValues.MatchExact(processer, header_val_lowercase, next_header_len, StormMessageHeaderType::WebsocketProtoHeader))
						{
							m_Connections[connection_id].m_GotWebsocketProtoHeader = true;
						}
						else if (m_Connections[connection_id].m_GotWebsocketKeyHeader == false &&
							m_HeaderValues.Match(processer, header_val_lowercase, StormMessageHeaderType::WebsocketKeyHeader))
						{
							StormSha1::CalcHash(processer, m_Connections[connection_id].m_PendingWriter);
							m_Connections[connection_id].m_GotWebsocketKeyHeader = true;
						}
					}

					DiscardReaderData(connection_id, full_data_len);
					DiscardParserData(connection_id, full_data_len);

					if (m_Connections[connection_id].m_GotHeaderTerminator)
					{
						// Check to see if the connection is a valid websocket request
						if (m_Connections[connection_id].m_GotGetHeader &&
							m_Connections[connection_id].m_GotWebsocketHeader &&
							m_Connections[connection_id].m_GotConnectionUpgradeHeader &&
							m_Connections[connection_id].m_GotWebsocketVerHeader &&
							m_Connections[connection_id].m_GotWebsocketKeyHeader &&
							m_Connections[connection_id].m_GotHeaderTerminator &&
							(m_HasProtocol == false || m_Connections[connection_id].m_GotWebsocketProtoHeader))
						{
							m_HeaderValues.WriteHeader(m_Connections[connection_id].m_PendingWriter, StormMessageHeaderType::ResponseTerminator);
							m_Connections[connection_id].m_State = StormSocketServerConnectionState::SendHandshakeResponse;
						}
						else
						{
							ForceDisconnect(connection_id);
						}

						break;
					}

					cur_header = next_header;
					next_header_len = next_header.AdvanceToNextHeader(full_data_len);
				}
			}

			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::SendHandshakeResponse)
			{
				if (SendPacketToConnection(m_Connections[connection_id].m_PendingWriter, connection_id) == false)
				{
					return false;
				}

				m_Connections[connection_id].m_State = StormSocketServerConnectionState::ReadHeaderAndApplyMask;
			}

			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::ReadHeaderAndApplyMask)
			{
				StormMessageHeaderReader cur_header;
				cur_header.m_Allocator = &m_Allocator;
				cur_header.m_FixedBlockSize = m_FixedBlockSize;
				cur_header.m_CurBlock = m_Allocator.ResolveHandle(m_Connections[connection_id].m_ParseBlock);
				cur_header.m_DataLength = m_Connections[connection_id].m_UnparsedDataLength;
				cur_header.m_ReadOffset = m_Connections[connection_id].m_ParseOffset;

				if (cur_header.m_DataLength < 2) // Enough data for a header
				{
					return true;
				}

				uint8_t opdata = cur_header.ReadByte();
				uint8_t len1 = cur_header.ReadByte();
				int header_len = 2;

				if ((opdata & 0x70) != 0) // Reserved bits must be zero
				{
					SignalCloseThread(connection_id);
					return true;
				}

				bool fin = (opdata & 0x80) != 0;
				int opcode = opdata & 0x0F;

				bool mask_enabled = (len1 & 0x80) != 0;

				// Figure out how much data is in the packet
				uint64_t len = len1 & 0x7F;
				if (len == 126)
				{
					if (cur_header.m_DataLength < 2)
					{
						return true;
					}

					uint16_t host_len = cur_header.ReadInt16();
					len = Marshal::HostToNetworkOrder(host_len);
					header_len += 2;
				}
				else if (len == 127)
				{
					if (cur_header.m_DataLength < 8)
					{
						return true;
					}

					len = Marshal::HostToNetworkOrder(cur_header.ReadInt64());
					header_len += 8;
				}

				// Read the mask
				uint32_t mask = 0;
				if (mask_enabled)
				{
					if (cur_header.m_DataLength < 4)
					{
						return true;
					}

					mask = (uint32_t)cur_header.ReadInt32();
					header_len += 4;
				}

				if (cur_header.m_DataLength < len)
				{
					return true;
				}

				// At this point, we have the full packet in memory

				int full_data_len = (int)len + header_len;

				StormSocketDataType::Index data_type = StormSocketDataType::Binary;

				StormWebsocketOp::Index op = (StormWebsocketOp::Index)opcode;
				switch (op)
				{
				case StormWebsocketOp::Continuation:
					if (m_Connections[connection_id].m_InContinuation == false)
					{
						SignalCloseThread(connection_id);
						return true;
					}
					data_type = StormSocketDataType::Continuation;
					break;
				case StormWebsocketOp::BinaryFrame:
					if (m_Connections[connection_id].m_InContinuation == true)
					{
						SignalCloseThread(connection_id);
						return true;
					}
					break;
				case StormWebsocketOp::TextFrame:
					if (m_Connections[connection_id].m_InContinuation == true)
					{
						SignalCloseThread(connection_id);
						return true;
					}

					data_type = StormSocketDataType::Text;
					break;
				case StormWebsocketOp::Pong:
					if (!fin || len > 125)
					{
						SignalCloseThread(connection_id);
						return true;
					}

					data_type = StormSocketDataType::Pong;
					break;
				case StormWebsocketOp::Ping:
					if (!fin || len > 125)
					{
						SignalCloseThread(connection_id);
						return true;
					}

					data_type = StormSocketDataType::Ping;
					break;
				case StormWebsocketOp::Close:
					if (!fin || len > 125)
					{
						SignalCloseThread(connection_id);
						return true;
					}

					SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kRemoteClose);
					SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kLocalClose);
					break;
				default:
					SignalCloseThread(connection_id);
					return true;
				}

				// Create the reader
				StormMessageReader reader;
				StormFixedBlockHandle cur_block_handle = m_Allocator.GetHandleForBlock(cur_header.m_CurBlock);
				reader.Init(&m_Allocator, &m_MessageReaders, cur_block_handle, (int)len, cur_header.m_ReadOffset, connection_id, m_FixedBlockSize);
				reader.m_PacketDataLen = full_data_len;
				reader.m_FullDataLen = (int)len;
				reader.m_DataType = data_type;
				reader.m_FinalInSequence = fin;

				if (mask != 0)
				{
					// Apply the mask
					void * cur_block = cur_header.m_CurBlock;
					int read_offset = cur_header.m_ReadOffset;
					int data_length = (int)len;

					do
					{
						if (data_length >= 4 && read_offset + 4 <= m_FixedBlockSize)
						{
							int val = Marshal::ReadInt32(cur_block, read_offset);
							val ^= (int)mask;

							Marshal::WriteInt32(cur_block, read_offset, val);
							read_offset += 4;
							data_length -= 4;
						}
						else if (data_length > 0 && read_offset != m_FixedBlockSize)
						{
							int val = Marshal::ReadByte(cur_block, read_offset);
							val ^= (int)mask;

							Marshal::WriteByte(cur_block, read_offset, (uint8_t)val);
							read_offset += 1;
							data_length -= 1;

							mask = (mask << 24) | (mask >> 8);
						}

						if (read_offset == m_FixedBlockSize)
						{
							cur_block = m_Allocator.GetNextBlock(cur_block);
							read_offset = 0;
						}
					} while (data_length > 0 && cur_block != NULL);
				}

        if (op == StormWebsocketOp::Close)
        {
          DiscardParserData(connection_id, full_data_len);
          FreeIncomingPacket(reader);
          m_Connections[connection_id].m_State = StormSocketServerConnectionState::ReadHeaderAndApplyMask;
          return true;
        }
				else if (reader.m_DataType == StormSocketDataType::Binary ||
					       reader.m_DataType == StormSocketDataType::Text ||
					       reader.m_DataType == StormSocketDataType::Continuation)
				{
					m_Connections[connection_id].m_InContinuation = !reader.m_FinalInSequence;
				} 

				m_Connections[connection_id].m_PendingReaderFullPacketLen = full_data_len;
				m_Connections[connection_id].m_State = StormSocketServerConnectionState::HandleContinuations;
				m_Connections[connection_id].m_PendingReader = reader;
			}


			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::HandleContinuations)
			{
				// Handle continuations
				StormMessageReader reader = m_Connections[connection_id].m_PendingReader;

				if (reader.m_DataType == StormSocketDataType::Binary ||
					reader.m_DataType == StormSocketDataType::Text ||
					reader.m_DataType == StormSocketDataType::Continuation)
				{
					if (m_Connections[connection_id].m_ReaderValid)
					{
						if (m_ContinuationMode == StormSocketContinuationMode::WaitForCompletion)
						{
							// Send this to the main thread
							StormSocketEventInfo data_message;
							data_message.ConnectionId = connection_id;
							data_message.Type = StormSocketEventType::Data;
							data_message.Reader = m_Connections[connection_id].m_InitialReader;
							data_message.RemoteIP = m_Connections[connection_id].m_RemoteIP;
							data_message.RemotePort = m_Connections[connection_id].m_RemotePort;

							if (m_EventQueue.Enqueue(data_message) == false)
							{
								return false;
							}

							m_Connections[connection_id].m_PacketsRecved.fetch_add(1);
							m_Connections[connection_id].m_InitialReader = reader;
							m_Connections[connection_id].m_LastReader = reader;
						}
						else
						{
							m_Connections[connection_id].m_LastReader.SetNextBlock(reader);
							m_Connections[connection_id].m_LastReader = reader;

							if (m_ContinuationMode == StormSocketContinuationMode::Combine)
							{
								m_Connections[connection_id].m_InitialReader.AddLength(reader.m_FullDataLen);
							}
						}
					}
					else
					{
						m_Connections[connection_id].m_ReaderValid = true;
						m_Connections[connection_id].m_InitialReader = reader;
						m_Connections[connection_id].m_LastReader = reader;
					}
				}

				m_Connections[connection_id].m_State = StormSocketServerConnectionState::HandleIncomingPacket;
			}

			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::HandleIncomingPacket)
			{
				StormMessageReader reader = m_Connections[connection_id].m_PendingReader;
				if (reader.m_DataType == StormSocketDataType::Ping)
				{
					// Reply with a pong
					StormMessageWriter writer = CreateOutgoingPacket(StormWebsocketOp::Pong, true);

					// Copy data from the recv'd message to the output message
					int length = (int)reader.m_FullDataLen;
					while (length > 0)
					{
						if (length >= 4)
						{
							int val = reader.ReadInt32();
							writer.WriteInt32(val);
							length -= 4;
						}
						else
						{
							uint8_t val = reader.ReadByte();
							writer.WriteByte(val);
							length -= 1;
						}
					}

					// Release the reader
					if (m_Connections[connection_id].m_ReaderValid)
					{
						// If we're in the middle of a continuation, this data has to be tagged onto the existing reader
						m_Connections[connection_id].m_InitialReader.m_PacketDataLen += reader.m_PacketDataLen;
						reader.FreeChain();
					}
					else
					{
						FreeIncomingPacket(reader);
					}

					// Send the message
					writer.CreateHeaderAndApplyMask((int)StormWebsocketOp::Pong, true, rand());

					m_Connections[connection_id].m_PendingWriter = writer;
					m_Connections[connection_id].m_State = StormSocketServerConnectionState::SendPong;

					// Advance past this packet to check if another packet is in the buffer
					DiscardParserData(connection_id, m_Connections[connection_id].m_PendingReaderFullPacketLen);
				}
				else if (reader.m_DataType == StormSocketDataType::Pong)
				{
					// Send this to the main thread
					StormSocketEventInfo data_message;
					data_message.ConnectionId = connection_id;
					data_message.Type = StormSocketEventType::Data;
					data_message.Reader = reader;
					data_message.RemoteIP = m_Connections[connection_id].m_RemoteIP;
					data_message.RemotePort = m_Connections[connection_id].m_RemotePort;

					if (m_EventQueue.Enqueue(data_message) == false)
					{
						return false;
					}

					// Advance past this packet to check if another packet is in the buffer
					DiscardParserData(connection_id, m_Connections[connection_id].m_PendingReaderFullPacketLen);
					m_Connections[connection_id].m_State = StormSocketServerConnectionState::ReadHeaderAndApplyMask;
				}
				else
				{
					reader = m_Connections[connection_id].m_InitialReader;
					if (reader.m_FinalInSequence || m_ContinuationMode == StormSocketContinuationMode::DeliverImmediately)
					{
						if (m_ContinuationMode == StormSocketContinuationMode::Combine)
						{
							m_Connections[connection_id].m_InitialReader.m_FinalInSequence = true;
						}

						//Console.WriteLine("Queing up packet of length {0}", reader.m_FullDataLen);

						// Send this to the main thread
						StormSocketEventInfo data_message;
						data_message.ConnectionId = connection_id;
						data_message.Type = StormSocketEventType::Data;
						data_message.Reader = m_Connections[connection_id].m_InitialReader;
						data_message.RemoteIP = m_Connections[connection_id].m_RemoteIP;
						data_message.RemotePort = m_Connections[connection_id].m_RemotePort;


						if (m_EventQueue.Enqueue(data_message) == false)
						{
							return false;
						}

						m_Connections[connection_id].m_PacketsRecved.fetch_add(1);
						m_Connections[connection_id].m_ReaderValid = false;
					}

					DiscardParserData(connection_id, m_Connections[connection_id].m_PendingReaderFullPacketLen);
					m_Connections[connection_id].m_State = StormSocketServerConnectionState::ReadHeaderAndApplyMask;
				}
			}

			if (m_Connections[connection_id].m_State == StormSocketServerConnectionState::SendPong)
			{
				StormMessageWriter writer = m_Connections[connection_id].m_PendingWriter;
				if (SendPacketToConnection(writer, connection_id) == false)
				{
					return false;
				}

				m_Connections[connection_id].m_State = StormSocketServerConnectionState::ReadHeaderAndApplyMask;
			}
		}
	}

	void StormSocketServerBase::DiscardParserData(StormSocketServerConnectionId connection_id, int amount)
	{
		if (m_Connections[connection_id].m_UnparsedDataLength < amount)
		{
			throw std::runtime_error("Read buffer underflow");
		}

		m_Connections[connection_id].m_ParseOffset += amount;
		while (m_Connections[connection_id].m_ParseOffset >= m_FixedBlockSize)
		{
			m_Connections[connection_id].m_ParseBlock = m_Allocator.GetNextBlock(m_Connections[connection_id].m_ParseBlock);
			m_Connections[connection_id].m_ParseOffset -= m_FixedBlockSize;
		}

		m_Connections[connection_id].m_UnparsedDataLength.fetch_sub(amount);
	}

	void StormSocketServerBase::DiscardReaderData(StormSocketServerConnectionId connection_id, int amount)
	{
    m_Connections[connection_id].m_RecvBuffer.DiscardData(amount);
	}

	bool StormSocketServerBase::ReservePacketSlot(StormSocketServerConnectionId id)
	{
		while (true)
		{
			int pending_packets = m_Connections[id].m_PendingPackets;
			if (pending_packets >= m_MaxPendingFrees - 1)
			{
				return false;
			}
			
			if (std::atomic_compare_exchange_weak(&m_Connections[id].m_PendingPackets, &pending_packets, pending_packets + 1))
			{
				return true;
			}
		}
	}

	void StormSocketServerBase::ReleasePacketSlot(StormSocketServerConnectionId id)
	{
		if (id.GetGen() == m_Connections[id].m_SlotGen)
		{
			m_Connections[id].m_PendingPackets.fetch_sub(1);
		}
	}

	StormMessageWriter StormSocketServerBase::CreateWriterInternal()
	{
		uint64_t prof = Profiling::StartProfiler();
		StormMessageWriter writer;
		writer.Init(&m_Allocator, &m_MessageSenders, false, 0, 0);
		Profiling::EndProfiler(prof, ProfilerCategory::kCreatePacket);
		return writer;
	}

	StormMessageWriter StormSocketServerBase::CreateOutgoingPacket(StormWebsocketOp::Index mode, bool final)
	{
		StormMessageWriter writer = CreateWriterInternal();
		writer.SaveHeaderRoom();
		writer.m_Mode = mode;
		writer.m_Final = final;
		return writer;
	}

	void StormSocketServerBase::ReleaseOutgoingPacket(StormMessageWriter & writer)
	{
		StormFixedBlockHandle start_block = writer.m_PacketInfo->m_StartBlock;
		m_Allocator.FreeBlockChain(start_block, StormFixedBlockType::BlockMem);
		m_MessageSenders.FreeBlock(writer.m_PacketHandle, StormFixedBlockType::Sender);
	}

	void StormSocketServerBase::SignalOutgoingSocket(StormSocketServerConnectionId id, StormSocketIOOperationType::Index type, int size)
	{
		int send_thread_index = id % m_NumSendThreads;

		StormSocketIOOperation op;
		op.m_ConnectionId = id;
		op.m_Type = type;
		op.m_Size = size;

		while (m_SendQueue[send_thread_index].Enqueue(op, 0, m_SendQueueIncdices.get(), m_SendQueueArray.get()) == false)
		{
			std::this_thread::yield();
		}

		m_SendThreadSemaphores[send_thread_index].Release();
	}

	void StormSocketServerBase::SetSocketDisconnected(StormSocketServerConnectionId id)
	{
		while (true)
		{
			if (id.GetGen() != m_Connections[id].m_SlotGen)
			{
				return;
			}

			StormSocketDisconnectFlags::Index cur_flags = (StormSocketDisconnectFlags::Index)m_Connections[id].m_DisconnectFlags;
			if ((cur_flags & StormSocketDisconnectFlags::kSocket) != 0)
			{
				return;
			}

			int new_flags = cur_flags | StormSocketDisconnectFlags::kSocket | StormSocketDisconnectFlags::kLocalClose | StormSocketDisconnectFlags::kRemoteClose;
			if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Connections[id].m_DisconnectFlags, (int *)&cur_flags, (int)new_flags))
			{
				//Console.WriteLine("Connection {0} socket is disconnected", id.m_Index.Index);

				// Tell the sending thread to flush the queue
				SignalOutgoingSocket(id, StormSocketIOOperationType::ClearQueue);

				// Tell the main thread that we've disconnected
				StormSocketEventInfo disconnect_message;
				disconnect_message.ConnectionId = id;
				disconnect_message.Type = StormSocketEventType::Disconnected;
				disconnect_message.RemoteIP = m_Connections[id].m_RemoteIP;
				disconnect_message.RemotePort = m_Connections[id].m_RemotePort;

				while (m_EventQueue.Enqueue(disconnect_message) == false)
				{
					std::this_thread::yield();
				}

				CheckDisconnectFlags(id, (StormSocketDisconnectFlags::Index)new_flags);
				return;
			}
		}
	}

	void StormSocketServerBase::CloseSocket(StormSocketServerConnectionId id)
	{

	}

  void StormSocketServerBase::FreeConnectionResources(StormSocketServerConnectionId id)
  {

  }

	void StormSocketServerBase::CloseSocketThread()
	{
		StormSocketServerConnectionId id;
		while (m_ThreadStopRequested == false)
		{
			m_CloseConnectionSemaphore.WaitOne();

			if (m_ClosingConnectionQueue.TryDequeue(id))
			{
				CloseSocket(id);
				SetSocketDisconnected(id);
				SetDisconnectFlag(id, StormSocketDisconnectFlags::kThreadClose);
			}
		}
	}

	void StormSocketServerBase::SignalCloseThread(StormSocketServerConnectionId id)
	{
		SetDisconnectFlag(id, StormSocketDisconnectFlags::kSignalClose);
	}

	void StormSocketServerBase::SetDisconnectFlag(StormSocketServerConnectionId id, StormSocketDisconnectFlags::Index flags)
	{
		while (true)
		{
			if (id.GetGen() != m_Connections[id].m_SlotGen)
			{
				return;
			}

			StormSocketDisconnectFlags::Index cur_flags = (StormSocketDisconnectFlags::Index)m_Connections[id].m_DisconnectFlags;
			if ((cur_flags & flags) != 0)
			{
				return;
			}

			int new_flags = cur_flags | flags;
			if (std::atomic_compare_exchange_weak((std::atomic_int *)&m_Connections[id].m_DisconnectFlags, (int *)&cur_flags, new_flags))
			{
				if (CheckDisconnectFlags(id, (StormSocketDisconnectFlags::Index)new_flags))
				{
					return;
				}

				if (flags == StormSocketDisconnectFlags::kLocalClose)
				{
					// Send a disconnect packet
					StormMessageWriter disconnect_writer = CreateOutgoingPacket(StormWebsocketOp::Close, true);
					disconnect_writer.CreateHeaderAndApplyMask((int)StormWebsocketOp::Close, true, 0);
					SendPacketToConnection(disconnect_writer, id);
					FreeOutgoingPacket(disconnect_writer);
				}

				if ((flags == StormSocketDisconnectFlags::kLocalClose || flags == StormSocketDisconnectFlags::kRemoteClose) &&
					(new_flags & StormSocketDisconnectFlags::kSocket) == 0 &&
					(new_flags & StormSocketDisconnectFlags::kCloseFlags) == StormSocketDisconnectFlags::kCloseFlags)
				{
					SignalOutgoingSocket(id, StormSocketIOOperationType::Close);
				}

				if (flags == StormSocketDisconnectFlags::kSignalClose)
				{
					m_Connections[id].m_FailedConnection = true;
					if (m_ClosingConnectionQueue.Enqueue(id))
					{
						m_CloseConnectionSemaphore.Release();
					}
				}

				return;
			}
		}
	}

	bool StormSocketServerBase::CheckDisconnectFlags(StormSocketServerConnectionId id, StormSocketDisconnectFlags::Index new_flags)
	{
		if ((new_flags & StormSocketDisconnectFlags::kAllFlags) == StormSocketDisconnectFlags::kAllFlags)
		{
			// If we were still connecting, free the handshake response packet
			if (m_Connections[id].m_State == StormSocketServerConnectionState::HandShake ||
				m_Connections[id].m_State == StormSocketServerConnectionState::SendHandshakeResponse ||
				m_Connections[id].m_State == StormSocketServerConnectionState::SendPong)
			{
				FreeOutgoingPacket(m_Connections[id].m_PendingWriter);
			}

#ifdef USE_MBED
      FreeOutgoingPacket(m_Connections[id].m_EncryptWriter);
#endif

			// Free any pent up packets
			if (m_Connections[id].m_ReaderValid)
			{
				m_Connections[id].m_InitialReader.FreeChain();
			}

			if (m_Connections[id].m_State == StormSocketServerConnectionState::HandleContinuations)
			{
				FreeIncomingPacket(m_Connections[id].m_PendingReader);
			}

      FreeConnectionResources(id);

			// Free the recv buffer
      m_Connections[id].m_RecvBuffer.FreeBuffers();
      m_Connections[id].m_DecryptBuffer.FreeBuffers();

			m_Connections[id].m_SlotGen = (m_Connections[id].m_SlotGen + 1) & 0xFF;

			//Console.WriteLine("Finalizing destruction on connection {0}", id.Index);

			m_Connections[id].m_Socket = InvalidSocketId;
			return true;
		}

		return false;
	}
}
