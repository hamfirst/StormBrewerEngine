
#include "Foundation/Common.h"

#include "Allocator2D.h"

Allocator2D::Allocator2D(int width, int height) :
  m_BinPacker(width, height)
{

}

Optional<Allocator2DResult> Allocator2D::Allocate(int width, int height)
{
  auto result = m_BinPacker.Insert(width, height, false, rbp::GuillotineBinPack::RectBestAreaFit, rbp::GuillotineBinPack::SplitLongerAxis);
  if (result.height == 0)
  {
    return{};
  }

  return Allocator2DResult{ result.x, result.y, result.width == height };
}

Allocator2DShelf::Allocator2DShelf(int width) :
  m_BinPacker(width, INT_MAX, false)
{

}

Optional<Allocator2DResult> Allocator2DShelf::Allocate(int width, int height)
{
  auto result = m_BinPacker.Insert(width, height, rbp::ShelfBinPack::ShelfChoiceHeuristic::ShelfNextFit);
  if (result.height == 0)
  {
    return{};
  }

  return Allocator2DResult{ result.x, result.y, result.width == height };
}
