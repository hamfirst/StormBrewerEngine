#pragma once

#include <string_view>

#include "Foundation/Delegate/Delegate.h"

class HttpRequest
{
public:
  HttpRequest();
  HttpRequest(const std::string_view & url, const std::string_view & headers = "");
  HttpRequest(const std::string_view & url, const std::string_view & headers, const std::string_view & body);
  HttpRequest(const HttpRequest & rhs) = delete;
  HttpRequest(HttpRequest && rhs) noexcept;
  ~HttpRequest();

  HttpRequest & operator = (const HttpRequest & rhs) = delete;
  HttpRequest & operator = (HttpRequest && rhs) noexcept;

  void Request(const std::string_view & url, const std::string_view & headers = "");
  void Request(const std::string_view & url, const std::string_view & headers, const std::string_view & body);

  void SetCallback(Delegate<void, const HttpRequest &> && callback);

  bool IsComplete() const;

  const std::string & GetResponse() const;
  const std::string & GetResponseHeaders() const;
  int GetResponseCode();


#ifdef _WEB

  int m_Socket;
  int m_Connected;
  int m_Connecting;
  int m_Completed;

  std::string m_Response;
  std::string m_ResponseHeaders;
  int m_ResponseCode;

  Delegate<void, const HttpRequest &> m_Callback;

public:
  void SetConnected(bool connected);
  void GotResponse(int status_code, czstr response, czstr headers);

#else

  void Cleanup();

  int m_RequestId = -1;

#endif

private:


};