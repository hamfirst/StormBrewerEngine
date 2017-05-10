
#include "FrameEditorContainer.h"
#include "FrameEditorSingleBox.h"
#include "FrameEditorSingleLine.h"


FrameEditorContainer::FrameEditorContainer(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<FrameData>> && get_frame_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def,
  QWidget * parent) :
  QDialog(parent),
  m_Getter(std::move(get_frame_data)),
  m_TabWidget(std::make_unique<QTabWidget>(this))
{
  CreateFrameEditorTabs(editor, sprite, texture_access, m_TabWidget.get(), &m_Getter, frame_id, frame_data_def);
}

void FrameEditorContainer::FrameEditorContainer::CreateFrameEditorTabs(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  NotNullPtr<QTabWidget> tab_widget,
  NotNullPtr<Delegate<NullOptPtr<FrameData>>> get_frame_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def)
{
  for (auto & frame_data : frame_data_def)
  {
    QWidget * widget = nullptr;

    switch (frame_data.m_Type)
    {
      case FrameDataDefType::kSingleBox:
        {
          widget = new FrameEditorSingleBox(editor, sprite, texture_access, 
            [get_frame_data] { auto data = get_frame_data->Call(); return data ? &data->m_SingleBoxData : nullptr; }, frame_id, frame_data.m_Name.data(), nullptr);
        }
        break;
      case FrameDataDefType::kSingleLine:
        {
          widget = new FrameEditorSingleLine(editor, sprite, texture_access, 
            [get_frame_data] { auto data = get_frame_data->Call(); return data ? &data->m_SingleLineData : nullptr; }, frame_id, frame_data.m_Name.data(), nullptr);
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
