#pragma once

#include <QWidget>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Asset/AssetSync.h"

#include "Runtime/SpriteBase/SpriteBaseDef.refl.h"

#include "Tools/Editor/Utility/DocumentValueWatcher.h"

class SpriteBaseEditor;
class QImage;

class SpriteBaseTextureFrameElement : public QWidget
{
  Q_OBJECT;
public:
  SpriteBaseTextureFrameElement(NotNullPtr<SpriteBaseEditor> editor, Delegate<SpriteBaseDefTexture *> && elem_ptr, QWidget * parent = nullptr);
  ~SpriteBaseTextureFrameElement();

  void SetSizeChangeCallback(Delegate<void> && callback);
  void SetFrameSelectCallback(Delegate<void, uint64_t> && callback);

protected:

  void LoadTexture();
  bool DataExists();

  void VisitElements(Delegate<void, QImage *, int, int, int, int, int, int, int, int, int> && callback, bool change_min_height = true);

protected:

  static const int magnification = 2;
  static const int buffer_size = 3;
  static const int border_size = 1;
  static const int spacing = buffer_size + border_size * 2;

protected:

  void resizeEvent(QResizeEvent * ev) override;
  void paintEvent(QPaintEvent * ev) override;

  void mouseMoveEvent(QMouseEvent * ev) override;
  void mousePressEvent(QMouseEvent * ev) override;
  void leaveEvent(QEvent * ev) override;

private:
  NotNullPtr<SpriteBaseEditor> m_Editor;

  Delegate<void> m_SizeChanged;
  Delegate<void, uint64_t> m_FrameSelectCallback;

  DocumentValueWatcher m_Watcher;

  Delegate<SpriteBaseDefTexture *> m_ElementPtr;
  AssetSync<TextureAsset> m_Texture;

  int m_HighlightedFrame;
  uint32_t m_TextureNameHash;
};

