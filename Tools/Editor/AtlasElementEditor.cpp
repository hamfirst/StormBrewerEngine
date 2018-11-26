
#include <QPainter>
#include <QWheelEvent>
#include <QApplication>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "StormData/StormDataPath.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Atlas/AtlasEngineData.h"

#include "Foundation/Math/Util.h"

#include "AtlasElementEditor.h"
#include "AtlasTextureLoadList.h"
#include "AtlasEditor.h"
#include "DrawUtil.h"

struct ProxyPoint
{
  RInt & x;
  RInt & y;

  int xb;
  int yb;

  bool x_modify;
  bool y_modify;

  bool x_reverse;
  bool y_reverse;

  int GetX() const
  {
    return xb + (x_reverse ? -x : (int)x);
  }

  int GetY() const
  {
    return yb + (y_reverse ? -y : (int)y);
  }
};

AtlasElementEditor::AtlasElementEditor(
        NotNullPtr<AtlasEditor> editor,
        AtlasDef & atlas,
        AtlasTextureLoadList & texture_access,
        QWidget * parent) :
        GeometryEditorBase(parent),
        m_Editor(editor),
        m_Atlas(atlas),
        m_TextureAccess(texture_access),
        m_LocalChange(false),
        m_SelectedElementIndex(-1)
{
  RefreshWatcher();
}

void AtlasElementEditor::SetSelectedElement(int elem_index)
{
  m_SelectedElementIndex = elem_index;
  RefreshWatcher();
}

void AtlasElementEditor::HandleDataUpdate()
{
  if (m_LocalChange)
  {
    return;
  }

  RefreshWatcher();
  if (m_Dragging)
  {
    StopDrawing();
  }

  repaint();
}

void AtlasElementEditor::RefreshWatcher()
{
  auto elem_ptr = m_Atlas.m_Elements.TryGet(m_SelectedElementIndex);
  if(elem_ptr == nullptr)
  {
    m_Watcher.Clear();
    return;
  }

  m_Watcher.Emplace(m_Editor);
  m_Watcher->SetPath(StormDataGetPath(*elem_ptr).data(), true, true, [this, index=m_SelectedElementIndex] { return m_Atlas.m_Elements.HasAt(index); });
  m_Watcher->SetChangeCallback([this](const ReflectionChangeNotification &) { HandleDataUpdate(); });
  m_Watcher->SetParentChangeCallback([this] { HandleDataUpdate(); });
  m_Watcher->SetChildChangeCallback([this] { HandleDataUpdate(); });
}

void AtlasElementEditor::WriteData(AtlasDefElementPosition & data)
{
  auto elem_ptr = m_Atlas.m_Elements.TryGet(m_SelectedElementIndex);
  if(elem_ptr == nullptr)
  {
    return;
  }

  m_LocalChange = true;
  elem_ptr->m_Data = data;
  m_LocalChange = false;

  repaint();
}

Optional<AtlasDefElementPosition> AtlasElementEditor::GetPreviewData()
{
  auto elem_ptr = m_Atlas.m_Elements.TryGet(m_SelectedElementIndex);
  if(elem_ptr == nullptr)
  {
    return {};
  }

  auto data = elem_ptr->m_Data;
  if(m_PreviewPoint && m_PreviewOffset)
  {
    VisitPoints([this, data_ptr = &data](int point_index, const ProxyPoint & point)
    {
      if(m_PreviewPoint.Value() == point_index)
      {
        if(point.x_modify)
        {
          point.x += point.x_reverse ? -m_PreviewOffset->x : m_PreviewOffset->x;
        }

        if(point.y_modify)
        {
          point.y += point.y_reverse ? m_PreviewOffset->y : -m_PreviewOffset->y;
        }

        if(&point.x == &data_ptr->m_StartX)
        {
          if(data_ptr->m_StartX > data_ptr->m_EndX)
          {
            data_ptr->m_StartX = data_ptr->m_EndX;
          }
        }
        else if(&point.x == &data_ptr->m_EndX)
        {
          if(data_ptr->m_EndX < data_ptr->m_StartX)
          {
            data_ptr->m_EndX = data_ptr->m_StartX;
          }
        }

        if(&point.y == &data_ptr->m_StartY)
        {
          if(data_ptr->m_StartY > data_ptr->m_EndY)
          {
            data_ptr->m_StartY = data_ptr->m_EndY;
          }
        }
        else if(&point.y == &data_ptr->m_EndY)
        {
          if(data_ptr->m_EndY < data_ptr->m_StartY)
          {
            data_ptr->m_EndY = data_ptr->m_StartY;
          }
        }
      }
    }, &data);

    if(data.m_StartOffsetX < 0)
    {
      data.m_StartOffsetX = 0;
    }

    if(data.m_EndOffsetX < 0)
    {
      data.m_EndOffsetX = 0;
    }

    if(data.m_StartOffsetY < 0)
    {
      data.m_StartOffsetY = 0;
    }

    if(data.m_EndOffsetY < 0)
    {
      data.m_EndOffsetY = 0;
    }
  }

  return data;
}


template <typename Visitor>
void AtlasElementEditor::VisitPoints(Visitor && visitor, NotNullPtr<AtlasDefElementPosition> elem_ptr)
{
  visitor(0, ProxyPoint{ elem_ptr->m_StartX, elem_ptr->m_StartY, 0, 0, true, true, false, false });
  visitor(1, ProxyPoint{ elem_ptr->m_EndX, elem_ptr->m_StartY, 0, 0, true, true, false, false });
  visitor(2, ProxyPoint{ elem_ptr->m_StartX, elem_ptr->m_EndY, 0, 0, true, true, false, false });
  visitor(3, ProxyPoint{ elem_ptr->m_EndX, elem_ptr->m_EndY, 0, 0, true, true, false, false });

  if(elem_ptr->m_Type == AtlasDefType::k3SliceVertical ||
     elem_ptr->m_Type == AtlasDefType::k3SliceHorizontal ||
     elem_ptr->m_Type == AtlasDefType::k9Slice)
  {
    bool allow_x = elem_ptr->m_Type == AtlasDefType::k3SliceHorizontal || elem_ptr->m_Type == AtlasDefType::k9Slice;
    bool allow_y = elem_ptr->m_Type == AtlasDefType::k3SliceVertical || elem_ptr->m_Type == AtlasDefType::k9Slice;
    visitor(4, ProxyPoint{ elem_ptr->m_StartOffsetX, elem_ptr->m_StartOffsetY,
                           elem_ptr->m_StartX, elem_ptr->m_StartY, allow_x, allow_y, false, false });
    visitor(5, ProxyPoint{ elem_ptr->m_EndOffsetX, elem_ptr->m_StartOffsetY,
                           elem_ptr->m_EndX, elem_ptr->m_StartY, allow_x, allow_y, true, false });
    visitor(6, ProxyPoint{ elem_ptr->m_StartOffsetX, elem_ptr->m_EndOffsetY,
                           elem_ptr->m_StartX, elem_ptr->m_EndY, allow_x, allow_y, false, true });
    visitor(7, ProxyPoint{ elem_ptr->m_EndOffsetX, elem_ptr->m_EndOffsetY,
                           elem_ptr->m_EndX, elem_ptr->m_EndY, allow_x, allow_y, true, true });
  }
}

template <typename Visitor>
void AtlasElementEditor::VisitEdges(Visitor && visitor, NotNullPtr<AtlasDefElementPosition> elem_ptr)
{
  visitor(0, elem_ptr->m_StartX, elem_ptr->m_StartY, elem_ptr->m_EndX, elem_ptr->m_StartY);
  visitor(1, elem_ptr->m_StartX, elem_ptr->m_StartY, elem_ptr->m_StartX, elem_ptr->m_EndY);
  visitor(2, elem_ptr->m_EndX, elem_ptr->m_StartY, elem_ptr->m_EndX, elem_ptr->m_EndY);
  visitor(3, elem_ptr->m_StartX, elem_ptr->m_EndY, elem_ptr->m_EndX, elem_ptr->m_EndY);

  if(elem_ptr->m_Type == AtlasDefType::k3SliceVertical ||
     elem_ptr->m_Type == AtlasDefType::k9Slice)
  {
    visitor(4, elem_ptr->m_StartX, elem_ptr->m_StartY + elem_ptr->m_StartOffsetY, elem_ptr->m_EndX, elem_ptr->m_StartY + elem_ptr->m_StartOffsetY);
    visitor(5, elem_ptr->m_StartX, elem_ptr->m_EndY - elem_ptr->m_EndOffsetY, elem_ptr->m_EndX, elem_ptr->m_EndY - elem_ptr->m_EndOffsetY);
  }

  if(elem_ptr->m_Type == AtlasDefType::k3SliceHorizontal ||
     elem_ptr->m_Type == AtlasDefType::k9Slice)
  {
    visitor(6, elem_ptr->m_StartX + elem_ptr->m_StartOffsetX, elem_ptr->m_StartY, elem_ptr->m_StartX + elem_ptr->m_StartOffsetX, elem_ptr->m_EndY);
    visitor(7, elem_ptr->m_EndX - elem_ptr->m_EndOffsetX, elem_ptr->m_StartY, elem_ptr->m_EndX - elem_ptr->m_EndOffsetX, elem_ptr->m_EndY);
  }
}

Vector2 OrientPoint(const Vector2 & point, const Vector2 & tex_size)
{
  auto out = point;
  out.x -= tex_size.x / 2;
  out.y = tex_size.y - out.y;
  out.y -= tex_size.y / 2;
  return out;
}


void AtlasElementEditor::DrawData()
{
  auto preview_data = GetPreviewData();
  if(preview_data.IsValid() == false)
  {
    return;
  }

  auto texture = GetTexture();
  if(texture == nullptr)
  {
    return;
  }

  auto tex_size = texture->GetSize();
  VisitEdges([&](int edge_index, int sx, int sy, int ex, int ey)
  {
    DrawLine(OrientPoint(Vector2(sx, sy), tex_size), OrientPoint(Vector2(ex, ey), tex_size));
  }, &preview_data.Value());

  VisitPoints([&](int point_index, const ProxyPoint & point)
  {
    int x = point.GetX();
    int y = point.GetY();

    if(m_PreviewPoint && m_PreviewPoint.Value() == point_index)
    {
      DrawHighlightedCornerControl(OrientPoint(Vector2(x, y), tex_size));
    }
    else
    {
      DrawCornerControl(OrientPoint(Vector2(x, y), tex_size));
    }

  }, &preview_data.Value());
}

void AtlasElementEditor::DrawPreview(const Vector2 & frame_pos, bool alt, bool shift, bool ctrl)
{
  auto pos = mapFromGlobal(QCursor::pos());
  auto cursor_pos = Vector2(pos.x(), pos.y());

  auto preview_data = GetPreviewData();
  if(preview_data.IsValid() == false)
  {
    return;
  }

  auto texture = GetTexture();
  if(texture == nullptr)
  {
    return;
  }

  m_PreviewPoint.Clear();
  VisitPoints([&](int point_index, const ProxyPoint & point)
  {
    auto pos = OrientPoint(Vector2(point.GetX(), point.GetY()), texture->GetSize());
    auto screen_pos = TransformFrameToScreen(pos);
    if (ManhattanDist(screen_pos, cursor_pos) < 20)
    {
      m_PreviewPoint = point_index;
    }
  }, &preview_data.Value());

  repaint();
}

void AtlasElementEditor::DrawLeave()
{
  m_PreviewPoint.Clear();
}

bool AtlasElementEditor::DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  if(m_PreviewPoint)
  {
    auto frame_pos = TransformScreenToFrame(pos);

    m_DrawStart = frame_pos;
    m_PreviewOffset = Vector2(0, 0);
    return true;
  }

  return false;
}

void AtlasElementEditor::DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  auto frame_pos = TransformScreenToFrame(pos);
  m_PreviewOffset = frame_pos - m_DrawStart.Value();

  repaint();
}

void AtlasElementEditor::DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl)
{
  bool valid_offset = m_PreviewOffset->x != 0 || m_PreviewOffset->y != 0;
  auto preview_data = GetPreviewData();

  m_PreviewOffset.Clear();
  m_DrawStart.Clear();

  if (valid_offset)
  {
    WriteData(preview_data.Value());
  }

  repaint();
}

void AtlasElementEditor::DrawCancel()
{
  m_PreviewOffset.Clear();
  m_DrawStart.Clear();
  repaint();
}

NullOptPtr<TextureAsset> AtlasElementEditor::GetTexture()
{
  if (m_Atlas.m_Textures.HighestIndex() == -1)
  {
    return nullptr;
  }

  auto elem_ptr = m_Atlas.m_Elements.TryGet(m_SelectedElementIndex);
  if(elem_ptr == nullptr)
  {
    return nullptr;
  }

  auto texture_hash = elem_ptr->m_TextureHash;

  auto default_texture = m_Atlas.m_Textures.begin();
  std::size_t texture_index = default_texture->first;

  for (auto texture : m_Atlas.m_Textures)
  {
    if (texture_hash == crc32(texture.second.m_Filename))
    {
      texture_index = texture.first;
    }
  }

  auto texture = m_TextureAccess.GetTexture(texture_index);
  return texture;
}

