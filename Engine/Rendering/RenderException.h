#pragma once

#include <exception>

class RenderException : public std::exception
{
public:
  RenderException(int error);

private:
  int m_Error;
};

void ReportRenderError(const char * file, int line, int error);

