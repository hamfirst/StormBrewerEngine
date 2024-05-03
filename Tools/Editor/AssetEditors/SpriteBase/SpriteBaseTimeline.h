#pragma once

#include "QTUtil/DraggableList.h"

#include "Runtime/Sprite/SpriteDef.refl.h"

#include "SpriteBaseTextureLoadList.h"

class SpriteBaseEditor;
class SpriteBaseTimelineElement;

class SpriteBaseTimeline : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseTimeline(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent = nullptr);
  ~SpriteBaseTimeline();

  void AddFrame(uint64_t frame_id);
  void RemoveFrame(QWidget * src_widget);

  void Finalize();

protected:

  void resizeEvent(QResizeEvent * ev) override;

public slots:
  void handleRearrange(int start_index, int end_index);

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;
  std::size_t m_AnimationIndex;

  SpriteBaseDefAnimation m_Animation;

  std::vector<std::pair<SpriteBaseDefAnimFrame, std::unique_ptr<SpriteBaseTimelineElement>>> m_Frames;

  std::unique_ptr<DraggableList> m_FrameList;
};

