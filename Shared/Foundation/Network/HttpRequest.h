#pragma once

#include <string_view>

#include "Foundation/Delegate/Delegate.h"

class HttpRequest
{
public:
  HttpRequest();
  HttpRequest(const std::string_view & url, const std::string_view & headers);
  HttpRequest(const std::string_view & url, const std::string_view & headers, const std::string_view & body);
  HttpRequest(const HttpRequest & rhs) = delete;
  HttpRequest(HttpRequest && rhs);
  ~HttpRequest();

  HttpRequest & operator = (const HttpRequest & rhs) = delete;
  HttpRequest & operator = (HttpRequest && rhs);

  void Request(const std::string_view & url, const std::string_view & headers);
  void Request(const std::string_view & url, const std::string_view & headers, const std::string_view & body);

  void SetCallback(Delegate<void, const HttpRequest &> && callback);

  bool IsComplete() const;

  const std::string & GetResponse() const;
  const std::string & GetResponseHeaders() const;
  int GetResponseCode();

  void Cleanup();

private:

  int m_RequestId = -1;

};