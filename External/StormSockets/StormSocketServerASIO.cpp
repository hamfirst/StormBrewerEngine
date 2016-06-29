
#include "StormSocketServerASIO.h"

#include <fstream>

#ifdef USE_MBED
#include "mbedtls\error.h"
#include "mbedtls\debug.h"
#endif

#ifdef _WINDOWS
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#endif

namespace StormSockets
{
  StormSocketServerASIO::StormSocketServerASIO(StormSocketInitSettings & settings)
    : StormSocketServerBase(settings),
      m_Acceptor(m_IOService),
      m_AcceptSocket(m_IOService)
  {
    m_LocalInterface = settings.LocalInterface;
    m_Port = settings.Port;
    m_UseSSL = false;

    m_ClientSockets = std::make_unique<std::experimental::optional<asio::ip::tcp::socket>[]>(settings.MaxConnections);

    if (settings.CertificateFile && settings.PrivateKeyFile != nullptr)
    {
      std::ifstream cert_file;
      cert_file.open(settings.CertificateFile, std::ifstream::in | std::ifstream::binary);
      cert_file.seekg(0, std::ios::end);
      int cert_file_length = (int)cert_file.tellg();
      cert_file.seekg(0, std::ios::beg);

      std::unique_ptr<char[]> cert_data = std::make_unique<char[]>(cert_file_length + 1);
      cert_file.read(cert_data.get(), cert_file_length);
      cert_data[cert_file_length] = 0;
      cert_file.close();

      std::ifstream key_file;
      key_file.open(settings.PrivateKeyFile, std::ifstream::in | std::ifstream::binary);
      key_file.seekg(0, std::ios::end);
      int key_file_length = (int)key_file.tellg();
      key_file.seekg(0, std::ios::beg);

      std::unique_ptr<char[]> key_data = std::make_unique<char[]>(key_file_length + 1);
      key_file.read(key_data.get(), key_file_length);
      key_data[key_file_length] = 0;
      key_file.close();

#ifdef USE_MBED

      int error;

#define MBED_CHECK_ERROR if(error < 0) throw std::runtime_error("Certificate load error " + std::to_string(error));

      mbedtls_x509_crt_init(&m_Cert);
      error = mbedtls_x509_crt_parse(&m_Cert, (uint8_t *)cert_data.get(), cert_file_length + 1); MBED_CHECK_ERROR;

      mbedtls_pk_init(&m_PrivateKey);
      error = mbedtls_pk_parse_key(&m_PrivateKey, (uint8_t *)key_data.get(), key_file_length + 1, nullptr, 0); MBED_CHECK_ERROR;

      mbedtls_entropy_init(&m_Entropy);
      mbedtls_ctr_drbg_init(&m_CtrDrbg);

      const char *pers = "stormsockets";
      error = mbedtls_ctr_drbg_seed(&m_CtrDrbg, mbedtls_entropy_func, &m_Entropy, (uint8_t *)pers, strlen(pers)); MBED_CHECK_ERROR;

      mbedtls_ssl_config_init(&m_SSLConfig);

      error = mbedtls_ssl_config_defaults(&m_SSLConfig,
        MBEDTLS_SSL_IS_SERVER,
        MBEDTLS_SSL_TRANSPORT_STREAM,
        MBEDTLS_SSL_PRESET_DEFAULT);
      MBED_CHECK_ERROR;

      mbedtls_ssl_conf_rng(&m_SSLConfig, mbedtls_ctr_drbg_random, &m_CtrDrbg);

      auto debug_func = [](void *ctx, int level, const char *file, int line, const char *str) 
      {     
        fprintf((FILE *)ctx, "%s:%04d: %s", file, line, str);
        fflush((FILE *)ctx); 
      };

      mbedtls_ssl_conf_dbg(&m_SSLConfig, debug_func, stdout);

      mbedtls_ssl_conf_ca_chain(&m_SSLConfig, m_Cert.next, NULL);
      error = mbedtls_ssl_conf_own_cert(&m_SSLConfig, &m_Cert, &m_PrivateKey); MBED_CHECK_ERROR;

      //mbedtls_debug_set_threshold(5);

#endif

      m_UseSSL = true;
    }
  }

  StormSocketServerASIO::~StormSocketServerASIO()
  {
    for (int index = 0; index < m_NumIOThreads; index++)
    {
      m_IOThreads[index].join();
    }

    for (int index = 0; index < m_NumSendThreads; index++)
    {
      m_SendThreadSemaphores[index].Release();
      m_SendThreads[index].join();
    }

    if (m_UseSSL)
    {
#ifdef USE_MBED
      mbedtls_x509_crt_free(&m_Cert);
      mbedtls_pk_free(&m_PrivateKey);
      mbedtls_ssl_config_free(&m_SSLConfig);
      mbedtls_ctr_drbg_free(&m_CtrDrbg);
      mbedtls_entropy_free(&m_Entropy);
#endif
    }
  }

  void StormSocketServerASIO::Start()
  {
    asio::ip::tcp::endpoint endpoint(asio::ip::address_v4::from_string(m_LocalInterface), m_Port);
    m_Acceptor.open(asio::ip::tcp::v4());
    m_Acceptor.bind(endpoint);
    m_Acceptor.listen();

    // Create the initial listening socket
    PrepareToAccept();

    // Start the io threads
    m_IOThreads = std::make_unique<std::thread[]>(m_NumIOThreads);
    for (int index = 0; index < m_NumIOThreads; index++)
    {
      m_IOThreads[index] = std::thread(&StormSocketServerASIO::IOThreadMain, this);
    }

    m_SendThreads = std::make_unique<std::thread[]>(m_NumSendThreads);
    for (int index = 0; index < m_NumSendThreads; index++)
    {
      m_SendThreads[index] = std::thread(&StormSocketServerASIO::SendThreadMain, this, index);
    }
  }

  void StormSocketServerASIO::PrepareToAccept()
  {
    auto accept_callback = [this](const asio::error_code & error) { AcceptNewConnection(error); };
    m_Acceptor.async_accept(m_AcceptSocket, m_AcceptEndpoint, accept_callback);
  }

  void StormSocketServerASIO::AcceptNewConnection(const asio::error_code & error)
  {
    m_AcceptSocket.set_option(asio::ip::tcp::no_delay(true));
    m_AcceptSocket.set_option(asio::socket_base::linger(1, 1));
    m_AcceptSocket.non_blocking(true);

    StormSocketServerConnectionId connection_id = AllocateConnection(m_AcceptSocket.native_handle(), 
      m_AcceptEndpoint.address().to_v4().to_ulong(), m_AcceptEndpoint.port());

    if (connection_id == StormSocketServerConnectionId::InvalidConnectionId)
    {
      m_AcceptSocket.close();
      m_AcceptSocket = asio::ip::tcp::socket(m_IOService);

      PrepareToAccept();
      return;
    }

    m_ClientSockets[connection_id].emplace(std::move(m_AcceptSocket));

    m_Connections[connection_id].m_RecvBuffer.InitBuffers();
    if (m_UseSSL)
    {
#ifdef USE_MBED

      mbedtls_ssl_init(&m_Connections[connection_id].m_SSLContext.m_SSLContext);
      mbedtls_ssl_setup(&m_Connections[connection_id].m_SSLContext.m_SSLContext, &m_SSLConfig);

      m_Connections[connection_id].m_DecryptBuffer.InitBuffers();

      auto send_callback = [](void * ctx, const unsigned char * data, size_t size) -> int
      {
        StormSocketServerConnection * connection = (StormSocketServerConnection *)ctx;
        connection->m_EncryptWriter.WriteByteBlock(data, 0, size);
        return size;
      };

      auto recv_callback = [](void * ctx, unsigned char * data, size_t size) -> int
      {
        StormSocketServerConnection * connection = (StormSocketServerConnection *)ctx;
        if (connection->m_DecryptBuffer.m_DataAvail == 0)
        {
          return MBEDTLS_ERR_SSL_WANT_READ;
        }

        void * block_start = connection->m_DecryptBuffer.m_Allocator->ResolveHandle(connection->m_DecryptBuffer.m_BlockStart);
        block_start = Marshal::MemOffset(block_start, connection->m_DecryptBuffer.m_ReadOffset);

        int mem_avail = connection->m_DecryptBuffer.m_Allocator->GetBlockSize() - connection->m_DecryptBuffer.m_ReadOffset;
        mem_avail = std::min(mem_avail, (int)connection->m_DecryptBuffer.m_DataAvail);
        mem_avail = std::min(mem_avail, (int)size);

        memcpy(data, block_start, mem_avail);
        return mem_avail;
      };

      auto recv_timeout_callback = [](void * ctx, unsigned char * data, size_t size, uint32_t timeout) -> int
      {
        StormSocketServerConnection * connection = (StormSocketServerConnection *)ctx;
        if (connection->m_DecryptBuffer.m_DataAvail == 0)
        {
          return MBEDTLS_ERR_SSL_WANT_READ;
        }

        void * block_start = connection->m_DecryptBuffer.m_Allocator->ResolveHandle(connection->m_DecryptBuffer.m_BlockStart);
        block_start = Marshal::MemOffset(block_start, connection->m_DecryptBuffer.m_ReadOffset);

        int mem_avail = connection->m_DecryptBuffer.m_Allocator->GetBlockSize() - connection->m_DecryptBuffer.m_ReadOffset;
        mem_avail = std::min(mem_avail, (int)connection->m_DecryptBuffer.m_DataAvail);
        mem_avail = std::min(mem_avail, (int)size);

        memcpy(data, block_start, mem_avail);
        connection->m_DecryptBuffer.DiscardData(mem_avail);
        return mem_avail;
      };

      mbedtls_ssl_set_bio(&m_Connections[connection_id].m_SSLContext.m_SSLContext,
        &m_Connections[connection_id],
        send_callback,
        recv_callback,
        recv_timeout_callback);
#endif
    }

    PrepareToRecv(connection_id);
    PrepareToAccept();
  }

  void StormSocketServerASIO::ProcessNewData(StormSocketServerConnectionId connection_id, const asio::error_code & error, std::size_t bytes_received)
  {
    if (!error)
    {
      if (m_UseSSL)
      {
        m_Connections[connection_id].m_DecryptBuffer.GotData(bytes_received);
        if (m_Connections[connection_id].m_SSLContext.m_SSLHandshakeComplete == false)
        {
#ifdef USE_MBED
          int ec = mbedtls_ssl_handshake(&m_Connections[connection_id].m_SSLContext.m_SSLContext);

          char error_str[1024];
          mbedtls_strerror(ec, error_str, sizeof(error_str));

          if (m_Connections[connection_id].m_EncryptWriter.m_PacketInfo->m_TotalLength > 0)
          {
            SendPacketToConnection(m_Connections[connection_id].m_EncryptWriter, connection_id);
            FreeOutgoingPacket(m_Connections[connection_id].m_EncryptWriter);
            m_Connections[connection_id].m_EncryptWriter = CreateWriterInternal();
            m_Connections[connection_id].m_EncryptWriter.m_Encrypt = false;
          }

          if (ec == 0)
          {
            m_Connections[connection_id].m_SSLContext.m_SSLHandshakeComplete = true;
          }
          else if (ec != MBEDTLS_ERR_SSL_WANT_READ)
          {
            SetSocketDisconnected(connection_id);
            SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kRecvThread);
            return;
          }
#endif
        }
        

        if (m_Connections[connection_id].m_SSLContext.m_SSLHandshakeComplete == true)
        {
#ifdef USE_MBED
          do
          {
            void * block_mem = m_Connections[connection_id].m_RecvBuffer.m_Allocator->ResolveHandle(m_Connections[connection_id].m_RecvBuffer.m_BlockCur);
            block_mem = Marshal::MemOffset(block_mem, m_Connections[connection_id].m_RecvBuffer.m_WriteOffset);
            int mem_avail = m_Connections[connection_id].m_RecvBuffer.m_Allocator->GetBlockSize() - m_Connections[connection_id].m_RecvBuffer.m_WriteOffset;

            int ret = mbedtls_ssl_read(&m_Connections[connection_id].m_SSLContext.m_SSLContext, (uint8_t *)block_mem, mem_avail);

            if (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE)
              break;

            if (ret < 0)
            {
              char error_str[1024];
              mbedtls_strerror(ret, error_str, sizeof(error_str));

              SetSocketDisconnected(connection_id);
              SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kRecvThread);
              return;
            }

            m_Connections[connection_id].m_UnparsedDataLength.fetch_add(ret);
            m_Connections[connection_id].m_RecvBuffer.GotData(ret);
          } while (true);
#endif
        }
      }
      else
      {
        // Data just goes directly into the recv buffer
        m_Connections[connection_id].m_UnparsedDataLength.fetch_add(bytes_received);
        m_Connections[connection_id].m_RecvBuffer.GotData(bytes_received);
      }

      uint64_t prof = Profiling::StartProfiler();

      TryProcessReceivedData(connection_id);
      
      PrepareToRecv(connection_id);
      Profiling::EndProfiler(prof, ProfilerCategory::kProcData);
    }
    else
    {
      SetSocketDisconnected(connection_id);
      SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kRecvThread);
    }
  }


  void StormSocketServerASIO::TryProcessReceivedData(StormSocketServerConnectionId connection_id)
  {
    if (ProcessReceivedData(connection_id) == false)
    {
      auto recheck_callback = [=]() 
      {
        TryProcessReceivedData(connection_id);
      };

      m_IOService.post(recheck_callback);
    }
  }

  bool StormSocketServerASIO::ProcessReceivedData(StormSocketServerConnectionId connection_id)
  {
    // Lock the receiver
    int old_val = 0;
    if (std::atomic_compare_exchange_weak(&m_Connections[connection_id].m_RecvCriticalSection, &old_val, 1) == false)
    {
      return false;
    }

    bool success = ProcessData(connection_id);

    m_Connections[connection_id].m_RecvCriticalSection.store(0);
    return success;
  }

  void StormSocketServerASIO::PrepareToRecv(StormSocketServerConnectionId connection_id)
  {
    StormSocketBuffer * buffer = m_UseSSL ? &m_Connections[connection_id].m_DecryptBuffer : &m_Connections[connection_id].m_RecvBuffer;

    void * buffer_start =
      Marshal::MemOffset(m_Allocator.ResolveHandle(buffer->m_BlockCur), buffer->m_WriteOffset);

    std::array<asio::mutable_buffer, 2> buffer_set = 
    {
      asio::buffer(buffer_start, m_FixedBlockSize - buffer->m_WriteOffset),
      asio::buffer(m_Allocator.ResolveHandle(buffer->m_BlockNext), m_FixedBlockSize)
    };

    auto recv_callback = [=](const asio::error_code & error, size_t bytes_received) { ProcessNewData(connection_id, error, bytes_received); };
    m_ClientSockets[connection_id]->async_read_some(buffer_set, recv_callback);
  }

  void StormSocketServerASIO::IOThreadMain()
  {
    m_IOService.run();
  }

  void StormSocketServerASIO::SetBufferSet(SendBuffer & buffer_set, int buffer_index, const void * ptr, int length)
  {
    buffer_set[buffer_index] = asio::buffer(ptr, length);
  }

  int StormSocketServerASIO::FillBufferSet(SendBuffer & buffer_set, int & cur_buffer, int pending_data, StormMessageWriter & writer, int send_offset, StormFixedBlockHandle & send_block)
  {
    StormFixedBlockHandle block_handle = send_block;
    send_block = InvalidBlockHandle;
    int websocket_header_offset = send_offset;

    while (pending_data > 0 && cur_buffer < kBufferSetCount && block_handle != InvalidBlockHandle)
    {
      int potential_data_in_block = m_FixedBlockSize - websocket_header_offset - (writer.m_ReservedHeaderLength + writer.m_ReservedTrailerLength);
      int set_len = std::min(pending_data, potential_data_in_block);
      int data_start = writer.m_ReservedHeaderLength - writer.m_HeaderLength + websocket_header_offset;
      int data_length = writer.m_HeaderLength + set_len + writer.m_TrailerLength;

      void * block = m_Allocator.ResolveHandle(block_handle);

      SetBufferSet(buffer_set, cur_buffer, Marshal::MemOffset(block, data_start), data_length);
      block_handle = m_Allocator.GetNextBlock(block_handle);

      websocket_header_offset = 0;
      pending_data -= set_len;
      send_block = block_handle;

      cur_buffer++;
    }

    return pending_data;
  }

  void StormSocketServerASIO::SendThreadMain(int thread_index)
  {
    StormSocketIOOperation op;

    StormMessageWriter writer;

    while (m_ThreadStopRequested == false)
    {
      m_SendThreadSemaphores[thread_index].WaitOne(100);

      while (m_SendQueue[thread_index].TryDequeue(op, 0, m_SendQueueIncdices.get(), m_SendQueueArray.get()))
      {
        StormSocketServerConnectionId connection_id = op.m_ConnectionId;
        int connection_gen = connection_id.GetGen();

        if (op.m_Type == StormSocketIOOperationType::FreePacket)
        {
          m_Connections[connection_id].m_PendingFreeData += op.m_Size;
          if (connection_gen != m_Connections[op.m_ConnectionId.GetIndex()].m_SlotGen)
          {
            continue;
          }

          StormSocketFreeQueueElement free_elem;

          while (m_FreeQueue[connection_id].PeekTop(free_elem, connection_gen, m_FreeQueueIncdices.get(), m_FreeQueueArray.get(), 0))
          {
            int writer_len = free_elem.m_Writer.m_PacketInfo->m_TotalLength;
            if (m_Connections[connection_id].m_PendingFreeData >= writer_len)
            {
              FreeOutgoingPacket(free_elem.m_Writer);
              ReleasePacketSlot(connection_id);

              m_Connections[connection_id].m_PendingFreeData -= writer_len;
              m_FreeQueue[connection_id].Advance(connection_gen, m_FreeQueueIncdices.get(), m_FreeQueueArray.get());
            }
            else
            {
              break;
            }
          }
        }
        else if (op.m_Type == StormSocketIOOperationType::ClearQueue)
        {
          if (connection_gen != m_Connections[op.m_ConnectionId.GetIndex()].m_SlotGen)
          {
            continue;
          }

          ReleaseSendQueue(connection_id, connection_gen);
          SetDisconnectFlag(connection_id, StormSocketDisconnectFlags::kSendThread);
          SignalCloseThread(connection_id);
        }
        else if (op.m_Type == StormSocketIOOperationType::Close)
        {
          if (connection_gen != m_Connections[op.m_ConnectionId.GetIndex()].m_SlotGen)
          {
            continue;
          }

          SignalCloseThread(connection_id);
        }
        else if (op.m_Type == StormSocketIOOperationType::SendPacket)
        {
          SendBuffer buffer_set;
          if (m_OutputQueue[connection_id].PeekTop(writer, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), 0))
          {
            StormSocketFreeQueueElement free_queue_elem;

            if (writer.m_Encrypt && m_UseSSL)
            {
              StormMessageWriter encrypted = EncryptWriter(connection_id, writer);
              m_OutputQueue[connection_id].ReplaceTop(encrypted, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), 0);

              FreeOutgoingPacket(writer);

              writer = encrypted;
            }

            int buffer_count = 0;
            int packet_count = 0;
            int send_offset = 0;
            int total_send_length = 0;

            while (buffer_count < kBufferSetCount)
            {
              if (m_Connections[connection_id].m_PendingRemainingData == 0)
              {
                send_offset = writer.m_PacketInfo->m_SendOffset;
                m_Connections[connection_id].m_PendingRemainingData = writer.m_PacketInfo->m_TotalLength;
                m_Connections[connection_id].m_PendingSendBlock = writer.m_PacketInfo->m_StartBlock;
              }

              int remaining_data =
                FillBufferSet(buffer_set, buffer_count, m_Connections[connection_id].m_PendingRemainingData, writer, send_offset, m_Connections[connection_id].m_PendingSendBlock);

              total_send_length += m_Connections[connection_id].m_PendingRemainingData - remaining_data;
              m_Connections[connection_id].m_PendingRemainingData = remaining_data;

              packet_count++;

              if (m_OutputQueue[connection_id].PeekTop(writer, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), packet_count) == false)
              {
                break;
              }

              if (writer.m_Encrypt && m_UseSSL)
              {
                StormMessageWriter encrypted = EncryptWriter(connection_id, writer);
                m_OutputQueue[connection_id].ReplaceTop(encrypted, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), packet_count);

                FreeOutgoingPacket(writer);

                writer = encrypted;
              }
            }

            int advance_count;

            // If we sent the max blocks worth of data and still have shit to send...
            if (m_Connections[connection_id].m_PendingRemainingData > 0)
            {
              advance_count = packet_count - 1;
              // Free every writer that got written to except for the last one
              for (int index = 0; index < packet_count - 1; index++)
              {
                m_OutputQueue[connection_id].PeekTop(writer, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), index);
                free_queue_elem.m_Writer = writer;

                if (m_FreeQueue[connection_id].Enqueue(free_queue_elem, connection_gen, m_FreeQueueIncdices.get(), m_FreeQueueArray.get()) == false)
                {
                  throw std::runtime_error("Free queue ran out of space");
                }
              }
              // Requeue up this operation so that we don't block out the number of writers
              if (m_SendQueue[thread_index].Enqueue(op, 0, m_SendQueueIncdices.get(), m_SendQueueArray.get()) == false)
              {
                throw std::runtime_error("Send queue ran out of space");
              }
            }
            else
            {
              advance_count = packet_count;
              // Just free everything
              for (int index = 0; index < packet_count; index++)
              {
                m_OutputQueue[connection_id].PeekTop(writer, connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get(), index);
                free_queue_elem.m_Writer = writer;

                if (m_FreeQueue[connection_id].Enqueue(free_queue_elem, connection_gen, m_FreeQueueIncdices.get(), m_FreeQueueArray.get()) == false)
                {
                  throw std::runtime_error("Free queue ran out of space");
                }
              }
            }

            uint64_t prof = Profiling::StartProfiler();
            auto send_callback = [=](const asio::error_code & error, std::size_t bytes_transfered)
            {
              if (!error)
              {
                SignalOutgoingSocket(connection_id, StormSocketIOOperationType::FreePacket, bytes_transfered);
              }
              else
              {
                SetSocketDisconnected(connection_id);
              }
            };

            m_ClientSockets[connection_id]->async_send(buffer_set, send_callback);

            Profiling::EndProfiler(prof, ProfilerCategory::kSend);

            for (int index = 0; index < advance_count; index++)
            {
              m_OutputQueue[connection_id].Advance(connection_gen, m_OutputQueueIncdices.get(), m_OutputQueueArray.get());
            }
          }
        }
      }
    }
  }

  void StormSocketServerASIO::ReleaseSendQueue(StormSocketServerConnectionId connection_id, int connection_gen)
  {
    StormMessageWriter writer;
    // Lock the queue so that nothing else can put packets into it
    m_OutputQueue[connection_id].Lock(connection_gen + 1, m_OutputQueueIncdices.get(), m_OutputQueueArray.get());

    // Drain the remaining packets
    while (m_OutputQueue[connection_id].TryDequeue(writer, connection_gen + 1, m_OutputQueueIncdices.get(), m_OutputQueueArray.get()))
    {
      if (writer.m_PacketInfo != NULL)
      {
        FreeOutgoingPacket(writer);
      }
    }

    m_OutputQueue[connection_id].Reset(connection_gen + 1, m_OutputQueueIncdices.get(), m_OutputQueueArray.get());

    m_FreeQueue[connection_id].Lock(connection_gen + 1, m_FreeQueueIncdices.get(), m_FreeQueueArray.get());
    StormSocketFreeQueueElement free_elem;

    while (m_FreeQueue[connection_id].TryDequeue(free_elem, connection_gen + 1, m_FreeQueueIncdices.get(), m_FreeQueueArray.get()))
    {
      FreeOutgoingPacket(free_elem.m_Writer);
    }

    m_FreeQueue[connection_id].Reset(connection_gen + 1, m_FreeQueueIncdices.get(), m_FreeQueueArray.get());
  }

  StormMessageWriter StormSocketServerASIO::CreateWriterInternal()
  {
    uint64_t prof = Profiling::StartProfiler();
    StormMessageWriter writer;
    writer.Init(&m_Allocator, &m_MessageSenders, m_UseSSL, 0, 0);
    Profiling::EndProfiler(prof, ProfilerCategory::kCreatePacket);
    return writer;
  }

  StormMessageWriter StormSocketServerASIO::EncryptWriter(StormSocketServerConnectionId connection_id, StormMessageWriter & writer)
  {
#ifdef USE_MBED
    StormFixedBlockHandle cur_block = writer.m_PacketInfo->m_StartBlock;

    int data_to_encrypt = writer.m_PacketInfo->m_TotalLength;

    int block_index = 0;
    while (cur_block != InvalidBlockHandle)
    {
      void * block_base = m_Allocator.ResolveHandle(cur_block);
      int start_offset = (block_index == 0 ? writer.m_PacketInfo->m_SendOffset : 0);
      int header_offset = writer.m_ReservedHeaderLength + start_offset;
      int block_size = writer.m_Allocator->GetBlockSize() - (writer.m_ReservedHeaderLength + writer.m_ReservedTrailerLength + start_offset);

      int data_size = std::min(data_to_encrypt, block_size);

      void * block_mem = Marshal::MemOffset(block_base, header_offset);
      int ec = mbedtls_ssl_write(&m_Connections[connection_id].m_SSLContext.m_SSLContext, (uint8_t *)block_mem, data_size);
      if (ec < 0)
      {
        throw std::runtime_error("Error encrypting packet");
      }

      data_to_encrypt -= data_size;

      cur_block = m_Allocator.GetNextBlock(cur_block);
      block_index++;
    }

    StormMessageWriter encrypted = m_Connections[connection_id].m_EncryptWriter;
    m_Connections[connection_id].m_EncryptWriter = CreateWriterInternal();
    m_Connections[connection_id].m_EncryptWriter.m_Encrypt = false;

    return encrypted;
#else

    StormMessageWriter dupe = writer.Duplicate();
    return dupe;

#endif
  }

  void StormSocketServerASIO::CloseSocket(StormSocketServerConnectionId id)
  {
    asio::error_code ec;
    m_ClientSockets[id]->close(ec);
  }

  void StormSocketServerASIO::FreeConnectionResources(StormSocketServerConnectionId id)
  {
    StormSocketServerBase::FreeConnectionResources(id);

#ifdef USE_MBED
    mbedtls_ssl_free(&m_Connections[id].m_SSLContext.m_SSLContext);
#endif

    m_ClientSockets[id]->close();
    m_ClientSockets[id] = std::experimental::optional<asio::ip::tcp::socket>();
  }
}
