#pragma once

#include <optional\optional.hpp>
#include <asio\asio.hpp>

#include <StormSockets\StormSocketServerBase.h>

#ifdef USE_MBED
#include "mbedtls/ssl.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#endif

namespace StormSockets
{
  class StormSocketServerASIO : public StormSocketServerBase
  {
    asio::io_service m_IOService;
    asio::ip::tcp::acceptor m_Acceptor;

    asio::ip::tcp::socket m_AcceptSocket;
    asio::ip::tcp::endpoint m_AcceptEndpoint;

    std::unique_ptr<std::experimental::optional<asio::ip::tcp::socket>[]> m_ClientSockets;

    std::unique_ptr<std::thread[]> m_IOThreads;
    std::unique_ptr<std::thread[]> m_SendThreads;

    std::string m_LocalInterface;
    uint16_t m_Port;

    static const int kBufferSetCount = 8;
    typedef std::array<asio::const_buffer, 8> SendBuffer;

#ifdef USE_MBED

    mbedtls_x509_crt m_Cert;
    mbedtls_pk_context m_PrivateKey;

    mbedtls_entropy_context m_Entropy;
    mbedtls_ctr_drbg_context m_CtrDrbg;

    mbedtls_ssl_config m_SSLConfig;

#endif


  public:

    StormSocketServerASIO(StormSocketInitSettings & settings);
    ~StormSocketServerASIO();

    void Start();
  private:

    void PrepareToAccept();
    void AcceptNewConnection(const asio::error_code& error);

    void ProcessNewData(StormSocketServerConnectionId connection_id, const asio::error_code & error, std::size_t bytes_received);
    bool ProcessReceivedData(StormSocketServerConnectionId connection_id);
    void PrepareToRecv(StormSocketServerConnectionId connection_id);
    void TryProcessReceivedData(StormSocketServerConnectionId connection_id);

    void IOThreadMain();
    void SetBufferSet(SendBuffer & buffer_set, int buffer_index, const void * ptr, int length);

    int FillBufferSet(SendBuffer & buffer_set, int & cur_buffer, int pending_data, StormMessageWriter & writer, int send_offset, StormFixedBlockHandle & send_block);

    void SendThreadMain(int thread_index);

    void ReleaseSendQueue(StormSocketServerConnectionId connection_id, int connection_gen);
    StormMessageWriter CreateWriterInternal();
    StormMessageWriter EncryptWriter(StormSocketServerConnectionId connection_id, StormMessageWriter & writer);

    void CloseSocket(StormSocketServerConnectionId id);
    void FreeConnectionResources(StormSocketServerConnectionId id);
  };
}
