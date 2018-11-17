
#include <QPainter>
#include <QMouseEvent>

#include "Runtime/Sprite/SpriteDef.refl.meta.h"

#include "StormData/StormDataJson.h"
#include "StormData/StormDataPath.h"

#include "SpriteBaseAnimationListElement.h"
#include "SpriteBaseAnimationListFrameElement.h"
#include "SpriteBaseEditor.h"

#include "PropertyEditorWidget.h"
#include "GenericList.h"

SpriteBaseAnimationListElement::SpriteBaseAnimationListElement(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, 
  SpriteBaseTextureLoadList & texture_access, std::size_t animation_index) :
  m_Editor(editor),
  m_Sprite(sprite),
  m_TextureAccess(texture_access),
  m_AnimationIndex(animation_index),
  m_FrameListContainer(std::make_unique<GenericListFrame>("Frames", false, false, this)),
  m_AnimNameLabel(std::make_unique<QLabel>("Name:", this)),
  m_EditFrames(std::make_unique<QPushButton>("Edit Frame List", this)),
  m_EditEvents(std::make_unique<QPushButton>("Edit Events", this)),
  m_Delete(std::make_unique<QPushButton>("Delete", this)),
  m_ShowFrameList(false),
  m_Timer(std::make_unique<QTimer>()),
  m_AnimFrame(0),
  m_AnimFrameDelay(0)
{
  setMinimumHeight(200);
  setMouseTracking(true);

  m_UpdateDelegateLink = m_TextureAccess.AddUpdateCallback([this] { update(); });

  m_FrameList = CreateGenericList<RMergeList, SpriteBaseDefAnimFrame>(m_Editor, sprite.m_Animations[animation_index].m_Frames,
    [](GenericList * list, SpriteBaseDefAnimFrame & def, std::size_t index, void * user_data) -> std::unique_ptr<QWidget>
    {
      auto parent = static_cast<SpriteBaseAnimationListElement *>(user_data);
      auto ptr = std::make_unique<SpriteBaseAnimationListFrameElement>(parent->m_Editor, parent->m_Sprite, parent->m_TextureAccess, parent->m_AnimationIndex, index);
      return std::move(ptr);
    }, this,
    [](QWidget * widget, SpriteBaseDefAnimFrame & def, void * user_data)
    {

    }, nullptr, 
    m_FrameListContainer.get(), [this]() -> void * { auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex); return anim ? &anim->m_Frames : nullptr; }, false);

  m_AnimName = PropertyEditorCreate(m_Editor, m_Editor->GetPropertyFieldDatabase().GetBasicField(PropertyFieldType::kString), true,
    [this]()-> void * { auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex); return anim ? &anim->m_Name : nullptr; },
    StormDataGetPath(m_Sprite.m_Animations[m_AnimationIndex].m_Name), {}, "Animation", this);

  m_AnimNameLabel->setGeometry(105, 2, 50, 20);
  m_AnimName->setGeometry(155, 2, 150, 20);

  m_EditFrames->setGeometry(155, 40, 100, 20);
  connect(m_EditFrames.get(), &QPushButton::pressed, this, &SpriteBaseAnimationListElement::editFrames);

  m_EditEvents->setGeometry(155, 80, 100, 20);
  connect(m_EditEvents.get(), &QPushButton::pressed, this, &SpriteBaseAnimationListElement::editEvents);

  m_Delete->setGeometry(455, 40, 100, 20);
  connect(m_Delete.get(), &QPushButton::pressed, this, &SpriteBaseAnimationListElement::remove);

  m_FrameListContainer->hide();
  m_FrameList->SetSizeChangeCallback([this] {HandleFrameListChanged(); });

  connect(m_Timer.get(), &QTimer::timeout, this, &SpriteBaseAnimationListElement::updateTimer);
  m_Timer->setInterval(16);
  m_Timer->start();

  HandleFrameListChanged();
}

SpriteBaseAnimationListElement::~SpriteBaseAnimationListElement()
{

}

void SpriteBaseAnimationListElement::SetSizeChangeCallback(Delegate<void> && callback)
{
  m_SizeChangedCallback = std::move(callback);
}

void SpriteBaseAnimationListElement::SetOpenEditorCallback(Delegate<void> && callback)
{
  m_EditCallback = std::move(callback);
}

void SpriteBaseAnimationListElement::SetOpenEventCallback(Delegate<void> && callback)
{
  m_EventCallback = std::move(callback);
}

void SpriteBaseAnimationListElement::SetRemoveCallback(Delegate<void> && callback)
{
  m_RemoveCallback = std::move(callback);
}

void SpriteBaseAnimationListElement::HandleFrameListChanged()
{
  setMinimumHeight(100 + (m_ShowFrameList ? m_FrameList->minimumHeight() : 0));
  m_SizeChangedCallback();
}

void SpriteBaseAnimationListElement::paintEvent(QPaintEvent * ev)
{
  QPainter p(this);

  if (m_Sprite.m_Animations.HasAt(m_AnimationIndex) == false)
  {
    return;
  }

  auto & frames = m_Sprite.m_Animations[m_AnimationIndex].m_Frames;
  if (frames.HighestIndex() < 0)
  {
    return;
  }

  std::vector<uint64_t> frame_ids;
  for (auto elem : frames)
  {
    frame_ids.push_back(elem.second.m_FrameId);
  }

  if (m_AnimFrame >= frame_ids.size())
  {
    return;
  }

  int src_x, src_y, src_w, src_h;
  auto img = m_TextureAccess.GetFrameAndImage(frame_ids[m_AnimFrame], src_x, src_y, src_w, src_h);

  if (img)
  {
    p.drawImage(QRect(0, 0, 100, 100), img.Value(), QRect(src_x, src_y, src_w, src_h));
  }
}

void SpriteBaseAnimationListElement::resizeEvent(QResizeEvent * ev)
{
  m_FrameListContainer->setGeometry(40, 100, width() - 40, height() - 100);
}

void SpriteBaseAnimationListElement::mousePressEvent(QMouseEvent * ev)
{
  if (ev->y() > 100)
  {
    return;
  }

  m_ShowFrameList = !m_ShowFrameList;
  if (m_ShowFrameList)
  {
    m_FrameListContainer->show();
  }
  else
  {
    m_FrameListContainer->hide();
  }

  HandleFrameListChanged();
}

void SpriteBaseAnimationListElement::editFrames()
{
  m_EditCallback();
}

void SpriteBaseAnimationListElement::editEvents()
{
  m_EventCallback();
}

void SpriteBaseAnimationListElement::remove()
{
  m_RemoveCallback();
}

void SpriteBaseAnimationListElement::updateTimer()
{
  auto anim = m_Sprite.m_Animations.TryGet(m_AnimationIndex);
  if (anim == nullptr || anim->m_Frames.HighestIndex() < 0)
  {
    return;
  }

  std::vector<int> frame_durations;
  for (auto elem : anim->m_Frames)
  {
    frame_durations.push_back(elem.second.m_FrameDuration);
  }

  if (m_AnimFrame >= frame_durations.size())
  {
    m_AnimFrame = 0;
    m_AnimFrameDelay = 0;
    update();
    return;
  }

  m_AnimFrameDelay++;
  if (m_AnimFrameDelay >= frame_durations[m_AnimFrame])
  {
    m_AnimFrameDelay = 0;
    m_AnimFrame++;

    if (m_AnimFrame >= frame_durations.size())
    {
      m_AnimFrame = 0;
      m_AnimFrameDelay = 0;
    }

    update();
  }
}