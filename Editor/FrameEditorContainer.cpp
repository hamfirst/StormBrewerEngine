
#include <QHBoxLayout>

#include "FrameEditorAnchorManager.h"
#include "FrameEditorAnchorEditor.h"
#include "FrameEditorContainer.h"
#include "FrameEditorSingleBox.h"
#include "FrameEditorMultiBox.h"
#include "FrameEditorSingleLine.h"
#include "FrameEditorLowerEdge.h"
#include "SpriteBaseEditor.h"
#include "SpriteBaseTextureLoadList.h"

#include "StormData/StormDataJson.h"

#include "Foundation/Frame/Frame.h"

#include "Runtime/FrameData/FrameData.refl.meta.h"


FrameEditorContainer::FrameEditorContainer(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  Delegate<NullOptPtr<FrameData>, uint64_t> && get_frame_data,
  Delegate<NullOptPtr<FrameData>> && get_default_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def,
  bool create_anchor_manager_tab,
  bool create_anchor_editor_tab,
  QWidget * parent) :
  QDialog(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_Getter(std::move(get_frame_data)),
  m_Default(std::move(get_default_data)),
  m_TabWidget(std::make_unique<QTabWidget>(this)),
  m_FrameId(frame_id)
{
  setMinimumSize(500, 500);

  m_Menu = std::make_unique<QMenuBar>();

  auto menuEdit = new QMenu(m_Menu.get());
  menuEdit->setTitle("&Edit");

  auto menuFrame = new QMenu(m_Menu.get());
  menuFrame->setTitle("&Frame");


  auto action_Undo = new QAction("Undo", this);
  action_Undo->setShortcut(QKeySequence::Undo);
  connect(action_Undo, &QAction::triggered, this, &FrameEditorContainer::undo);
  menuEdit->addAction(action_Undo);

  auto action_Redo = new QAction("Redo", this);
  action_Redo->setShortcut(QKeySequence::Redo);
  connect(action_Redo, &QAction::triggered, this, &FrameEditorContainer::redo);
  menuEdit->addAction(action_Redo);

  auto action_Copy = new QAction("Copy", this);
  action_Copy->setShortcut(QKeySequence::Copy);
  connect(action_Copy, &QAction::triggered, this, &FrameEditorContainer::copy);
  menuEdit->addAction(action_Copy);

  auto action_CopyPrev = new QAction("Duplicate Previous Frame", this);
  action_CopyPrev->setShortcut(QKeySequence(Qt::Key_D));
  connect(action_CopyPrev, &QAction::triggered, this, &FrameEditorContainer::copyPrev);
  menuEdit->addAction(action_CopyPrev);

  auto action_Paste = new QAction("Paste", this);
  action_Paste->setShortcut(QKeySequence::Paste);
  connect(action_Paste, &QAction::triggered, this, &FrameEditorContainer::paste);
  menuEdit->addAction(action_Paste);

  auto action_PrevFrame = new QAction("Prev Frame", this);
  action_PrevFrame->setShortcut(QKeySequence(Qt::Key_1));
  connect(action_PrevFrame, &QAction::triggered, this, &FrameEditorContainer::prevFrame);
  menuFrame->addAction(action_PrevFrame);

  auto action_NextFrame = new QAction("Next Frame", this);
  action_NextFrame->setShortcut(QKeySequence(Qt::Key_2));
  connect(action_NextFrame, &QAction::triggered, this, &FrameEditorContainer::nextFrame);
  menuFrame->addAction(action_NextFrame);

  m_Menu->addMenu(menuEdit);
  m_Menu->addMenu(menuFrame);

  CreateFrameEditorTabs(editor, sprite, texture_access, m_TabWidget.get(), &m_ChildWidgets, &m_Getter, &m_Default, 
    frame_id, frame_data_def, create_anchor_manager_tab, create_anchor_editor_tab);

  auto layout = new QHBoxLayout();
  layout->setMenuBar(m_Menu.get());
  layout->addWidget(m_TabWidget.get());
  setLayout(layout);
}

void FrameEditorContainer::Finalize()
{
  for (auto elem : m_ChildWidgets)
  {
    connect(elem, &FrameEditorBase::magnificationChanged, this, &FrameEditorContainer::magnificationChanged);
  }
}

bool FrameEditorContainer::IncFrame()
{
  uint32_t texture_hash = m_FrameId >> 32;
  int frame_index = m_FrameId & 0xFFFFFFFF;
  int texture_index = -1;

  for (auto elem : m_Sprite.m_Textures)
  {
    auto hash = crc32(elem.second.m_Filename.data());
    if (hash == texture_hash)
    {
      texture_index = (int)elem.first;
      break;
    }
  }

  if (texture_index == -1)
  {
    return false;
  }

  auto & texture_info = m_Sprite.m_Textures[texture_index];
  auto texture = m_TextureAccess.GetTexture(texture_index);
  if (texture == nullptr)
  {
    return false;
  }

  auto size_in_frames = GetSizeInFrames(texture_info.m_FrameWidth, texture_info.m_FrameHeight, texture->GetWidth(), texture->GetHeight());
  auto num_frames_in_texture = size_in_frames.x * size_in_frames.y;

  if (num_frames_in_texture == 0)
  {
    return false;
  }

  if (frame_index < num_frames_in_texture - 1)
  {
    m_FrameId++;
    UpdateChildFrames();
    return true;
  }

  int next_texture_index = -1;
  for (int index = texture_index + 1; index <= m_Sprite.m_Textures.HighestIndex(); ++index)
  {
    if (m_Sprite.m_Textures.HasAt(index))
    {
      next_texture_index = index;
      break;
    }
  }

  if (next_texture_index == -1)
  {
    return false;
  }

  m_FrameId = crc32(m_Sprite.m_Textures[next_texture_index].m_Filename.data());
  m_FrameId <<= 32;
  UpdateChildFrames();
  return true;
}

bool FrameEditorContainer::DecFrame()
{
  uint32_t texture_hash = m_FrameId >> 32;
  int frame_index = m_FrameId & 0xFFFFFFFF;
  int texture_index = -1;

  for (auto elem : m_Sprite.m_Textures)
  {
    auto hash = crc32(elem.second.m_Filename.data());
    if (hash == texture_hash)
    {
      texture_index = (int)elem.first;
      break;
    }
  }

  if (texture_index == -1)
  {
    return false;
  }

  auto & texture_info = m_Sprite.m_Textures[texture_index];
  auto texture = m_TextureAccess.GetTexture(texture_index);
  if (texture == nullptr)
  {
    return false;
  }

  auto size_in_frames = GetSizeInFrames(texture_info.m_FrameWidth, texture_info.m_FrameHeight, texture->GetWidth(), texture->GetHeight());
  auto num_frames_in_texture = size_in_frames.x * size_in_frames.y;

  if (num_frames_in_texture == 0)
  {
    return false;
  }

  if (frame_index > 0)
  {
    m_FrameId--;
    UpdateChildFrames();
    return true;
  }

  int prev_texture_index = -1;
  for (int index = texture_index - 1; index >= 0; --index)
  {
    if (m_Sprite.m_Textures.HasAt(index))
    {
      prev_texture_index = index;
      break;
    }
  }

  if (prev_texture_index == -1)
  {
    return false;
  }

  auto & prev_texture_info = m_Sprite.m_Textures[prev_texture_index];
  texture = m_TextureAccess.GetTexture(prev_texture_index);
  if (texture == nullptr)
  {
    return false;
  }

  size_in_frames = GetSizeInFrames(prev_texture_info.m_FrameWidth, prev_texture_info.m_FrameHeight, texture->GetWidth(), texture->GetHeight());
  num_frames_in_texture = size_in_frames.x * size_in_frames.y;

  m_FrameId = crc32(m_Sprite.m_Textures[prev_texture_index].m_Filename.data());
  m_FrameId <<= 32;
  m_FrameId += num_frames_in_texture - 1;
  UpdateChildFrames();
  return true;
}

void FrameEditorContainer::FrameEditorContainer::CreateFrameEditorTabs(
  NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite,
  SpriteBaseTextureLoadList & texture_access,
  NotNullPtr<QTabWidget> tab_widget,
  NotNullPtr<std::vector<FrameEditorBase *>> child_widgets,
  NotNullPtr<Delegate<NullOptPtr<FrameData>, uint64_t>> get_frame_data,
  NullOptPtr<Delegate<NullOptPtr<FrameData>>> default_data,
  uint64_t frame_id,
  const std::vector<FrameDataDefElem> & frame_data_def,
  bool create_anchor_manager_tab,
  bool create_anchor_editor_tab)
{
  for (auto & frame_data : frame_data_def)
  {
    FrameEditorBase * widget = nullptr;

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
          auto getter = [get_frame_data, name = std::move(name_copy1)](uint64_t frame_id) -> NullOptPtr<ROpaque<Box>>
          { 
            auto data = get_frame_data->Call(frame_id);
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

          auto new_element = [get_frame_data, name = std::move(name_copy3)](uint64_t frame_id, const Box & box)
          {
            auto data = get_frame_data->Call(frame_id);
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
          auto getter = [get_frame_data, name = std::move(name_copy1)](uint64_t frame_id) -> NullOptPtr<ROpaque<std::vector<Box>>>
          { 
            auto data = get_frame_data->Call(frame_id); 
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

          auto new_element = [get_frame_data, name = std::move(name_copy3)](uint64_t frame_id, std::vector<Box> && list)
          {
            auto data = get_frame_data->Call(frame_id);
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
          auto getter = [get_frame_data, name = std::move(name_copy1)](uint64_t frame_id) -> NullOptPtr<ROpaque<FrameDataSingleLineInfo>>
          { 
            auto data = get_frame_data->Call(frame_id); 
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

          auto new_element = [get_frame_data, name = std::move(name_copy3)](uint64_t frame_id, const FrameDataSingleLineInfo & line)
          {
            auto data = get_frame_data->Call(frame_id);
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
          auto getter = [get_frame_data, name = std::move(name_copy1)](uint64_t frame_id) -> NullOptPtr<ROpaque<FrameDataLowerEdgeInfo>>
          { 
            auto data = get_frame_data->Call(frame_id); 
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

          auto new_element = [get_frame_data, name = std::move(name_copy3)](uint64_t frame_id, const FrameDataLowerEdgeInfo & line)
          {
            auto data = get_frame_data->Call(frame_id);
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

      if (child_widgets)
      {
        child_widgets->push_back(widget);
      }
    }
  }

  if (create_anchor_manager_tab)
  {
    auto widget = new FrameEditorAnchorManager(editor, sprite, texture_access, nullptr);
    tab_widget->addTab(widget, "Anchors");

    if (child_widgets)
    {
      child_widgets->push_back(widget);
    }
  }

  if (create_anchor_editor_tab)
  {
    auto getter = [get_frame_data](uint64_t frame_id) -> NullOptPtr<RMergeList<FrameDataAnchorElement>>
    {
      auto data = get_frame_data->Call(frame_id);
      if (data == nullptr)
      {
        return nullptr;
      }

      return &data->m_Anchors;
    };

    auto default_getter = [default_data]() -> NullOptPtr<RMergeList<FrameDataAnchorElement>>
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

      return &data->m_Anchors;
    };

    auto new_element = [get_frame_data](uint64_t frame_id, const RMergeList<FrameDataAnchorElement> & anchors)
    {
      auto data = get_frame_data->Call(frame_id);
      if (data == nullptr)
      {
        return;
      }

      data->m_Anchors = anchors;
    };

    auto widget = new FrameEditorAnchorEditor(editor, sprite, texture_access, getter, default_getter, new_element, frame_id, nullptr);
    tab_widget->addTab(widget, "Anchors");

    if (child_widgets)
    {
      child_widgets->push_back(widget);
    }
  }
}

void FrameEditorContainer::magnificationChanged(int mag)
{
  for (auto elem : m_ChildWidgets)
  {
    elem->setMagnification(mag);
  }
}

void FrameEditorContainer::undo()
{
  m_Editor->Undo();
}

void FrameEditorContainer::redo()
{
  m_Editor->Redo();
}

void FrameEditorContainer::copy()
{
  m_ChildWidgets[m_TabWidget->currentIndex()]->Copy();
}

void FrameEditorContainer::copyPrev()
{
  if (DecFrame())
  {
    m_ChildWidgets[m_TabWidget->currentIndex()]->Copy();
    IncFrame();
    m_ChildWidgets[m_TabWidget->currentIndex()]->Paste();
  }
}

void FrameEditorContainer::paste()
{
  m_ChildWidgets[m_TabWidget->currentIndex()]->Paste();
}

void FrameEditorContainer::nextFrame()
{
  IncFrame();
}

void FrameEditorContainer::prevFrame()
{
  DecFrame();
}

void FrameEditorContainer::UpdateChildFrames()
{
  for (auto elem : m_ChildWidgets)
  {
    elem->SetFrame(m_FrameId);
  }
}