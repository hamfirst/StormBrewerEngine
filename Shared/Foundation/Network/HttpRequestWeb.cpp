
#include "Foundation/Common.h"
#include "Foundation/Network/HttpRequest.h"
#include "Foundation/Allocator/IdAllocator.h"

#ifdef _WEB

#include <emscripten/html5.h>
#include <emscripten/emscripten.h>

static bool s_HttpRequestInit = false;
struct HttpRequestAllocatorData
{
  HttpRequestAllocatorData()
  {
    s_HttpRequestInit = true;
  }

  ~HttpRequestAllocatorData()
  {
    s_HttpRequestInit = false;
  }

  IdAllocator m_HttpRequestIdAllocator;
};

HttpRequestAllocatorData s_HttpRequestAllocInfo;
std::vector<HttpRequest *> s_HttpRequests;

extern "C"
{
  void HandleHttpRequestConnect(int index)
  {
    s_HttpRequests[index]->SetConnected(true);
  }

  void HandleHttpRequestMessage(int status_code, czstr response, czstr headers)
  {
    s_HttpRequests[index]->GotResponse(status_code, response, headers);
  }

  void HandleHttpRequestClose(int index)
  {
    s_HttpRequests[index]->SetConnected(false);
  }
}

#define INVALID_SOCKET -1

HttpRequest::HttpRequest() :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false),
  m_Completed(false)
{

}

HttpRequest::HttpRequest(const std::string_view & url, const std::string_view & headers) :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false),
  m_Completed(false)
{
  Request(url, headers);
}

HttpRequest::HttpRequest(const std::string_view & url, const std::string_view & headers, const std::string_view & body) :
  m_Socket((int)INVALID_SOCKET),
  m_Connected(false),
  m_Connecting(false),
  m_Completed(false)
{
  Request(url, headers, body);
}

HttpRequest::~HttpRequest()
{
  Cleanup();
}

HttpRequest::HttpRequest(HttpRequest && rhs) noexcept
{
  m_Socket = rhs.m_Socket;
  m_Connected = rhs.m_Connected;
  m_Connecting = rhs.m_Connecting;
  m_Completed = rhs.m_Completed;

  m_Response = std::move(m_Response);
  m_ResponseHeaders = std::move(m_ResponseHeaders);
  m_ResponseCode = m_ResponseCode;

  m_Callback = std::move(rhs.m_Callback);

  rhs.m_Socket = (int)INVALID_SOCKET;
  rhs.m_Connected = false;
  rhs.m_Connecting = false;

  rhs.m_ResponseCode = 0;
}

HttpRequest & HttpRequest::operator = (HttpRequest && rhs) noexcept
{
  Cleanup();

  m_Socket = rhs.m_Socket;
  m_Connected = rhs.m_Connected;
  m_Connecting = rhs.m_Connecting;
  m_Completed = rhs.m_Completed;

  m_Response = std::move(m_Response);
  m_ResponseHeaders = std::move(m_ResponseHeaders);
  m_ResponseCode = m_ResponseCode;

  m_Callback = std::move(rhs.m_Callback);

  rhs.m_Socket = (int)INVALID_SOCKET;
  rhs.m_Connected = false;
  rhs.m_Connecting = false;

  rhs.m_ResponseCode = 0;
}

void HttpRequest::Request(const std::string_view & url, const std::string_view & headers)
{
  Cleanup();

  if (s_HttpRequestInit == false)
  {
    return;
  }

  m_Socket = s_HttpRequestAllocInfo.m_HttpRequestIdAllocator.Allocate();
  while ((int)s_HttpRequests.size() <= m_Socket)
  {
    s_HttpRequests.push_back(nullptr);
  }

  s_HttpRequests[m_Socket] = this;
  EM_ASM_ARGS({ FoundationCreateHttpRequest($0, $1, $2, $3); }, m_Socket, url.data(), headers.data(), "");
  m_Connecting = true;
}

void HttpRequest::Request(const std::string_view & url, const std::string_view & headers, const std::string_view & body)
{
  Cleanup();

  if (s_HttpRequestInit == false)
  {
    return;
  }

  m_Socket = s_HttpRequestAllocInfo.m_HttpRequestIdAllocator.Allocate();
  while ((int)s_HttpRequests.size() <= m_Socket)
  {
    s_HttpRequests.push_back(nullptr);
  }

  s_HttpRequests[m_Socket] = this;
  EM_ASM_ARGS({ FoundationCreateHttpRequest($0, $1, $2, $3); }, m_Socket, url.data(), headers.data(), body.data());
  m_Connecting = true;
}

bool HttpRequest::IsConnected()
{
  return m_Connected;
}

bool HttpRequest::IsConnecting()
{
  return m_Connecting;
}

void HttpRequest::Cleanup()
{
  m_Connected = false;
  m_Connecting = false;
  m_Completed = false;

  m_Callback.Clear();

  if (s_HttpRequestInit == false)
  {
    return;
  }

  if (m_Socket == (int)INVALID_SOCKET)
  {
    return;
  }

  s_HttpRequests[m_Socket] = nullptr;
  s_HttpRequestAllocInfo.m_HttpRequestIdAllocator.Release(m_Socket);
  EM_ASM_ARGS({ FoundationDestroyHttpRequest($0); }, m_Socket);

  m_Socket = (int)INVALID_SOCKET;
}

void HttpRequest::SetCallback(Delegate<void, const HttpRequest &> && callback)
{
  m_Callback = std::move(callback);
}

bool HttpRequest::IsComplete() const
{
  return m_Complete != 0;
}

const std::string & HttpRequest::GetResponse() const
{
  return m_Response;
}

const std::string & HttpRequest::GetResponseHeaders() const
{
  return m_ResponseHeaders;
}

int HttpRequest::GetResponseCode()
{
  return m_ResponseCode;
}

void HttpRequest::SetConnected(bool connected)
{
  m_Connected = connected;
  m_Connecting = false;

  if(connected == false)
  {
    m_Complete = true;
  }
}

void HttpRequest::GotResponse(int status_code, czstr response, czstr headers)
{
  m_StatusCode = status_code;
  m_Response = response;
  m_ResponseHeaders = headers;

  m_Connected = false;
  m_Connecting = false;
  m_Completed = true;

  if(m_Callback)
  {
    m_Callback(*this);
  }
}

#endif