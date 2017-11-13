
#include "FrameEditorContainer.h"
#include "FrameEditorSingleBox.h"
#include "FrameEditorMultiBox.h"
#include "FrameEditorSingleLine.h"
#include "FrameEditorLowerEdge.h"

#include "StormData/StormDataJson.h"
#include "Runtime/FrameData/FrameData.refl.meta.h"


FrameEditorContainer::FrameEditorContainer(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<FrameData>> && get_frame_data,
  Delegate<NullOptPtr<FrameData>> && get_default_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def,
  QWidget * parent) :
  QDialog(parent),
  m_Getter(std::move(get_frame_data)),
  m_Default(std::move(get_default_data)),
  m_TabWidget(std::make_unique<QTabWidget>(this))
{
  setMinimumSize(500, 500);

  CreateFrameEditorTabs(editor, sprite, texture_access, m_TabWidget.get(), &m_Getter, &m_Default, frame_id, frame_data_def);
}

void FrameEditorContainer::FrameEditorContainer::CreateFrameEditorTabs(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  NotNullPtr<QTabWidget> tab_widget,
  NotNullPtr<Delegate<NullOptPtr<FrameData>>> get_frame_data,
  NullOptPtr<Delegate<NullOptPtr<FrameData>>> default_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def)
{
  for (auto & frame_data : frame_data_def)
  {
    QWidget * widget = nullptr;

    std::unique_ptr<char[]> name_copy1 = std::make_unique<char[]>(frame_data.m_Name.size() + 1);
    std::unique_ptr<char[]> name_copy2 = std::make_unique<char[]>(frame_data.m_Name.size() + 1);
    std::unique_ptr<char[]> name_copy3 = std::make_unique<char[]>(frame_data.m_Name.size() + 1);
    strncpy(name_copy1.get(), frame_data.m_Name.data(), frame_data.m_Name.size());
    strncpy(name_copy2.get(), frame_data.m_Name.data(), frame_data.m_Name.size());
    strncpy(name_copy3.get(), frame_data.m_Name.data(), frame_data.m_Name.size());

    switch (frame_data.m_Type)
    {
      case FrameDataDefType::kSingleBox:
        {
          auto getter = [get_frame_data, name = std::move(name_copy1)]() -> NullOptPtr<ROpaque<Box>>
          { 
            auto data = get_frame_data->Call(); 
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_SingleBoxData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto default_getter = [default_data, name = std::move(name_copy2)]() -> NullOptPtr<ROpaque<Box>>
          {
            if (default_data == nullptr)
            {
              return nullptr;
            }

            auto data = default_data->Call();
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_SingleBoxData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto new_element = [get_frame_data, name = std::move(name_copy3)](const Box & box)
          {
            auto data = get_frame_data->Call();
            if (data == nullptr)
            {
              return;
            }

            FrameDataSingleBox info;
            info.m_Data = box;
            info.m_FrameDataName = name.get();

            data->m_SingleBoxData.EmplaceBack(std::move(info));
          };

          widget = new FrameEditorSingleBox(editor, sprite, texture_access, getter, default_getter, new_element, frame_id, nullptr);
        }
        break;
      case FrameDataDefType::kMultiBox:
        {
          auto getter = [get_frame_data, name = std::move(name_copy1)]() -> NullOptPtr<ROpaque<std::vector<Box>>>
          { 
            auto data = get_frame_data->Call(); 
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_MultiBoxData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto default_getter = [default_data, name = std::move(name_copy2)]()->NullOptPtr<ROpaque<std::vector<Box>>>
          {
            if (default_data == nullptr)
            {
              return nullptr;
            }

            auto data = default_data->Call();
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_MultiBoxData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto new_element = [get_frame_data, name = std::move(name_copy3)](std::vector<Box> && list)
          {
            auto data = get_frame_data->Call();
            if (data == nullptr)
            {
              return;
            }

            FrameDataMultiBox info;
            info.m_Data = std::move(list);
            info.m_FrameDataName = name.get();

            data->m_MultiBoxData.EmplaceBack(std::move(info));
          };

          widget = new FrameEditorMultiBox(editor, sprite, texture_access, getter, default_getter, new_element, frame_id, true, nullptr);
        }
        break;
      case FrameDataDefType::kSingleLine:
        {
          auto getter = [get_frame_data, name = std::move(name_copy1)]() -> NullOptPtr<ROpaque<FrameDataSingleLineInfo>>
          { 
            auto data = get_frame_data->Call(); 
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_SingleLineData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto default_getter = [default_data, name = std::move(name_copy2)]() -> NullOptPtr<ROpaque<FrameDataSingleLineInfo>>
          {
            if (default_data == nullptr)
            {
              return nullptr;
            }

            auto data = default_data->Call();
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_SingleLineData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto new_element = [get_frame_data, name = std::move(name_copy3)](const FrameDataSingleLineInfo & line)
          {
            auto data = get_frame_data->Call();
            if (data == nullptr)
            {
              return;
            }

            FrameDataSingleLine info;
            info.m_Data = line;
            info.m_FrameDataName = name.get();

            data->m_SingleLineData.EmplaceBack(std::move(info));
          };

          widget = new FrameEditorSingleLine(editor, sprite, texture_access, getter, default_getter, new_element, frame_id, nullptr);
        }
        break;
      case FrameDataDefType::kLowerEdge:
        {
          auto getter = [get_frame_data, name = std::move(name_copy1)]() -> NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>
          { 
            auto data = get_frame_data->Call(); 
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_LowerEdgeData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto default_getter = [default_data, name = std::move(name_copy2)]() -> NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>
          {
            if (default_data == nullptr)
            {
              return nullptr;
            }

            auto data = default_data->Call();
            if (data == nullptr)
            {
              return nullptr;
            }

            for (auto & elem : data->m_LowerEdgeData)
            {
              if (elem.second.m_FrameDataName.ToString() == name.get())
              {
                return &elem.second.m_Data;
              }
            }

            return nullptr;
          };

          auto new_element = [get_frame_data, name = std::move(name_copy3)](const FrameDataLowerEdgeInfo & line)
          {
            auto data = get_frame_data->Call();
            if (data == nullptr)
            {
              return;
            }

            FrameDataLowerEdge info;
            info.m_Data = line;
            info.m_FrameDataName = name.get();

            data->m_LowerEdgeData.EmplaceBack(std::move(info));
          };

          widget = new FrameEditorLowerEdge(editor, sprite, texture_access, getter, default_getter, new_element, frame_id, nullptr);
        }
        break;

    }

    if (widget)
    {
      tab_widget->addTab(widget, frame_data.m_Name.data());
    }
  }
}

void FrameEditorContainer::resizeEvent(QResizeEvent * ev)
{
  m_TabWidget->setGeometry(QRect(0, 0, width() - 1, height() - 1));
}
