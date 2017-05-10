#pragma once

#include <exception>

class ENGINE_EXPORT RenderException : public std::exception
{
public:
  RenderException(int error);

private:
  int m_Error;
};

void ENGINE_EXPORT ReportRenderError(const char * file, int line, int error);

