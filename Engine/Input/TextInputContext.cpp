
#include "Engine/EngineCommon.h"
#include "Engine/Input/TextInputContext.h"
#include "Engine/Window/WindowManager.h"

#include <SDL/SDL_keyboard.h>

TextInputContext::TextInputContext(uint32_t window_id, bool allow_first_input) :
  m_WindowId(window_id),
  m_LastModification(GetTimeSeconds()),
  m_TimeCreated(m_LastModification),
  m_AllowFirstInput(allow_first_input)
{

}

void TextInputContext::MakeCurrent(NullOptPtr<Box> input_box)
{
  g_WindowManager.SetTextInputContext(m_WindowId, shared_from_this(), input_box);
}

void TextInputContext::Unbind()
{
  g_WindowManager.ClearTextInputContext(m_WindowId, this);
}

void TextInputContext::SetEnterDelegate(const Delegate<void, const char *> & del)
{
  m_EnterDelegate = del;
}

void TextInputContext::SetEscapeDelegate(const Delegate<void, const char *> & del)
{
  m_EscapeDelegate = del;
}

void TextInputContext::SetTabDelegate(const Delegate<void, const char *> & del)
{
  m_TabDelegate = del;
}


bool TextInputContext::IsTextInputActive()
{
  return g_WindowManager.IsTextInputContextActive(m_WindowId, this);
}

double TextInputContext::GetTimeSinceLastUpdate()
{
  return GetTimeSeconds() - m_LastModification;
}

const std::string & TextInputContext::GetCurrentInput()
{
  return m_Text;
}

const std::string & TextInputContext::GetCurrentComposition()
{
  return m_Composition;
}

std::size_t TextInputContext::GetCursorPos()
{
  return m_CursorPos;
}

std::size_t TextInputContext::GetCharacterByteOffset(std::size_t character_index)
{
  if (character_index >= m_CharacterPositions.size())
  {
    return m_Text.length();
  }

  return m_CharacterPositions[character_index].first;
}

std::size_t TextInputContext::GetMultibyteLength(czstr str)
{
  int len = 0;
  while(*str != 0)
  {
    len += (*str & 0xc0) != 0x80;
    str++;
  }

  return len;
}

std::size_t TextInputContext::GetMultibyteCharacterLength(czstr str)
{
  if (*str == 0)
  {
    return 0;
  }

  if ((*str & 0xc0) == 0x80)
  {
    throw std::runtime_error("Invalid mb string");
  }

  str++;
  int len = 1;
  while (*str != 0)
  {
    if ((*str & 0xc0) == 0x80)
    {
      len++;
      str++;
    }
    else
    {
      break;
    }
  }

  return len;
}

void TextInputContext::CommitInput(czstr input)
{
  if (m_AllowFirstInput == false)
  {
    m_AllowFirstInput = true;
    return;
  }

  std::size_t num_characters = GetMultibyteLength(input);

  std::size_t insert_len = strlen(input);
  std::size_t insert_pos = m_CursorPos > 0 ? m_CharacterPositions[m_CursorPos - 1].second : 0;

  std::vector<std::pair<std::size_t, std::size_t>> new_chars;
  std::size_t new_char_pos = insert_pos;

  czstr char_input = input;
  for (std::size_t index = 0; index < num_characters; index++)
  {
    std::size_t new_char_len = GetMultibyteCharacterLength(char_input);
    new_chars.emplace_back(std::make_pair(new_char_pos, new_char_pos + new_char_len));
    char_input += new_char_len;
    new_char_pos += new_char_len;
  }

  for (auto itr = m_CharacterPositions.begin() + m_CursorPos, end = m_CharacterPositions.end(); itr != end; ++itr)
  {
    itr->first += insert_len;
    itr->second += insert_len;
  }

  m_Text.insert(m_Text.begin() + insert_pos, input, input + insert_len);
  m_CharacterPositions.insert(m_CharacterPositions.begin() + m_CursorPos, new_chars.begin(), new_chars.end());
  m_CursorPos += num_characters;
}

void TextInputContext::SetComposition(czstr character)
{
  m_Composition = character;
}

void TextInputContext::HandleKeyPressEvent(int key_sym)
{
  m_LastModification = GetTimeSeconds();

  if (key_sym == SDLK_RETURN)
  {
    HandleEnterPressed();
  }
  else if (key_sym == SDLK_BACKSPACE)
  {
    HandleBackspacePressed();
  }
  else if (key_sym == SDLK_DELETE)
  {
    HandleDeletePressed();
  }
  else if (key_sym == SDLK_TAB)
  {
    HandleTabPressed();
  }
  else if (key_sym == SDLK_ESCAPE)
  {
    HandleEscapePressed();
  }
  else if (key_sym == SDLK_LEFT)
  {
    if (m_Composition.length() == 0 && m_CursorPos != 0)
    {
      m_CursorPos--;
    }
  }
  else if (key_sym == SDLK_RIGHT)
  {
    if (m_Composition.length() == 0 && m_CursorPos < m_CharacterPositions.size())
    {
      m_CursorPos++;
    }
  }
  else if (key_sym == SDLK_HOME)
  {
    HandleHomePressed();
  }
  else if (key_sym == SDLK_END)
  {
    HandleEndPressed();
  }
}

void TextInputContext::HandleEnterPressed()
{
  if (m_EnterDelegate)
  {
    m_EnterDelegate(m_Text.data());
  }
}

void TextInputContext::HandleEscapePressed()
{
  if (m_EscapeDelegate)
  {
    m_EscapeDelegate(m_Text.data());
  }
}

void TextInputContext::HandleTabPressed()
{
  if (m_TabDelegate)
  {
    m_TabDelegate(m_Text.data());
  }
}

void TextInputContext::HandleBackspacePressed()
{
  if (m_CursorPos == 0)
  {
    return;
  }

  if (m_CharacterPositions.size() == 0)
  {
    return;
  }

  if (m_Composition.size() != 0)
  {
    return;
  }

  m_CursorPos--;

  auto slice = m_CharacterPositions[m_CursorPos];
  m_CharacterPositions.erase(m_CharacterPositions.begin() + m_CursorPos);

  m_Text.erase(m_Text.begin() + slice.first, m_Text.begin() + slice.second);

  auto character_len = slice.second - slice.first;

  for (auto itr = m_CharacterPositions.begin() + m_CursorPos, end = m_CharacterPositions.end(); itr != end; ++itr)
  {
    itr->first -= character_len;
    itr->second -= character_len;
  }
}

void TextInputContext::HandleDeletePressed()
{
  if (m_CharacterPositions.size() == 0)
  {
    return;
  }

  if (m_Composition.size() != 0)
  {
    return;
  }

  if (m_CursorPos >= m_CharacterPositions.size())
  {
    return;
  }

  auto slice = m_CharacterPositions[m_CursorPos];
  m_CharacterPositions.erase(m_CharacterPositions.begin() + m_CursorPos);

  m_Text.erase(m_Text.begin() + slice.first, m_Text.begin() + slice.second);

  auto character_len = slice.second - slice.first;

  for (auto itr = m_CharacterPositions.begin() + m_CursorPos, end = m_CharacterPositions.end(); itr != end; ++itr)
  {
    itr->first -= character_len;
    itr->second -= character_len;
  }
}

void TextInputContext::HandleHomePressed()
{
  m_CursorPos = 0;
}

void TextInputContext::HandleEndPressed()
{
  m_CursorPos = m_CharacterPositions.size();
}

