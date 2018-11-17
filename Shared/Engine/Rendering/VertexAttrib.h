#pragma once


static const int kMaxVertexAttribs = 16;

struct VertexAttrib
{
  const char * m_Name;
  int m_Size = 0;
  unsigned int m_Type = 0;
  unsigned char m_Normalized = 0;
  int m_Stride = 0;
  void * m_Ptr = nullptr;
};

struct VertexAttribSpec
{
  int m_NumAttribs;
  NotNullPtr<VertexAttrib> m_Attribs;
};

struct VertexAttribState
{
  bool m_Enabled = false;
  int m_Size = 0;
  unsigned int m_Type = 0;
  unsigned char m_Normalized = 0;
  int m_Stride = 0;
  void * m_Ptr = nullptr;
};

extern VertexAttribSpec g_DefaultVertexSpec;
