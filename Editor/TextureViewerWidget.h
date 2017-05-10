#pragma once

#include <QOpenGLWidget>

#include "Engine/Asset/TextureAsset.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

#include "QTUtil/LerpVar.h"

class TextureViewerWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  TextureViewerWidget(QWidget *parent = nullptr);
  ~TextureViewerWidget();

  void LoadTexture(czstr file_path);
  void UnloadTexture();

  void SetGridWidth(int width);
  void SetGridHeight(int height);

  RenderVec2 TransformFromTextureSpaceToClipSpace(RenderVec2 texture_space);
  RenderVec2 TransformFromClipSpaceToTextureSpace(RenderVec2 clip_space);
  RenderVec2 TransformFromScreenSpaceToClipSpace(RenderVec2 screen_space);
  RenderVec2 TransformFromClipSpaceToScreenSpace(RenderVec2 clip_space);

  RenderVec2 TransformFromTextureSpaceToScreenSpace(RenderVec2 texture_space);
  RenderVec2 TransformFromScreenSpaceToTextureSpace(RenderVec2 screen_space);

protected:

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
  RenderUtil m_RenderUtil;
  ShaderProgram m_TextureShader;
  VertexBuffer m_VertexBuffer;
  VertexArray m_VertexArray;
  ShaderProgram m_GridShader;
  VertexBuffer m_GridBuffer;
  VertexArray m_GridArray;

  int m_GridWidth;
  int m_GridHeight;

  RenderVec2 m_Center = {};
  LerpVar m_Magnification;

  bool m_Dragging = false;
  QPoint m_CursorPos;
};
