#pragma once

#include "Foundation/Common.h"

enum class FrameEditorEdgeType
{
  kTop,
  kBottom,
  kLeft,
  kRight,
};

struct FrameEditorEdge
{
  Vector2 m_P1;
  Vector2 m_P2;
  FrameEditorEdgeType m_Type;
};

class FrameEditorByteArray
{
public:

  FrameEditorByteArray(const FrameEditorByteArray &) = delete;
  FrameEditorByteArray(FrameEditorByteArray && rhs) = default;

  FrameEditorByteArray(const Box & rhs);
  FrameEditorByteArray(const std::vector<Box> & rhs);

  FrameEditorByteArray & operator = (const FrameEditorByteArray &) = delete;
  FrameEditorByteArray & operator = (FrameEditorByteArray &&) = default;

  std::vector<Box> ConvertToMinimalBoxes();
  std::vector<Box> ConvertToMaximalBoxes();
  std::vector<FrameEditorEdge> ConvertToEdges();

  int GetWidth() const;
  int GetHeight() const;
  Vector2 GetSize() const;

  void AddBox(const Box & box);
  void RemoveBox(const Box & box);

  void OffsetEdge(FrameEditorEdge & edge, int offset, Optional<Box> & box);

  static Vector2 GetOffsetForEdgeType(FrameEditorEdgeType type);
  static int GetOffsetForEdgeMove(FrameEditorEdgeType type, const Vector2 & start, const Vector2 & end);

private:
  Vector2 m_Origin;
  Vector2 m_Size;
  std::vector<uint8_t> m_Data;
};

