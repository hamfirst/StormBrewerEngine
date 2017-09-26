#pragma once

#include "Game/GameServerEventSender.h"
#include "Game/GameEventReconciler.h"
#include "GameClient/GameClientController.refl.h"

class GameServerEventResponder : public GameServerEventSender
{
public:
  GameServerEventResponder(NullOptPtr<GameClientController> client_controller, NullOptPtr<GameEventReconciler> reconciler, NullOptPtr<int> reconcile_frame);

  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr) override;
  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) override;
  virtual bool ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos) override;

private:
  NullOptPtr<GameClientController> m_ClientController;
  NullOptPtr<GameEventReconciler> m_Reconciler;
  NullOptPtr<int> m_ReconcileFrame;
};
