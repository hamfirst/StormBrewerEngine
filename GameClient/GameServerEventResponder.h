#pragma once

#include "Game/GameController.refl.h"
#include "Game/GameServerEventSender.h"
#include "Game/GameEventReconciler.h"

class GameClientController;
class GameClientInstanceContainer;

class GameServerEventResponder : public GameServerEventSender
{
public:
  GameServerEventResponder(bool authority, NullOptPtr<GameClientInstanceContainer> instance_container,
    NullOptPtr<GameClientController> client_controller, NullOptPtr<GameEventReconciler> reconciler, NullOptPtr<int> reconcile_frame);

  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr) override;
  virtual void SendGlobalEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, ServerObjectHandle object_handle) override;
  virtual void SendEntityEvent(std::size_t class_id, const void * event_ptr, std::size_t connection_id, ServerObjectHandle object_handle) override;
  virtual void SendAuthEvent(std::size_t class_id, const void * event_ptr) override;
  virtual bool ReconcileEvent(std::size_t event_type_name_hash, uint64_t event_id, const GameNetVec2 & pos) override;

private:
  bool m_Authority;
  NullOptPtr<GameClientInstanceContainer> m_InstanceContainer;
  NullOptPtr<GameClientController> m_ClientController;
  NullOptPtr<GameEventReconciler> m_Reconciler;
  NullOptPtr<int> m_ReconcileFrame;
};
