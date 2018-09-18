#pragma once

#include "StormNet/NetSerialize.h"
#include "StormNet/NetDeserialize.h"

#include "Foundation/Math/Intersection.h"

template <class VecCompType, class NetBitWriter>
struct NetSerializer<IntersectionVecType<VecCompType>, NetBitWriter>
{
  void operator()(const IntersectionVecType<VecCompType> & val, NetBitWriter & writer)
  {
    NetSerializer<VecCompType, NetBitWriter> serializer;
    serializer(val.x, writer);
    serializer(val.y, writer);
  }
};

template <class VecCompType, class NetBitReader>
struct NetDeserializer<IntersectionVecType<VecCompType>, NetBitReader>
{
  void operator()(IntersectionVecType<VecCompType> & val, NetBitReader & reader)
  {
    NetDeserializer<VecCompType, NetBitReader> dserializer;
    dserializer(val.x, reader);
    dserializer(val.y, reader);
  }
};


