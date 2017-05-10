#pragma once

#include "GenericListFrame.h"
#include "GenericList.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

class SpriteBaseEditor;

class SpriteBaseTextureFrameList : public GenericListFrame
{
  Q_OBJECT
public:
  SpriteBaseTextureFrameList(NotNullPtr<SpriteBaseEditor> editor, SpriteBaseDef & sprite, QWidget * parent = nullptr);
  ~SpriteBaseTextureFrameList();

  void SetFrameSelectionCallback(Delegate<void, uint64_t> && callback);

private:

  NotNullPtr<SpriteBaseEditor> m_Editor;
  SpriteBaseDef & m_Sprite;

  Delegate<void, uint64_t> m_SelectionCallback;
};

