#pragma once

#include <QOpenGLWidget>

#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexBuffer.h"
#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/VertexArray.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"

#include "Runtime/Map/MapDef.refl.h"
#include "Runtime/Entity/EntityResource.h"

#include "QTUtil/LerpVar.h"

#include "MapEditorLayer.h"

class MapEditor;
class MapEditorToolBase;

template <typename ToolType>
class MapEditorTool
{

};

class MapEditorViewer : public QOpenGLWidget
{
  Q_OBJECT

public:
  MapEditorViewer(NotNullPtr<MapEditor> editor, MapDef & map, QWidget *parent = nullptr);
  ~MapEditorViewer();

  void SetGridWidth(int width);
  int GetGridWidth() const;
  void SetGridHeight(int height);
  int GetGridHeight() const;

  void SetSelectionBox(const Box & box);
  void ClearSelectionBox();

  template <typename ToolType, typename ... InitArgs>
  void SetTool(const MapEditorTool<ToolType> &, InitArgs && ... init_args)
  {
    SetTool(std::make_unique<ToolType>(*m_Editor, std::forward<InitArgs>(init_args)...));
  }

  void SetTool(std::unique_ptr<MapEditorToolBase> && tool);
  void ClearTool();

  void ChangeLayerSelection(const MapEditorLayerSelection & layer);
  void ClearLayerSelection();

  void ZoomToEntity(std::size_t layer_index, std::size_t entity_index);

  RenderVec2 TransformFromMapSpaceToClipSpace(RenderVec2 map_space);
  RenderVec2 TransformFromClipSpaceToMapSpace(RenderVec2 clip_space);
  RenderVec2 TransformFromScreenSpaceToClipSpace(RenderVec2 screen_space);
  RenderVec2 TransformFromClipSpaceToScreenSpace(RenderVec2 clip_space);

  RenderVec2 TransformFromMapSpaceToScreenSpace(RenderVec2 map_space);
  RenderVec2 TransformFromScreenSpaceToMapSpace(RenderVec2 screen_space);

  void SnapToGrid(Vector2 & pos);

  void SetTileFrameInfo(MapTile & tile, uint64_t frame_id);
  uint64_t GetFrameIdForMapTile(const MapTile & tile);

protected:

  Vector2 GetCursorPos();
  Vector2 GetSnappedCursorPos();

  void SyncMouse();

protected:

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void keyPressEvent(QKeyEvent * event) override;

  void mousePressEvent(QMouseEvent * event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent * event) override;
  void wheelEvent(QWheelEvent *event) override;

public slots:

  void tick();

private:
  NotNullPtr<MapEditor> m_Editor;
  MapDef & m_Map;

  Optional<MapEditorLayerSelection> m_SelectedLayer;
  Optional<Box> m_SelectionBox;

  std::unique_ptr<MapEditorToolBase> m_Tool;
  VertexBuffer m_DrawBuffer;

  RenderState m_RenderState;
  RenderUtil m_RenderUtil;

  ShaderProgram m_GridShader;
  VertexBuffer m_GridBuffer;
  VertexArray m_GridArray;

  int m_GridWidth;
  int m_GridHeight;
  bool m_DrawGrid = true;

  RenderVec2 m_Center = {};
  LerpVar m_Magnification;

  bool m_Dragging = false;
  bool m_Panning = false;
  bool m_HasMouse = false;

  Optional<Vector2> m_LastDrawPos;
  QPoint m_CursorPos;
};
