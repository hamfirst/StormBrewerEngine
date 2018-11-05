#pragma once

#include "Runtime/ServerObject/ServerObjectComponent.h"

template <typename BaseClass, typename BaseConfig, typename NetBitWriter>
struct NetSerializer<ServerObjectComponent<BaseClass, BaseConfig>, NetBitWriter>
{
  void operator()(const ServerObjectComponent<BaseClass, BaseConfig> & val, NetBitWriter & writer)
  {

  }
};

template <typename BaseClass, typename BaseConfig, typename NetBitReader>
struct NetDeserializer<ServerObjectComponent<BaseClass, BaseConfig>, NetBitReader>
{
  void operator()(ServerObjectComponent<BaseClass, BaseConfig> & val, NetBitReader & reader)
  {

  }
};


