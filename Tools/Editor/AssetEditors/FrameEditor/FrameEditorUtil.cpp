
#include "Foundation/Math/Util.h"

#include "AssetEditors/FrameEditor/FrameEditorUtil.h"


FrameEditorByteArray::FrameEditorByteArray(const Box & rhs)
{
  m_Origin = rhs.m_Start - Vector2(1, 1);
  m_Size = rhs.m_End - rhs.m_Start + Vector2(3, 3);

  m_Data = std::vector<uint8_t>(m_Size.x * m_Size.y);

  for (int y = 1; y < m_Size.y - 1; y++)
  {
    for (int x = 1; x < m_Size.x - 1; x++)
    {
      m_Data[y * m_Size.x + x] = 1;
    }
  }
}

FrameEditorByteArray::FrameEditorByteArray(const std::vector<Box> & rhs)
{
  if (rhs.size() == 0)
  {
    m_Origin = {};
    m_Size = Vector2(2, 2);
    m_Data = std::vector<uint8_t>(4);
    return;
  }

  Box b = rhs[0];
  for (std::size_t index = 1, end = rhs.size(); index < end; ++index)
  {
    BoxUnionInPlace(b, rhs[index]);
  }

  m_Origin = b.m_Start - Vector2(1, 1);
  m_Size = b.m_End - b.m_Start + Vector2(3, 3);

  m_Data = std::vector<uint8_t>(m_Size.x * m_Size.y);

  for (auto & box : rhs)
  {
    auto size = box.Size() + Vector2(1, 1);
    auto offset = box.m_Start - m_Origin;

    for (int y = offset.y, y_size = size.y; y_size > 0; y++, y_size--)
    {
      for (int x = offset.x, x_size = size.x; x_size > 0; x++, x_size--)
      {
        m_Data[y * m_Size.x + x] = 1;
      }
    }
  }
}

std::vector<Box> FrameEditorByteArray::ConvertToMinimalBoxes()
{
  auto marked = std::vector<uint8_t>(m_Size.x * m_Size.y);
  std::vector<Box> boxes;

  for (int y = 0; y < m_Size.y; y++)
  {
    for (int x = 0; x < m_Size.x; x++)
    {
      if (m_Data[y * m_Size.x + x] && marked[y * m_Size.x + x] == 0)
      {
        int width = 1;
        int height = 1;
        for (int bx = x + 1; bx < m_Size.x; bx++)
        {
          if (m_Data[y * m_Size.x + bx] && marked[y * m_Size.x + bx] == 0)
          {
            marked[y * m_Size.x + bx] = 1;
            width++;
          }
          else
          {
            break;
          }
        }

        for (int by = y + 1; by < m_Size.y; by++)
        {
          bool row_ok = true;
          for (int bx = x, b_end = width; b_end > 0; bx++, b_end--)
          {
            if (m_Data[by * m_Size.x + bx] == 0 || marked[by * m_Size.x + bx] == 1)
            {
              row_ok = false;
              break;
            }
          }

          if (row_ok)
          {
            for (int bx = x, b_end = width; b_end > 0; bx++, b_end--)
            {
              marked[by * m_Size.x + bx] = 1;
            }

            height++;
          }
          else
          {
            break;
          }
        }

        Box b;
        b.m_Start = Vector2(x, y) + m_Origin;
        b.m_End = b.m_Start + Vector2(width, height) - Vector2(1, 1);
        boxes.push_back(b);
      }
    }
  }

  return boxes;
}

std::vector<Box> FrameEditorByteArray::ConvertToMaximalBoxes()
{
  auto marked = std::vector<uint8_t>(m_Size.x * m_Size.y);
  std::vector<Box> boxes;

  for (int y = 0; y < m_Size.y; y++)
  {
    for (int x = 0; x < m_Size.x; x++)
    {
      if (m_Data[y * m_Size.x + x] && marked[y * m_Size.x + x] == 0)
      {
        int width = 1;
        int height = 1;
        for (int bx = x + 1; bx < m_Size.x; bx++)
        {
          if (m_Data[y * m_Size.x + bx])
          {
            marked[y * m_Size.x + bx] = 1;
            width++;
          }
          else
          {
            break;
          }
        }

        for (int by = y + 1; by < m_Size.y; by++)
        {
          bool row_ok = true;
          for (int bx = x, b_end = width; b_end > 0; bx++, b_end--)
          {
            if (m_Data[by * m_Size.x + bx] == 0)
            {
              row_ok = false;
              break;
            }
          }

          if (row_ok)
          {
            for (int bx = x, b_end = width; b_end > 0; bx++, b_end--)
            {
              marked[by * m_Size.x + bx] = 1;
            }

            height++;
          }
          else
          {
            break;
          }
        }

        Box b;
        b.m_Start = Vector2(x, y) + m_Origin;
        b.m_End = b.m_Start + Vector2(width, height) - Vector2(1, 1);
        boxes.push_back(b);
      }
    }
  }

  return boxes;
}

std::vector<FrameEditorEdge> FrameEditorByteArray::ConvertToEdges()
{
  auto marked = std::vector<uint8_t>(m_Size.x * m_Size.y);
  std::vector<FrameEditorEdge> edges;

  for (int y = 1; y < m_Size.y - 1; y++)
  {
    for (int x = 1; x < m_Size.x - 1; x++)
    {
      int this_index = y * m_Size.x + x;
      int top_index = (y - 1) * m_Size.x + x;
      int bot_index = (y + 1) * m_Size.x + x;
      int left_index = y * m_Size.x + (x - 1);
      int right_index = y * m_Size.x + (x + 1);

      if ((marked[this_index] & 0x1) == 0 && m_Data[this_index] == 1 && m_Data[bot_index] == 0)
      {
        int width = 0;
        for (int ex = x; ex < m_Size.x - 1; ex++)
        {
          int edge_index = y * m_Size.x + ex;
          int check_index = (y + 1) * m_Size.x + ex;

          if (m_Data[edge_index] == 1 && m_Data[check_index] == 0)
          {
            marked[edge_index] |= 0x1;
            width += 1;
          }
          else
          {
            break;
          }
        }

        edges.push_back(FrameEditorEdge{ Vector2{ x, y } + m_Origin, Vector2{ x + width, y } + m_Origin, FrameEditorEdgeType::kTop });
      }

      if ((marked[this_index] & 0x2) == 0 && m_Data[this_index] == 1 && m_Data[top_index] == 0)
      {
        int width = 0;
        for (int ex = x; ex < m_Size.x - 1; ex++)
        {
          int edge_index = y * m_Size.x + ex;
          int check_index = (y - 1) * m_Size.x + ex;

          if (m_Data[edge_index] == 1 && m_Data[check_index] == 0)
          {
            marked[edge_index] |= 0x2;
            width += 1;
          }
          else
          {
            break;
          }
        }

        edges.push_back(FrameEditorEdge{ Vector2{x, y} + m_Origin, Vector2{x + width, y} + m_Origin, FrameEditorEdgeType::kBottom });
      }

      if ((marked[this_index] & 0x4) == 0 && m_Data[this_index] == 1 && m_Data[left_index] == 0)
      {
        int height = 0;
        for (int ey = y; ey < m_Size.y - 1; ey++)
        {
          int edge_index = ey * m_Size.x + x;
          int check_index = ey * m_Size.x + (x - 1);

          if (m_Data[edge_index] == 1 && m_Data[check_index] == 0)
          {
            marked[edge_index] |= 0x4;
            height += 1;
          }
          else
          {
            break;
          }
        }

        edges.push_back(FrameEditorEdge{ Vector2{ x, y } + m_Origin, Vector2{ x, y + height } + m_Origin, FrameEditorEdgeType::kLeft });
      }

      if ((marked[this_index] & 0x8) == 0 && m_Data[this_index] == 1 && m_Data[right_index] == 0)
      {
        int height = 0;
        for (int ey = y; ey < m_Size.y - 1; ey++)
        {
          int edge_index = ey * m_Size.x + x;
          int check_index = ey * m_Size.x + (x + 1);

          if (m_Data[edge_index] == 1 && m_Data[check_index] == 0)
          {
            marked[edge_index] |= 0x8;
            height += 1;
          }
          else
          {
            break;
          }
        }

        edges.push_back(FrameEditorEdge{ Vector2{ x, y } + m_Origin, Vector2{ x, y + height } + m_Origin, FrameEditorEdgeType::kRight });
      }
    }
  }

  return edges;
}

int FrameEditorByteArray::GetWidth() const
{
  return m_Size.x;
}

int FrameEditorByteArray::GetHeight() const
{
  return m_Size.y;
}

Vector2 FrameEditorByteArray::GetSize() const
{
  return m_Size;
}

void FrameEditorByteArray::AddBox(const Box & box)
{
  auto new_box = box;
  new_box.m_Start -= m_Origin;
  new_box.m_End -= m_Origin;

  if (new_box.m_Start.x < 0 || new_box.m_Start.y < 0 || new_box.m_End.x >= m_Size.x || new_box.m_End.y >= m_Size.y)
  {
    auto min_boxes = ConvertToMinimalBoxes();
    min_boxes.push_back(box);

    *this = FrameEditorByteArray(min_boxes);
    return;
  }

  for (int y = new_box.m_Start.y, end_y = new_box.m_End.y; y <= end_y; ++y)
  {
    for (int x = new_box.m_Start.x, end_x = new_box.m_End.x; x <= end_x; ++x)
    {
      m_Data[y * m_Size.x + x] = 1;
    }
  }
}

void FrameEditorByteArray::RemoveBox(const Box & box)
{
  auto new_box = box;
  new_box.m_Start -= m_Origin;
  new_box.m_End -= m_Origin;

  new_box.m_End.x = std::min(new_box.m_End.x, m_Size.x);
  new_box.m_End.y = std::min(new_box.m_End.y, m_Size.y);
  
  if (new_box.m_Start.x >= m_Size.x || new_box.m_Start.y >= m_Size.y || new_box.m_End.x < 0 || new_box.m_End.y < 0)
  {
    return;
  }

  for (int y = std::max(new_box.m_Start.y, 0), end_y = std::min(new_box.m_End.y, m_Size.y - 1); y <= end_y; ++y)
  {
    for (int x = std::max(new_box.m_Start.x, 0), end_x = std::min(new_box.m_End.x, m_Size.x - 1); x <= end_x; ++x)
    {
      m_Data[y * m_Size.x + x] = 0;
    }
  }
}

Vector2 FrameEditorByteArray::GetOffsetForEdgeType(FrameEditorEdgeType type)
{
  switch (type)
  {
  case FrameEditorEdgeType::kTop:
    return Vector2(0, 1);
  case FrameEditorEdgeType::kLeft:
    return Vector2(0, 0);
  case FrameEditorEdgeType::kBottom:
    return Vector2(0, 0);
  case FrameEditorEdgeType::kRight:
    return Vector2(1, 0);
  default:
    return Vector2(0, 0);
  }
}

int FrameEditorByteArray::GetOffsetForEdgeMove(FrameEditorEdgeType type, const Vector2 & start, const Vector2 & end)
{
  if (type == FrameEditorEdgeType::kTop)
  {
    return end.y - start.y;
  }
  else if (type == FrameEditorEdgeType::kBottom)
  {
    return start.y - end.y;
  }
  else if (type == FrameEditorEdgeType::kLeft)
  {
    return start.x - end.x;
  }
  else if (type == FrameEditorEdgeType::kRight)
  {
    return end.x - start.x;
  }

  return 0;
}

void FrameEditorByteArray::OffsetEdge(FrameEditorEdge & edge, int offset, Optional<Box> & box)
{
  if (offset == 0)
  {
    return;
  }

  Vector2 offset_direction;
  Vector2 check_direction;
  if (edge.m_Type == FrameEditorEdgeType::kTop)
  {
    offset_direction = Vector2(0, 1);
    check_direction = Vector2(1, 0);
  }
  else if (edge.m_Type == FrameEditorEdgeType::kBottom)
  {
    offset_direction = Vector2(0, -1);
    check_direction = Vector2(1, 0);
  }
  else if (edge.m_Type == FrameEditorEdgeType::kLeft)
  {
    offset_direction = Vector2(-1, 0);
    check_direction = Vector2(0, 1);
  }
  else if (edge.m_Type == FrameEditorEdgeType::kRight)
  {
    offset_direction = Vector2(1, 0);
    check_direction = Vector2(0, 1);
  }

  if (offset >= 0)
  {
    auto start_box = Box::FromPoints(edge.m_P1, edge.m_P2);
    start_box.m_End -= check_direction;

    edge.m_P1 += offset_direction * offset;
    edge.m_P2 += offset_direction * offset;

    auto end_box = Box::FromPoints(edge.m_P1, edge.m_P2);
    end_box.m_End -= check_direction;

    box = BoxUnion(start_box, end_box);
    return;
  }
  else
  {
    auto edge_offset = edge.m_P2 - edge.m_P1;
    auto len = ManhattanLength(edge_offset);

    offset *= -1;
    while (offset > 0)
    {
      auto point = edge.m_P1 - m_Origin;
      auto test = point - offset_direction;

      bool all_good = true;

      auto test_point = test;
      for (int v = len; v > 0; v--, test_point += check_direction)
      {
        if(test_point.x < 0 || test_point.x >= m_Size.x ||
           test_point.y < 0 || test_point.y >= m_Size.y)
        {
          all_good = false;
          break;
        }

        int this_index = test_point.y * m_Size.x + test_point.x;
        if (m_Data[this_index] != 1)
        {
          all_good = false;
          break;
        }
      }

      if (all_good)
      {
        auto write_point = point;
        for (int v = len; v > 0; v--, write_point += check_direction)
        {
          int this_index = write_point.y * m_Size.x + write_point.x;
          m_Data[this_index] = 0;
        }
      }
      else
      {
        break;
      }

      edge.m_P1 -= offset_direction;
      edge.m_P2 -= offset_direction;
      offset--;
    }

    return;
  }

}
