

#include "SpriteBaseTimeline.h"
#include "SpriteBaseTimelineElement.h"

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"

#include <sb/vector.h>

SpriteBaseTimeline::SpriteBaseTimeline(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent) :
  QWidget(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_AnimationIndex(animation_index),
  m_FrameList(std::make_unique<DraggableList>(Qt::Horizontal, false, this))
{
  if (animation_index != -1)
  {
    m_Animation = m_Sprite.m_Animations[animation_index];

    std::vector<QWidget *> initial_widgets;
    for (auto elem : m_Animation.m_Frames)
    {
      auto widget = std::make_unique<SpriteBaseTimelineElement>(m_Editor, m_Sprite, m_TextureAccess, elem.second.m_FrameId);
      widget->SetRemoveCallback([this, w = widget.get()]{ RemoveFrame(w); });
      widget->SetClickCallback([this, w = widget.get()]
      { 
        for(std::size_t index = 0, end = m_Frames.size(); index < end; ++index)
        {
          if (m_Frames[index].second.get() == w)
          {
            m_FrameList->StartDragging(index);
            break;
          }
        }
      });
      
      initial_widgets.push_back(widget.get());
      m_Frames.push_back(std::make_pair(elem.second, std::move(widget)));
    }

    m_FrameList->SetInitialWidgets(initial_widgets);
  }
  else
  {
    m_Animation.m_Name = "Animation";
  }

  connect(m_FrameList.get(), &DraggableList::dragComplete, this, &SpriteBaseTimeline::handleRearrange);
  m_FrameList->show();
}

SpriteBaseTimeline::~SpriteBaseTimeline()
{
  m_Frames.clear();
}

void SpriteBaseTimeline::AddFrame(uint64_t frame_id)
{
  SpriteBaseDefAnimFrame frame_data;
  frame_data.m_FrameId = frame_id;

  auto widget = std::make_unique<SpriteBaseTimelineElement>(m_Editor, m_Sprite, m_TextureAccess, frame_id);
  widget->SetRemoveCallback([this, w = widget.get()]{ RemoveFrame(w); });
  widget->SetClickCallback([this, w = widget.get()]
  {
    for (std::size_t index = 0, end = m_Frames.size(); index < end; ++index)
    {
      if (m_Frames[index].second.get() == w)
      {
        m_FrameList->StartDragging(index);
        break;
      }
    }
  });

  m_FrameList->AddWidget(widget.get());
  m_Frames.push_back(std::make_pair(frame_data, std::move(widget)));
}

void SpriteBaseTimeline::RemoveFrame(QWidget * src_widget)
{
  for(auto itr = m_Frames.begin(), end = m_Frames.end(); itr < end; ++itr)
  {
    if (itr->second.get() == src_widget)
    {
      m_FrameList->RemoveWidget(itr->second.get());
      m_Frames.erase(itr);
      return;
    }
  }
}

void SpriteBaseTimeline::Finalize()
{
  m_Animation.m_Frames.Clear();

  for (auto & frame : m_Frames)
  {
    m_Animation.m_Frames.EmplaceBack(frame.first);
  }

  if (m_Sprite.m_Animations.HasAt(m_AnimationIndex))
  {
    m_Sprite.m_Animations[m_AnimationIndex] = std::move(m_Animation);
  }
  else
  {
    m_Sprite.m_Animations.PushBack(std::move(m_Animation));
  }
}

void SpriteBaseTimeline::resizeEvent(QResizeEvent * ev)
{
  m_FrameList->setGeometry(0, 0, width() - 1, height() - 1);
}

void SpriteBaseTimeline::handleRearrange(int start_index, int end_index)
{
  vrearrange(m_Frames, start_index, end_index);
  m_FrameList->Rearrange(start_index, end_index);
}
