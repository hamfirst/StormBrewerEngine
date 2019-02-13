#pragma once

#include <QOpenGLWidget>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"

#include "QTUtil/QtLerpVar.h"

class TextureViewer : public QOpenGLWidget
{
  Q_OBJECT

public:
  TextureViewer(const char * file_path, QWidget *parent = nullptr);
  ~TextureViewer();

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent * event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent * event) override;
  void wheelEvent(QWheelEvent *event) override;

public slots:

  void tick();

private:
  void HandleTextureLoad(TextureAsset * asset);

  TextureAsset::LoadCallbackLink m_TextureAsset;

  std::string m_FilePath;

  RenderState m_RenderState;
  VertexBuffer m_VertexBuffer;

  RenderVec2 m_Center = {};
  QtLerpVar m_Magnification;

  bool m_Dragging = false;
  QPoint m_CursorPos;
};
