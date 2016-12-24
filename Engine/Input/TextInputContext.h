#pragma once

class TextInputContext : public std::enable_shared_from_this<TextInputContext>
{
public:

  TextInputContext() = delete;
  TextInputContext(const TextInputContext & rhs) = delete;
  TextInputContext(TextInputContext && rhs) = delete;

  TextInputContext & operator = (const TextInputContext & rhs) = delete;
  TextInputContext & operator = (TextInputContext && rhs) = delete;

  void MakeCurrent(NullOptPtr<Box> input_box);
  void Unbind();

  void SetEnterDelegate(const Delegate<void, const char *> & del);
  void SetEscapeDelegate(const Delegate<void, const char *> & del);
  void SetTabDelegate(const Delegate<void, const char *> & del);

  bool IsTextInputActive();
  double GetTimeSinceLastUpdate();

  const std::string & GetCurrentInput();
  const std::string & GetCurrentComposition();

  std::size_t GetCursorPos();
  std::size_t GetCharacterByteOffset(std::size_t character_index);

  static std::size_t GetMultibyteLength(czstr str);
  static std::size_t GetMultibyteCharacterLength(czstr str);

private:

  friend class WindowManager;
  friend class Window;

  TextInputContext(uint32_t window_id);

  void CommitInput(czstr character);
  void SetComposition(czstr character);

  void HandleKeyPressEvent(int key_sym);

  void HandleEnterPressed();
  void HandleEscapePressed();
  void HandleTabPressed();
  void HandleBackspacePressed();
  void HandleDeletePressed();
  void HandleHomePressed();
  void HandleEndPressed();

private:

  bool m_AllowNewLine;

  std::string m_Text;
  std::string m_Composition;

  std::size_t m_CursorPos = 0;

  uint32_t m_WindowId;
  double m_LastModification;
  double m_TimeCreated;

  std::vector<std::pair<std::size_t, std::size_t>> m_CharacterPositions;

  Delegate<void, const char *> m_EnterDelegate;
  Delegate<void, const char *> m_EscapeDelegate;
  Delegate<void, const char *> m_TabDelegate;
};
