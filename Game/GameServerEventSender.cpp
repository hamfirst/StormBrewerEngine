
#include "Game/GameCommon.h"
#include "Game/GameServerEventSender.h"

void GameServerEventSender::SendSoundEvent(const GameNetVec2 & pos, uint32_t asset_hash)
{
  if (ReconcileEvent<PlaySoundGlobalEvent>(pos, asset_hash) == false)
  {
    return;
  }

  PlaySoundGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendSoundEvent(const GameNetVec2 & pos, const GameNetVec2 & normal, uint32_t asset_hash)
{
  if (ReconcileEvent<PlaySoundGlobalEvent>(pos, normal, (int16_t)asset_hash) == false)
  {
    return;
  }

  PlaySoundGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxEvent(const GameNetVec2 & pos, uint32_t asset_hash)
{
  if (ReconcileEvent<PlayVfxGlobalEvent>(pos, asset_hash) == false)
  {
    return;
  }

  PlayVfxGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

void GameServerEventSender::SendVfxEvent(const GameNetVec2 & pos, const GameNetVec2 & normal, uint32_t asset_hash)
{
  if (ReconcileEvent<PlayVfxGlobalEvent>(pos, normal, (int16_t)asset_hash) == false)
  {
    return;
  }

  PlayVfxGlobalEvent ev;
  ev.m_PositionX = (int16_t)((int32_t)pos.x);
  ev.m_PositionY = (int16_t)((int32_t)pos.y);
  ev.m_AssetHash = asset_hash;
  BroadcastEvent(ev);
}

