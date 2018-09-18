#pragma once

#include "PixelBuffer.h"

void Blit(PixelBuffer & src, PixelBuffer & dst, int src_x, int src_y, int dst_x, int dst_y, int width, int height);
void BlitRotated(PixelBuffer & src, PixelBuffer & dst, int src_x, int src_y, int dst_x, int dst_y, int width, int height);

