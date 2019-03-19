
#include "Foundation/Common.h"
#include "Foundation/Network/NetworkInternal.h"
#include "Foundation/Network/HttpRequest.h"

#ifndef _WEB

HttpRequest::HttpRequest()
{

}

HttpRequest::HttpRequest(const std::string_view & url, const std::string_view & headers)
{
  Request(url, headers);
}

HttpRequest::HttpRequest(const std::string_view & url, const std::string_view & headers, const std::string_view & body)
{
  Request(url, headers, body);
}

HttpRequest::HttpRequest(HttpRequest && rhs) noexcept
{
  m_RequestId = rhs.m_RequestId;
  rhs.m_RequestId = -1;

  if(m_RequestId)
  {
    auto & req = g_HttpData[m_RequestId];
    req.m_Request = this;
  }
}

HttpRequest::~HttpRequest()
{
  Cleanup();
}

HttpRequest & HttpRequest::operator = (HttpRequest && rhs) noexcept
{
  Cleanup();

  m_RequestId = rhs.m_RequestId;
  rhs.m_RequestId = -1;

  if(m_RequestId)
  {
    auto & req = g_HttpData[m_RequestId];
    req.m_Request = this;
  }

  return *this;
}

void HttpRequest::Request(const std::string_view & url, const std::string_view & headers)
{
  Cleanup();

  m_RequestId = (int)g_HttpIdAllocator.Allocate();

  StormSockets::StormURI uri;
  StormSockets::ParseURI(url.data(), uri);

  auto & req = g_HttpData[m_RequestId];
  req.m_ConnectionId = g_NetworkFrontendHttp->RequestConnect(uri, "GET", nullptr, 0, headers.data(), (int)headers.length());
  req.m_State = NetworkConnectionState::kConnecting;
  req.m_Request = this;
}

void HttpRequest::Request(const std::string_view & url, const std::string_view & headers, const std::string_view & body)
{
  Cleanup();

  m_RequestId = (int)g_HttpIdAllocator.Allocate();

  StormSockets::StormURI uri;
  StormSockets::ParseURI(url.data(), uri);

  auto & req = g_HttpData[m_RequestId];
  req.m_ConnectionId = g_NetworkFrontendHttp->RequestConnect(uri, "POST", body.data(), (int)body.length(), headers.data(), (int)headers.length());
  req.m_State = NetworkConnectionState::kConnecting;
  req.m_Request = this;
}

void HttpRequest::SetCallback(Delegate<void, const HttpRequest &> && callback)
{
  if(m_RequestId == -1)
  {
    return;
  }

  auto & req = g_HttpData[m_RequestId];
  req.m_Callback = std::move(callback);
}

bool HttpRequest::IsComplete() const
{
  if(m_RequestId == -1)
  {
    return true;
  }

  auto & req = g_HttpData[m_RequestId];
  return req.m_Disconnected;
}

const std::string & HttpRequest::GetResponse() const
{
  static std::string empty;
  if(m_RequestId == -1)
  {
    return empty;
  }

  auto & req = g_HttpData[m_RequestId];
  return req.m_Response;
}

const std::string & HttpRequest::GetResponseHeaders() const
{
  static std::string empty;
  if(m_RequestId == -1)
  {
    return empty;
  }

  auto & req = g_HttpData[m_RequestId];
  return req.m_ResponseHeaders;
}

int HttpRequest::GetResponseCode()
{
  if(m_RequestId == -1)
  {
    return 0;
  }

  auto & req = g_HttpData[m_RequestId];
  return req.m_ResponseCode;
}

void HttpRequest::Cleanup()
{
  if(m_RequestId == -1)
  {
    return;
  }

  auto & req = g_HttpData[m_RequestId];
  req.m_Freed = true;

  if(req.m_Disconnected)
  {
    g_HttpIdAllocator.Release((std::size_t)m_RequestId);
    req = {};
  }
  else
  {
    g_NetworkFrontendHttp->ForceDisconnect(req.m_ConnectionId);
  }

  m_RequestId = -1;
}

#endif