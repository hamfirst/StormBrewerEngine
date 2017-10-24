
#include "SpriteBaseAnimationEventEditorDialog.h"
#include "SpriteBaseTextureFrameList.h"
#include "SpriteBaseTimeline.h"
#include "SpriteBaseEditor.h"

#include "Runtime/SpriteBase/SpriteAnimationEventDef.refl.meta.h"
#include "Runtime/SpriteBase/SpriteBaseDef.refl.meta.h"

#include "StormData/StormDataJson.h"

SpriteBaseAnimationEventEditorDialog::SpriteBaseAnimationEventEditorDialog(NotNullPtr<SpriteBaseEditor> editor,
  SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent) :
  QDialog(parent),
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_EventWatcher(editor),
  m_AnimationIndex(animation_index),
  m_SelectedFrame(0),
  m_SelectedEvent(-1),
  m_Timeline(std::make_unique<AnimationTrack>(this)),
  m_PropertyFrame(std::make_unique<GenericFrame>("Properties", this))
{
  connect(m_Timeline.get(), &AnimationTrack::selectedFrameChanged, this, &SpriteBaseAnimationEventEditorDialog::handleFrameChanged);
  connect(m_Timeline.get(), &AnimationTrack::selectedEventChanged, this, &SpriteBaseAnimationEventEditorDialog::handleEventChanged);
  connect(m_Timeline.get(), &AnimationTrack::newEvent, this, &SpriteBaseAnimationEventEditorDialog::handleNewEvent);
  connect(m_Timeline.get(), &AnimationTrack::deleteEvent, this, &SpriteBaseAnimationEventEditorDialog::handleDeleteEvent);
  connect(m_Timeline.get(), &AnimationTrack::eventMoved, this, &SpriteBaseAnimationEventEditorDialog::handleEventMove);

  auto layer_tile_path = ".m_Animations[" + std::to_string(m_AnimationIndex) + "].m_Events";
  m_EventWatcher.SetPath(layer_tile_path.data(), false, true, [=] { return m_Sprite.m_Animations.HasAt(m_AnimationIndex); });
  m_EventWatcher.SetChangeCallback([=](const ReflectionChangeNotification & change) { UpdateTimeline(); });
  m_EventWatcher.SetChildChangeCallback([=](const ReflectionChangeNotification & change, std::size_t index) { UpdateTimeline(); });

  m_Properties = m_PropertyFrame->CreateWidget<PropertyEditor>();
  UpdateTimeline();
  UpdateFrame();
}

SpriteBaseAnimationEventEditorDialog::~SpriteBaseAnimationEventEditorDialog()
{

}

void SpriteBaseAnimationEventEditorDialog::handleFrameChanged(int frame_index)
{
  m_SelectedFrame = frame_index;
  UpdateFrame();
}

void SpriteBaseAnimationEventEditorDialog::handleEventChanged(int event_id)
{
  m_SelectedEvent = -1;
  bool found_event = false;

  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim != nullptr)
  {
    auto event = anim->m_Events.TryGet(event_id);
    if (event)
    {
      m_SelectedEvent = event_id;
      m_Properties->LoadStruct(m_Editor, *event, true);
      found_event = true;
    }
  }

  if (found_event == false)
  {
    m_Properties->Unload();
  }

  UpdateFrame();
}

void SpriteBaseAnimationEventEditorDialog::handleEventMove(int event_id, int frame_index, int frame_delay)
{
  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim == nullptr)
  {
    return;
  }

  auto event = anim->m_Events.TryGet(event_id);
  if (event && (event->m_Frame != frame_index || event->m_FrameDelay != frame_delay))
  {
    m_Editor->BeginTransaction();
    event->m_Frame = frame_index;
    event->m_FrameDelay = frame_delay;
    m_Editor->CommitChanges();
  }
}

void SpriteBaseAnimationEventEditorDialog::handleNewEvent(int frame_index, int frame_delay)
{
  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim == nullptr)
  {
    return;
  }

  SpriteBaseAnimationEvent event_info;
  event_info.m_Frame = frame_index;
  event_info.m_FrameDelay = frame_delay;
  event_info.m_EventData.SetType<SpriteAnimationEventBase>();
  anim->m_Events.EmplaceBack(std::move(event_info));

  m_SelectedEvent = anim->m_Events.HighestIndex();
  m_Properties->LoadStruct(m_Editor, anim->m_Events[m_SelectedEvent], true);
}

void SpriteBaseAnimationEventEditorDialog::handleDeleteEvent(int event_id)
{
  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim == nullptr)
  {
    return;
  }

  anim->m_Events.RemoveAt(event_id);
}

void SpriteBaseAnimationEventEditorDialog::closeEvent(QCloseEvent * ev)
{
  emit closed();
}

void SpriteBaseAnimationEventEditorDialog::resizeEvent(QResizeEvent * ev)
{
  auto display_height = (height() * 3) / 4;
  auto panel_width = width() / 3;
  m_FrameDisplay->setGeometry(0, 0, width() - panel_width - 1, display_height);
  m_Timeline->setGeometry(0, display_height + 1, width() - panel_width - 1, height() - display_height - 1);
  m_PropertyFrame->setGeometry(width() - panel_width, 0, panel_width, height());
}

QSize SpriteBaseAnimationEventEditorDialog::sizeHint() const
{
  return QSize(800, 500);
}

void SpriteBaseAnimationEventEditorDialog::UpdateFrame()
{
  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim == nullptr)
  {
    return;
  }

  auto frame_index = m_SelectedFrame;

  auto itr = anim->m_Frames.begin();
  while (frame_index && itr != anim->m_Frames.end())
  {
    frame_index--;
    ++itr;
  }

  if (itr == anim->m_Frames.end())
  {
    return;
  }

  auto frame_id = (uint64_t)itr->second.m_FrameId;

  auto getter = [this]() -> NullOptPtr<ROpaque<std::vector<Box>>>
  {
    auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
    if (anim == nullptr)
    {
      return nullptr;
    }

    auto event = anim->m_Events.TryGet(m_SelectedEvent);
    if (event == nullptr)
    {
      return nullptr;
    }

    return &event->m_EventArea;
  };

  auto new_element = [this](std::vector<Box> && box_list)
  {

  };

  if (m_FrameDisplay == nullptr)
  {
    m_FrameDisplay = std::make_unique<FrameEditorMultiBox>(m_Editor, m_Sprite, m_TextureAccess, getter, new_element, frame_id, false, this);
    m_FrameDisplay->show();
  }
  else
  {
    m_FrameDisplay->ChangeFrame(frame_id, getter, new_element);
  }
}

void SpriteBaseAnimationEventEditorDialog::UpdateTimeline()
{
  std::vector<AnimationTrackFrameInfo> frames;
  std::vector<AnimationTrackEventInfo> events;

  auto anim_info = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim_info != nullptr)
  {
    for (auto & frame : anim_info->m_Frames)
    {
      frames.emplace_back(AnimationTrackFrameInfo{ (int)frame.second.m_FrameDuration });
    }
  }

  for (auto & elem : anim_info->m_Events)
  {
    AnimationTrackEventInfo ev_info;
    ev_info.m_Frame = elem.second.m_Frame;
    ev_info.m_Delay = elem.second.m_FrameDelay;
    ev_info.m_Id = elem.first;
    ev_info.m_Type = elem.second.m_EventData.GetTypeNameHash();
    events.push_back(ev_info);
  }

  m_Timeline->SetFrames(std::move(frames));
  m_Timeline->SetEvents(std::move(events));
}
