
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/VertexList.h"

#include <atomic>

static const int kNumScratchVerts = 8092;
static VertexInfo s_ScratchVerts[kNumScratchVerts];
static std::atomic_bool s_ScratchVertsUsed;

VertexList::VertexList()
{
  if(s_ScratchVertsUsed.exchange(true) == false)
  {
    m_Verts = s_ScratchVerts;
    m_Size = 0;
    m_Capacity = 8092;
  }
  else
  {
    m_Verts = nullptr;
    m_Size = 0;
    m_Capacity = 0;
  }
}

VertexList::~VertexList()
{
  if (m_Verts)
  {
    if (m_Verts == s_ScratchVerts)
    {
      s_ScratchVertsUsed.store(false);
    }
    else
    {
      free(m_Verts);
    }
  }
}

void VertexList::AddVert(const VertexInfo & vert)
{
  if (m_Capacity == m_Size)
  {
    Grow();
  }

  memcpy(&m_Verts[m_Size], &vert, sizeof(VertexInfo));
  m_Size++;
}

VertexInfo & VertexList::AddVert()
{
  if (m_Capacity == m_Size)
  {
    Grow();
  }

  return m_Verts[m_Size++];
}

bool VertexList::HasVerts() const
{
  return m_Size > 0;
}

void VertexList::Grow()
{
  auto new_size = m_Capacity == 0 ? 1 : m_Capacity * 2;
  auto new_verts = (VertexInfo *)malloc(sizeof(VertexInfo) * new_size);

  memcpy(new_verts, m_Verts, m_Capacity * sizeof(VertexInfo));

  if (m_Verts == s_ScratchVerts)
  {
    s_ScratchVertsUsed.store(false);
  }
  else
  {
    free(m_Verts);
  }

  m_Verts = new_verts;
  m_Capacity = new_size;
}
