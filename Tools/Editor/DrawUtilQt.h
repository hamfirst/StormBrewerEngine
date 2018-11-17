#pragma once

#include <QImage>
#include <QPainter>

#include "Foundation/Optional/Optional.h"

#include "Engine/EngineCommon.h"
#include "Engine/Rendering/Texture.h"
#include "Engine/Asset/TextureAsset.h"


class DrawUtilQt
{
public:

  static Optional<QImage> CreateImageFromTexture(const TextureAsset & tex);

  static void DrawFrameBorder(int frame_width, int frame_height, int dx, int dy, int magnification, int border_size, bool selected, bool highlighted, QPainter & painter);

  static bool DrawFrame(const TextureAsset & tex, int frame_width, int frame_height, uint32_t frame_index, int dx, int dy, int magnification, QPainter & painter);
  static bool DrawFrame(QImage & img, int frame_width, int frame_height, uint32_t frame_index, int dx, int dy, int magnification, QPainter & painter);
};