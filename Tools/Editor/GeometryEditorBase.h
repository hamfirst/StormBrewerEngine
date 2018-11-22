#pragma once

#include <QOpenGLWidget>

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "FrameEditorUtil.h"

class DocumentEditorWidgetBase;

class GeometryEditorBase : public QOpenGLWidget
{
  Q_OBJECT;
public:
  explicit GeometryEditorBase(QWidget * parent = nullptr);

  virtual void Copy();
  virtual void Paste();

protected:

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

public slots:

  void tick();
  void setMagnification(int mag);

  signals:
  void magnificationChanged(int mag);

protected:

  void SyncMouse();
  void SyncDraw();

  virtual Optional<Vector2> GetFrameSize();
  virtual uint64_t GetFrameId();
  virtual NullOptPtr<TextureAsset> GetTexture();
  virtual bool UpperLeftOrigin() const;

  Vector2 TransformScreenToFrame(const Vector2 & pos);
  Vector2 TransformFrameToScreen(const Vector2 & pos);

  void DrawBox(const Box & box);
  void DrawActionBox(const Box & box);
  void DrawEdge(const FrameEditorEdge & edge);
  void DrawHighlightedEdge(const FrameEditorEdge & edge);

  void DrawLine(const Vector2 & a, const Vector2 & b);
  void DrawHighlightedLine(const Vector2 & a, const Vector2 & b);
  void DrawCornerControl(const Vector2 & pos);
  void DrawHighlightedCornerControl(const Vector2 & pos);

  virtual void DrawData();
  virtual void DrawPreview(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawLeave();
  virtual bool DrawStart(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawMove(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawEnd(const Vector2 & pos, bool alt, bool shift, bool ctrl);
  virtual void DrawCancel();

  void StopDrawing();

protected:

  virtual void keyPressEvent(QKeyEvent * event) override;
  virtual void keyReleaseEvent(QKeyEvent * event) override;

  virtual void mousePressEvent(QMouseEvent * event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent * event) override;
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void leaveEvent(QEvent * event) override;

protected:

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;
  ShaderProgram m_Shader;
  VertexBuffer m_VertexBuffer;

  Optional<GeometryVertexBufferBuilder> m_GeometryBuidler;

  RenderVec2 m_Center = {};
  int m_Magnification = 4;
  int m_WheelDelta = 0;

  bool m_MirrorX = false;
  bool m_MirrorY = false;

  bool m_HasMouse = false;
  bool m_Panning = false;
  bool m_Dragging = false;
  QPoint m_CursorPos;
};

