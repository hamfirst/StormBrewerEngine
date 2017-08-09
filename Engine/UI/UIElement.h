#pragma once

#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementHandle.h"
#include "Engine/UI/UIElementExprBlock.h"
#include "Engine/UI/UIElementExprBinding.h"
#include "Engine/UI/UIElementExprTypes.refl.h"

#include "Runtime/UI/UIDef.refl.h"

#include "Foundation/SkipField/SkipFieldIterator.h"

#include "StormExpr/StormExprEval.h"

class RenderState;
class RenderUtil;

enum class UIElementState
{
  kInactive,
  kActive,
  kHover,
  kPressed,
};

using UIOnClickHandler = Delegate<void, NotNullPtr<UIElement>>;
using UIOnStateChangeHandler = Delegate<void, UIElementState, UIElementState>;
using UIOnUpdateHandler = Delegate<void, NotNullPtr<UIElement>>;

class UIElement
{
public:

  UIElement();
  virtual ~UIElement();

  virtual void Update();
  virtual void Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset);

  void SetActive();
  void SetInactive();

  void SetEnabled();
  void SetEnabled(bool enabled);
  void SetDisabled();

  void Destroy();

  UIElementHandle GetHandle();

  UIElementState GetState();
  Optional<Box> GetActiveArea();

  NullOptPtr<UIElement> GetChild(uint32_t child_name_hash);
  NullOptPtr<UIElement> GetParent();

  void SetOnUpdateHandler(UIOnUpdateHandler && handler);
  void SetOnClickHandler(UIOnClickHandler && handler);
  void SetOnStateChangeHandler(UIOnStateChangeHandler && handler);

  void SetInput(uint32_t variable_name, float val);
  void SetInput(uint32_t variable_name, const std::string & val);
  void SetInput(uint32_t variable_name, czstr val);

protected:

  UIElementExprBindingList InitializeExprBlock(const UIDef & def, NullOptPtr<StormExprValueInitBlock> parent_block, UIManager & manager, std::vector<std::string> & errors);

  const std::string & GetName() const;

  void SetActiveArea(const Box & box);
  void SetOffset(const Vector2 & offset);

  virtual StormExprValueInitBlock GetLocalBlock() = 0;
  virtual StormExprValueInitBlock GetAsParentBlock() = 0;
  virtual UIElementExprBindingList CreateBindingList() = 0;
  StormExprValueInitBlock GetAutoBlock();

private:

  template <typename Type>
  friend class SkipField;

  friend class UIManager;

  void SetHandle(Handle & handle);
  void SetIterator(const SkipFieldIterator & itr);
  const SkipFieldIterator & GetIterator() const;

private:
  struct BindingEvalInfo
  {
    UIElementExprBinding m_Binding;
    int m_FunctionIndex;
  };


  struct ChildBindingEvalInfo
  {
    UIElementExprBinding m_Binding;
    UIElementHandle m_Handle;
    int m_FunctionIndex;
  };

private:

  UIElementHandle m_Handle;
  SkipFieldIterator m_Iterator;

  std::string m_Name;
  uint32_t m_NameHash;
  NullOptPtr<UIElement> m_Parent;
  std::vector<NotNullPtr<UIElement>> m_Children;

  UIOnClickHandler m_OnClick;
  UIOnStateChangeHandler m_OnStateChange;
  UIOnUpdateHandler m_OnUpdate;

  Box m_ActiveArea;
  Vector2 m_Offset;
  UIElementState m_State = UIElementState::kInactive;
  bool m_Enabled = true;
  float m_TimeCreated;

  UIAutoCalculatedBlock m_AutoBlock;
  UIElementExprDynamicBlock m_InputBlock;
  std::vector<StormExprValueBlock> m_BlockList;
  std::vector<std::pair<uint32_t, UIElementExprDynamicBlockVariable>> m_InputLookup;
  std::vector<BindingEvalInfo> m_BindingList;
  std::vector<ChildBindingEvalInfo> m_ChildBindingList;

  Optional<StormExprEval> m_Eval;
};
