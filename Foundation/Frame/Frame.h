#pragma once

#include "Foundation/Common.h"

inline Vector2 GetSizeInFrames(int frame_width, int frame_height, int tex_width, int tex_height)
{
  int width_in_frames = (tex_width + frame_width - 1) / frame_width;
  int height_in_frames = (tex_height + frame_height - 1) / frame_height;
  return Vector2(width_in_frames, height_in_frames);
}

inline Vector2 GetFrameDisplaySize(int frame_width, int frame_height, int tex_width, int tex_height, int magnification, int spacing_size)
{
  int width_in_frames = (tex_width + frame_width - 1) / frame_width;
  int height_in_frames = (tex_height + frame_height - 1) / frame_height;
  return Vector2(tex_width * magnification + width_in_frames * spacing_size + spacing_size, 
                 tex_height * magnification + height_in_frames * spacing_size + spacing_size);
}

template <typename Visitor>
void VisitFrames(int frame_width, int frame_height, int tex_width, int tex_height, Visitor && visitor)
{
  auto frame_size = GetSizeInFrames(frame_width, frame_height, tex_width, tex_height);
  int width_in_frames = frame_size.x;
  int height_in_frames = frame_size.y;
  int frame_index = 0;

  for (int fy = 0; fy < height_in_frames; ++fy)
  {
    for (int fx = 0; fx < width_in_frames; ++fx)
    {
      int src_x = fx * frame_width;
      int src_y = fy * frame_height;

      visitor(src_x, src_y, fx, fy, frame_index);
      frame_index++;
    }
  }
}

template <typename Visitor>
void VisitFrame(int frame_width, int frame_height, int tex_width, int tex_height, int frame_index, Visitor && visitor)
{
  auto frame_size = GetSizeInFrames(frame_width, frame_height, tex_width, tex_height);
  int width_in_frames = frame_size.x;
  int height_in_frames = frame_size.y;

  int fx = frame_index % width_in_frames;
  int fy = frame_index / width_in_frames;

  int src_x = fx * frame_width;
  int src_y = fy * frame_height;

  visitor(src_x, src_y);
}
