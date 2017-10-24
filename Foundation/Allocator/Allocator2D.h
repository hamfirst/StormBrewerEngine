#pragma once

#include "Foundation/Common.h"

#include <binpack/GuillotineBinPack.h>
#include <binpack/ShelfBinPack.h>

struct Allocator2DResult
{
  int m_X, m_Y;
  bool m_Rotated;
};

class Allocator2D
{
public:
  Allocator2D(int width, int height);

  Optional<Allocator2DResult> Allocate(int width, int height);

private:
  rbp::GuillotineBinPack m_BinPacker;
};

class Allocator2DShelf
{
public:
  Allocator2DShelf(int width);

  Optional<Allocator2DResult> Allocate(int width, int height);

private:
  rbp::ShelfBinPack m_BinPacker;
};
