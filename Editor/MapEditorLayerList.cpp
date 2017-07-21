
#include <QMenu>
#include <QKeyEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionFrame>
#include <QMouseEvent>

#include <StormRefl/StormReflJson.h>
#include <StormData/StormDataJson.h>
#include <sb/vector.h>

#include "Runtime/Map/MapDef.refl.meta.h"
#include "Runtime/Map/MapTileJson.h"

#include "MapEditor.h"
#include "MapEditorLayerList.h"
#include "MapEditorViewer.h"


struct MapEditorLayerListElement
{
  MapEditorLayerList * m_LayerList;
  MapEditorLayerSelection m_LayerInfo;

  ~MapEditorLayerListElement()
  {
    m_LayerList->LayerRemoved(m_LayerInfo);
  }
};

struct MapEditorLayerListEntityData : public MapEditorLayerListElement
{
  Optional<DocumentSubValueListMirror> m_SubValueList;
};


MapEditorLayerList::MapEditorLayerList(NotNullPtr<MapEditor> editor, MapDef & map, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Map(map),
  m_ScrollBar(std::make_unique<QScrollBar>(this)),
  m_SelectNewLayers(false),
  m_ManualTileLayerMirror(m_Editor),
  m_EntityLayerMirror(m_Editor),
  m_ParalaxLayerMirror(m_Editor),
  m_EffectLayerMirror(m_Editor),
  m_VolumeLayerMirror(m_Editor),
  m_PathLayerMirror(m_Editor)
{
  setFocusPolicy(Qt::ClickFocus);
  setMaximumWidth(220);

  connect(m_ScrollBar.get(), &QScrollBar::valueChanged, this, &MapEditorLayerList::scrollChanged);

  CreateMirrorList<RMergeList, MapManualTileLayer, RString, MapEditorLayerListElement, MapEditorLayerList>(
    m_ManualTileLayerMirror,
    m_Map.m_ManualTileLayers,
    ".m_Name",
    [](MapManualTileLayer & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
        { 
          label.m_LayerList = ptr;
          label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kManualTileLayer, index };
          ptr->UpdateScroll();

          if(ptr->m_SelectNewLayers)
          {
            ptr->m_Editor->ChangeLayerSelection(label.m_LayerInfo);
          }
        },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
  );

  CreateMirrorList<RMergeList, MapEntityLayer, RString, MapEditorLayerListEntityData, MapEditorLayerList>(
    m_EntityLayerMirror,
    m_Map.m_EntityLayers,
    ".m_Name",
    [](MapEntityLayer & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListEntityData & data, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
        { 
          data.m_LayerList = ptr;
          data.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kEntityLayer, index };

          data.m_SubValueList.Emplace(ptr->m_Editor);
          CreateMirrorList<RMergeList, MapEntity, RString, MapEditorLayerListElement, MapEditorLayerListEntityData>(
            data.m_SubValueList.Value(),
            ptr->m_Map.m_EntityLayers[index].m_Entities,
            [=]() -> void * { auto list = ptr->m_Map.m_EntityLayers.TryGet(index); return list ? &list->m_Entities : nullptr; },
            ".m_Name",
            [](MapEntity & elem, NotNullPtr<MapEditorLayerListEntityData>) -> RString & { return elem.m_Name; },
            [](RString & name, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerListEntityData> ptr)
                { 
                  label.m_LayerList = ptr->m_LayerList;
                  label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kEntity, ptr->m_LayerInfo.m_Index, index };
                  ptr->m_LayerList->UpdateScroll();
                },
            [](RString & name, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerListEntityData> ptr) { ptr->m_LayerList->repaint(); },
            &data
          );

          ptr->UpdateScroll();

          if (ptr->m_SelectNewLayers)
          {
            ptr->m_Editor->ChangeLayerSelection(data.m_LayerInfo);
          }
        },
    [](RString & name, MapEditorLayerListEntityData & data, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
  );

  CreateMirrorList<RMergeList, MapParalaxLayer, RString, MapEditorLayerListElement, MapEditorLayerList>(
    m_ParalaxLayerMirror,
    m_Map.m_ParalaxLayers,
    ".m_Name",
    [](MapParalaxLayer & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
      {
        label.m_LayerList = ptr;
        label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kParalaxLayer, index };
        ptr->UpdateScroll();

        if (ptr->m_SelectNewLayers)
        {
          ptr->m_Editor->ChangeLayerSelection(label.m_LayerInfo);
        }
      },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
    );

  CreateMirrorList<RMergeList, MapEffectLayer, RString, MapEditorLayerListElement, MapEditorLayerList>(
    m_EffectLayerMirror,
    m_Map.m_EffectLayers,
    ".m_Name",
    [](MapEffectLayer & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
      {
        label.m_LayerList = ptr;
        label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kEffectLayer, index };
        ptr->UpdateScroll();

        if (ptr->m_SelectNewLayers)
        {
          ptr->m_Editor->ChangeLayerSelection(label.m_LayerInfo);
        }
      },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
    );

  CreateMirrorList<RMergeList, MapPath, RString, MapEditorLayerListElement, MapEditorLayerList>(
    m_PathLayerMirror,
    m_Map.m_Paths,
    ".m_Name",
    [](MapPath & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
      {
        label.m_LayerList = ptr;
        label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kPath, index };
        ptr->UpdateScroll();

        if (ptr->m_SelectNewLayers)
        {
          ptr->m_Editor->ChangeLayerSelection(label.m_LayerInfo);
        }
      },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
    );

  CreateMirrorList<RMergeList, MapVolume, RString, MapEditorLayerListElement, MapEditorLayerList>(
    m_VolumeLayerMirror,
    m_Map.m_Volumes,
    ".m_Name",
    [](MapVolume & elem, NotNullPtr<MapEditorLayerList>) -> RString & { return elem.m_Name; },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr)
      {
        label.m_LayerList = ptr;
        label.m_LayerInfo = MapEditorLayerSelection{ MapEditorLayerItemType::kVolume, index };
        ptr->UpdateScroll();

        if (ptr->m_SelectNewLayers)
        {
          ptr->m_Editor->ChangeLayerSelection(label.m_LayerInfo);
        }
      },
    [](RString & filename, MapEditorLayerListElement & label, std::size_t index, NotNullPtr<MapEditorLayerList> ptr) { ptr->repaint(); },
    this
    );

  m_SelectNewLayers = true;

  UpdateScroll();
}

void MapEditorLayerList::ChangeLayerSelection(const MapEditorLayerSelection & layer)
{
  m_Selection = layer;
  repaint();
}

void MapEditorLayerList::ClearLayerSelection()
{
  m_Selection.Clear();
  repaint();
}

void MapEditorLayerList::ToggleSelectedLayer()
{
  if (m_Selection)
  {
    bool hidden = IsLayerHidden(m_Selection.Value());
    SetHideLayer(m_Selection.Value(), !hidden);
  }
}

bool MapEditorLayerList::IsLayerHidden(const MapEditorLayerSelection & layer)
{
  switch (layer.m_Type)
  {
  case MapEditorLayerItemType::kManualTileLayer:
    {
      auto layer_ptr = m_Editor->GetManualTileManager().GetLayerManager(layer.m_Index);
      return layer_ptr ? layer_ptr->IsHidden() : false;
    }
  case MapEditorLayerItemType::kEntityLayer:
    {
      auto layer_ptr = m_Editor->GetEntityManager().GetLayerManager(layer.m_Index);
      return layer_ptr ? layer_ptr->IsHidden() : false;
    }
  case MapEditorLayerItemType::kParalaxLayer:
    {
      auto layer_ptr = m_Editor->GetParalaxManager().GetLayerManager(layer.m_Index);
      return layer_ptr ? layer_ptr->IsHidden() : false;
    }
  case MapEditorLayerItemType::kEffectLayer:
    {
      auto layer_ptr = m_Editor->GetEffectManager().GetLayerManager(layer.m_Index);
      return layer_ptr ? layer_ptr->IsHidden() : false;
    }
  }

  return false;
}

void MapEditorLayerList::SetHideLayer(const MapEditorLayerSelection & layer, bool hidden)
{
  switch (layer.m_Type)
  {
  case MapEditorLayerItemType::kManualTileLayer:
    {
      auto layer_ptr = m_Editor->GetManualTileManager().GetLayerManager(layer.m_Index);
      if (layer_ptr) layer_ptr->SetHidden(hidden);
      break;
    }
  case MapEditorLayerItemType::kEntityLayer:
    {
      auto layer_ptr = m_Editor->GetEntityManager().GetLayerManager(layer.m_Index);
      if (layer_ptr) layer_ptr->SetHidden(hidden);
      break;
    }
  case MapEditorLayerItemType::kParalaxLayer:
    {
      auto layer_ptr = m_Editor->GetParalaxManager().GetLayerManager(layer.m_Index);
      if (layer_ptr) layer_ptr->SetHidden(hidden);
      break;
    }
  case MapEditorLayerItemType::kEffectLayer:
    {
      auto layer_ptr = m_Editor->GetEffectManager().GetLayerManager(layer.m_Index);
      if (layer_ptr) layer_ptr->SetHidden(hidden);
      break;
    }
  }
}

void MapEditorLayerList::DeleteLayer(const MapEditorLayerSelection & layer)
{
  switch (layer.m_Type)
  {
  case MapEditorLayerItemType::kManualTileLayer:
    {
      m_Map.m_ManualTileLayers.RemoveAt(layer.m_Index);
      break;
    }
  case MapEditorLayerItemType::kEntityLayer:
    {
      m_Map.m_EntityLayers.RemoveAt(layer.m_Index);
      break;
    }
  case MapEditorLayerItemType::kEntity:
    {
      if(m_Map.m_EntityLayers.HasAt(layer.m_Index))
      {
        m_Map.m_EntityLayers[layer.m_Index].m_Entities.RemoveAt(layer.m_SubIndex);
      }
      break;
    }
  case MapEditorLayerItemType::kParalaxLayer:
    {
      m_Map.m_ParalaxLayers.RemoveAt(layer.m_Index);
      break;
    }
  case MapEditorLayerItemType::kEffectLayer:
    {
      m_Map.m_EffectLayers.RemoveAt(layer.m_Index);
      break;
    }
  case MapEditorLayerItemType::kVolume:
    {
      m_Map.m_Volumes.RemoveAt(layer.m_Index);
      break;
    }
  case MapEditorLayerItemType::kPath:
    {
      m_Map.m_Paths.RemoveAt(layer.m_Index);
      break;
    }
  }
}

int MapEditorLayerList::VisitElements(Delegate<bool, const MapEditorLayerSelection &, int> && visitor)
{
  int y_pos = 0;
  int layer_height = fontMetrics().height();

  MapEditorLayerSelection elem = {};
  elem.m_Type = MapEditorLayerItemType::kManualTileLayerParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_ManualTileParentExpanded)
  {
    for (auto layer : m_Map.m_ManualTileLayers)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kManualTileLayer;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;
    }
  }

  elem.m_Type = MapEditorLayerItemType::kEntityLayerParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_EntityParentExpanded)
  {
    for (auto layer : m_Map.m_EntityLayers)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kEntityLayer;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;

      auto layer_ptr = m_Editor->GetEntityManager().GetLayerManager(layer.first);
      if (layer_ptr && layer_ptr->IsCollapsed() == false)
      {
        for (auto entity : layer.second.m_Entities)
        {
          MapEditorLayerSelection elem = {};
          elem.m_Type = MapEditorLayerItemType::kEntity;
          elem.m_Index = layer.first;
          elem.m_SubIndex = entity.first;

          if (visitor(elem, y_pos) == false)
          {
            return y_pos;
          }

          y_pos += layer_height;
        }
      }
    }
  }

  elem = {};
  elem.m_Type = MapEditorLayerItemType::kParalaxLayerParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_ParalaxParentExpanded)
  {
    for (auto layer : m_Map.m_ParalaxLayers)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kParalaxLayer;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;
    }
  }

  elem = {};
  elem.m_Type = MapEditorLayerItemType::kEffectLayerParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_EffectParentExpanded)
  {
    for (auto layer : m_Map.m_EffectLayers)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kEffectLayer;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;
    }
  }

  elem = {};
  elem.m_Type = MapEditorLayerItemType::kVolumeParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_VolumeExpanded)
  {
    elem = {};
    elem.m_Type = MapEditorLayerItemType::kCreateVolume;
    if (visitor(elem, y_pos) == false)
    {
      return y_pos;
    }

    y_pos += layer_height;

    for (auto layer : m_Map.m_Volumes)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kVolume;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;
    }
  }

  elem = {};
  elem.m_Type = MapEditorLayerItemType::kPathParent;
  if (visitor(elem, y_pos) == false)
  {
    return y_pos;
  }

  y_pos += layer_height;

  if (m_PathExpanded)
  {
    elem = {};
    elem.m_Type = MapEditorLayerItemType::kCreatePath;
    if (visitor(elem, y_pos) == false)
    {
      return y_pos;
    }

    y_pos += layer_height;

    for (auto layer : m_Map.m_Paths)
    {
      MapEditorLayerSelection elem = {};
      elem.m_Type = MapEditorLayerItemType::kPath;
      elem.m_Index = layer.first;

      if (visitor(elem, y_pos) == false)
      {
        return y_pos;
      }

      y_pos += layer_height;
    }
  }

  return y_pos;
}

Optional<MapEditorLayerSelection> MapEditorLayerList::GetLayerForPosition(int y)
{
  Optional<MapEditorLayerSelection> selection;
  VisitElements([this, &selection, y](const MapEditorLayerSelection & layer, int y_pos) -> bool
  {
    int layer_height = fontMetrics().height();

    y_pos -= m_ScrollBar->value();
    if (y < y_pos + layer_height)
    {
      selection = layer;
      return false;
    }
    else
    {
      return true;
    }
  });

  return selection;
}

void MapEditorLayerList::LayerRemoved(const MapEditorLayerSelection & layer)
{
  if (m_Selection && layer.m_Type == m_Selection->m_Type && layer.m_Index == m_Selection->m_Index && layer.m_SubIndex == m_Selection->m_SubIndex)
  {
    m_Editor->ClearLayerSelection();
  }

  UpdateScroll();
}

void MapEditorLayerList::UpdateScroll()
{
  int content_height = VisitElements([](const MapEditorLayerSelection &, int) { return true; });

  if (height() >= content_height)
  {
    m_ScrollBar->hide();
    m_ScrollBar->setMaximum(0);
  }
  else
  {
    m_ScrollBar->show();
    m_ScrollBar->setMaximum(content_height - height());
    m_ScrollBar->setPageStep(height());
  }

  repaint();
}

void MapEditorLayerList::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  p.fillRect(0, 0, width(), height(), Qt::white);

  QStyleOptionFrame frame_option;
  frame_option.rect = QRect(0, 0, width() - 1, height() - 1);

  style()->drawPrimitive(QStyle::PE_Frame, &frame_option, &p, this);

  int layer_height = fontMetrics().height();

  VisitElements([&](const MapEditorLayerSelection & layer, int y_pos) 
    {
      y_pos -= m_ScrollBar->value();

      if(m_Selection && layer.m_Type == m_Selection->m_Type && layer.m_Index == m_Selection->m_Index && layer.m_SubIndex == m_Selection->m_SubIndex)
      {
        p.fillRect(0, y_pos, width() - 1, layer_height, Qt::darkBlue);
        p.setPen(Qt::white);
      }
      else
      {
        p.setPen(Qt::black);
      }

      QFont font = p.font();
      if (IsLayerHidden(layer))
      {
        font.setItalic(true);
      }
      else
      {
        font.setItalic(false);
      }

      p.setFont(font);

      switch (layer.m_Type)
      {
      case MapEditorLayerItemType::kManualTileLayerParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_ManualTileParentExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Manual Tile Layers");
          break;
        }
      case MapEditorLayerItemType::kManualTileLayer:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, m_Map.m_ManualTileLayers[layer.m_Index].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kEntityLayerParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_EntityParentExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Entity Layers");
          break;
        }
      case MapEditorLayerItemType::kEntityLayer:
        {
          auto layer_ptr = m_Editor->GetEntityManager().GetLayerManager(layer.m_Index);

          QStyleOption option;
          option.rect = QRect(layer_height + 5, y_pos, layer_height, layer_height);
          style()->drawPrimitive((layer_ptr && layer_ptr->IsCollapsed() == false) ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height * 2 + 7, y_pos, width(), height(), 0, m_Map.m_EntityLayers[layer.m_Index].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kEntity:
        {
          p.drawText(layer_height * 2 + 17, y_pos, width(), height(), 0, m_Map.m_EntityLayers[layer.m_Index].m_Entities[layer.m_SubIndex].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kParalaxLayerParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_ParalaxParentExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Paralax Layers");
          break;
        }
      case MapEditorLayerItemType::kParalaxLayer:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, m_Map.m_ParalaxLayers[layer.m_Index].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kEffectLayerParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_EffectParentExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Effect Layers");
          break;
        }
      case MapEditorLayerItemType::kEffectLayer:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, m_Map.m_EffectLayers[layer.m_Index].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kVolumeParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_VolumeExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Volumes");
          break;
        }
      case MapEditorLayerItemType::kCreateVolume:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, "Create Volume");
          break;
        }
      case MapEditorLayerItemType::kVolume:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, m_Map.m_Volumes[layer.m_Index].m_Name.data());
          break;
        }
      case MapEditorLayerItemType::kPathParent:
        {
          QStyleOption option;
          option.rect = QRect(2, y_pos, layer_height, layer_height);
          style()->drawPrimitive(m_PathExpanded ? QStyle::PE_IndicatorArrowDown : QStyle::PE_IndicatorArrowRight, &option, &p, this);
          p.drawText(layer_height + 2, y_pos, width(), height(), 0, "Paths");
          break;
        }
      case MapEditorLayerItemType::kCreatePath:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, "Create Path");
          break;
        }
      case MapEditorLayerItemType::kPath:
        {
          p.drawText(layer_height + 10, y_pos, width(), height(), 0, m_Map.m_Paths[layer.m_Index].m_Name.data());
          break;
        }

      }

      return true;
    });
}

void MapEditorLayerList::resizeEvent(QResizeEvent * ev)
{
  int scroll_width = m_ScrollBar->sizeHint().width();
  m_ScrollBar->setGeometry(width() - scroll_width - 2, 1, scroll_width, height() - 3);

  UpdateScroll();
}

void MapEditorLayerList::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_H)
  {
    ToggleSelectedLayer();
    repaint();

    return;
  }

  if (event->key() == Qt::Key_Delete && m_Selection)
  {
    DeleteLayer(m_Selection.Value());
  }
}

void MapEditorLayerList::mousePressEvent(QMouseEvent * ev)
{
  auto selection = GetLayerForPosition(ev->y());
  if (selection == false)
  {
    return;
  }

  if (ev->button() == Qt::LeftButton)
  {
    switch (selection->m_Type)
    {
    case MapEditorLayerItemType::kManualTileLayerParent:
      if (ev->x() < 15)
      {
        m_ManualTileParentExpanded = !m_ManualTileParentExpanded;
      }
      break;

    case MapEditorLayerItemType::kEntityLayerParent:
      if (ev->x() < 15)
      {
        m_EntityParentExpanded = !m_EntityParentExpanded;
      }
      break;

    case MapEditorLayerItemType::kEntityLayer:
      if (ev->x() < 30)
      {
        auto layer_ptr = m_Editor->GetEntityManager().GetLayerManager(selection->m_Index);
        if (layer_ptr)
        {
          layer_ptr->ToggleColapsed();
        }
      }
      break;

    case MapEditorLayerItemType::kParalaxLayerParent:
      if (ev->x() < 15)
      {
        m_ParalaxParentExpanded = !m_ParalaxParentExpanded;
      }
      break;

    case MapEditorLayerItemType::kEffectLayerParent:
      if (ev->x() < 15)
      {
        m_EffectParentExpanded = !m_EffectParentExpanded;
      }
      break;

    case MapEditorLayerItemType::kVolumeParent:
      if (ev->x() < 15)
      {
        m_VolumeExpanded = !m_VolumeExpanded;
      }
      break;

    case MapEditorLayerItemType::kPathParent:
      if (ev->x() < 15)
      {
        m_PathExpanded = !m_PathExpanded;
      }
      break;
    }

    m_Editor->ChangeLayerSelection(selection.Value());
  }
  else if(ev->button() == Qt::RightButton)
  {
    switch (selection->m_Type)
    {
    case MapEditorLayerItemType::kManualTileLayerParent:
      {
        QMenu menu(this);
        connect(menu.addAction("Add"), &QAction::triggered, this, &MapEditorLayerList::addManualTileLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kManualTileLayer:
      {
        QMenu menu(this);
        connect(menu.addAction("Remove"), &QAction::triggered, this, &MapEditorLayerList::removeManualTileLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kEntityLayerParent:
      {
        QMenu menu(this);
        connect(menu.addAction("Add"), &QAction::triggered, this, &MapEditorLayerList::addEntityLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kParalaxLayerParent:
      {
        QMenu menu(this);
        connect(menu.addAction("Add"), &QAction::triggered, this, &MapEditorLayerList::addParalaxLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kEffectLayerParent:
      {
        QMenu menu(this);
        connect(menu.addAction("Add"), &QAction::triggered, this, &MapEditorLayerList::addEffectLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kEntityLayer:
      {
        QMenu menu(this);
        connect(menu.addAction("Remove"), &QAction::triggered, this, &MapEditorLayerList::removeEntityLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kParalaxLayer:
      {
        QMenu menu(this);
        connect(menu.addAction("Remove"), &QAction::triggered, this, &MapEditorLayerList::removeParalaxLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    case MapEditorLayerItemType::kEffectLayer:
      {
        QMenu menu(this);
        connect(menu.addAction("Remove"), &QAction::triggered, this, &MapEditorLayerList::removeEffectLayer);
        menu.exec(mapToGlobal(ev->pos()));
        break;
      }
    }
  }
}

void MapEditorLayerList::scrollChanged()
{
  repaint();
}

void MapEditorLayerList::addManualTileLayer()
{
  auto file_name = m_Editor->GetFileNameForAssetType("tilesheet");
  if (!file_name)
  {
    return;
  }

  MapManualTileLayer tile_layer;
  tile_layer.m_Name = "Tile Layer";
  tile_layer.m_TileSheet = file_name.Value();

  m_Map.m_ManualTileLayers.EmplaceBack(std::move(tile_layer));
}

void MapEditorLayerList::removeManualTileLayer()
{
  if (m_Selection == false)
  {
    return;
  }

  if (m_Selection->m_Type != MapEditorLayerItemType::kManualTileLayer)
  {
    return;
  }

  m_Map.m_ManualTileLayers.RemoveAt(m_Selection->m_Index);
}

void MapEditorLayerList::addEntityLayer()
{
  MapEntityLayer entity_layer;
  entity_layer.m_Name = "Entity Layer";

  m_Map.m_EntityLayers.EmplaceBack(std::move(entity_layer));
}

void MapEditorLayerList::removeEntityLayer()
{
  if (m_Selection == false)
  {
    return;
  }

  if (m_Selection->m_Type != MapEditorLayerItemType::kEntityLayer)
  {
    return;
  }

  m_Map.m_EntityLayers.RemoveAt(m_Selection->m_Index);
}

void MapEditorLayerList::addParalaxLayer()
{
  auto file_name = m_Editor->GetFileNameForAssetType("image");
  if (!file_name)
  {
    return;
  }

  MapParalaxLayer paralax_layer;
  paralax_layer.m_Name = "Paralax Layer";
  paralax_layer.m_Image = file_name.Value();

  m_Map.m_ParalaxLayers.EmplaceBack(std::move(paralax_layer));
}

void MapEditorLayerList::removeParalaxLayer()
{
  if (m_Selection == false)
  {
    return;
  }

  if (m_Selection->m_Type != MapEditorLayerItemType::kParalaxLayer)
  {
    return;
  }

  m_Map.m_ParalaxLayers.RemoveAt(m_Selection->m_Index);
}

void MapEditorLayerList::addEffectLayer()
{
  MapEffectLayer effect_layer;
  effect_layer.m_Name = "Effect Layer";

  m_Map.m_EffectLayers.EmplaceBack(std::move(effect_layer));
}

void MapEditorLayerList::removeEffectLayer()
{
  if (m_Selection == false)
  {
    return;
  }

  if (m_Selection->m_Type != MapEditorLayerItemType::kEffectLayer)
  {
    return;
  }

  m_Map.m_EffectLayers.RemoveAt(m_Selection->m_Index);
}
