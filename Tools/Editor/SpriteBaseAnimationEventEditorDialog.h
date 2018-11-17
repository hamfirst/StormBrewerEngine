#pragma once

#include <QDialog>

#include "QTUtil/AnimationTrack.h"

#include "GenericFrame.h"
#include "GenericListFrame.h"
#include "GenericList.h"
#include "DocumentListValueWatcher.h"
#include "SpriteBaseFrameDisplay.h"
#include "PropertyEditor.h"
#include "FrameEditorMultiBox.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"


class SpriteBaseEditor;
class SpriteBaseTextureLoadList;
class SpriteBaseTextureFrameList;
class SpriteBaseTimeline;

class SpriteBaseAnimationEventEditorDialog : public QDialog
{
  Q_OBJECT
public:
  SpriteBaseAnimationEventEditorDialog(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, SpriteBaseTextureLoadList & texture_access, int animation_index, QWidget * parent = nullptr);
  ~SpriteBaseAnimationEventEditorDialog();

public slots:
  void handleFrameChanged(int frame_index);
  void handleEventChanged(int event_id);
  void handleEventMove(int event_id, int frame_index, int frame_delay);

  void handleNewEvent(int frame_index, int frame_delay);
  void handleDeleteEvent(int event_id);

signals:
  void closed();

protected:
  virtual void closeEvent(QCloseEvent * ev) override;
  virtual void resizeEvent(QResizeEvent * ev) override;
  virtual QSize sizeHint() const override;

  void UpdateFrame();
  void UpdateTimeline();

private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;
  SpriteBaseTextureLoadList & m_TextureAccess;

  DocumentListValueWatcher m_EventWatcher;

  std::size_t m_AnimationIndex;
  int m_SelectedFrame;
  int m_SelectedEvent;

  std::unique_ptr<FrameEditorMultiBox> m_FrameDisplay;
  std::unique_ptr<AnimationTrack> m_Timeline;
  std::unique_ptr<GenericFrame> m_PropertyFrame;

  PropertyEditor * m_Properties;
};

