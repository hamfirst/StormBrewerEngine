#pragma once

#include "VertexDefinition.h"


class ENGINE_EXPORT VertexList
{
public:
  VertexList();
  VertexList(const VertexList & rhs) = delete;
  VertexList(VertexList && rhs) = delete;

  ~VertexList();

  VertexList & operator = (const VertexList & rhs) = delete;
  VertexList & operator = (VertexList && rhs) = delete;

  void AddVert(const VertexInfo & vert);
  VertexInfo & AddVert();

private:

  void Grow();

private:

  friend class VertexBuffer;

  gsl::owner<VertexInfo *> m_Verts;
  std::size_t m_Size;
  std::size_t m_Capacity;
};

