#pragma once

#include <asio\asio.hpp>


class DocumentServer final
{
  bool Start();


private:

  asio::io_service m_Service;
  asio::ip::tcp::socket m_Socket;

};

