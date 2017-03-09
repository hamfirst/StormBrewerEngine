
#include "Engine/EngineCommon.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Input/InputState.h"

#include <SDL2/SDL_keyboard.h>


KeyboardState::KeyboardState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{

}

void KeyboardState::CheckDeltaState(bool in_focus, bool text_input_active)
{
  int num_keys = 0;
  const uint8_t * keys = SDL_GetKeyboardState(&num_keys);

  for (int index = 0; index < num_keys; index++)
  {
    bool pressed = keys[index] && in_focus;

    if (text_input_active && m_PressedState[index] == false && ScanCodeBlockeByTextInput(index))
    {
      pressed = false;
    }

    m_KeyboardControls[index].SetControlValue(pressed);

    if (m_PressedState[index] == 0 && pressed)
    {
      m_PressedThisFrame[index] = true;
      if (m_InputState->m_BinaryControlCallback)
      {
        m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(index));
      }
    }
    else
    {
      m_PressedThisFrame[index] = false;
    }

    m_PressedState[index] = pressed;
  }
}

BinaryControlHandle KeyboardState::AddKeyBinding(int scan_code, int priority, ControlBindingMode mode, const Delegate<void, bool> & callback)
{
  Handle handle = m_KeyboardControls[scan_code].CreateControlBinding(priority, mode, callback);
  return BinaryControlHandle(m_InputState, handle, CreateKeyboardBinding(scan_code));
}

void KeyboardState::RemoveKeyBinding(BinaryControlHandle handle)
{
  m_KeyboardControls[handle.m_ControlId.m_Index].RemoveControlBinding(handle.m_Control);
}

bool KeyboardState::GetKeyState(int scan_code)
{
  if (scan_code >= kNumKeyboardKeys)
  {
    return false;
  }

  return m_PressedState[scan_code];
}

bool KeyboardState::GetKeyPressedThisFrame(int scan_code)
{
  if (scan_code >= kNumKeyboardKeys)
  {
    return false;
  }

  return m_PressedThisFrame[scan_code];
}

void KeyboardState::HandleKeyPressMessage(int scan_code, bool pressed, bool text_input_active)
{
  if (text_input_active && m_PressedState[scan_code] == false && ScanCodeBlockeByTextInput(scan_code))
  {
    pressed = false;
  }

  if (m_KeyboardControls[scan_code].SetControlValue(pressed))
  {
    m_PassThroughCallbacks.Call(pressed, CreateKeyboardBinding(scan_code));
  }

  if (m_PressedState[scan_code] == 0 && pressed)
  {
    m_PressedThisFrame[scan_code] = true;
    if (m_InputState->m_BinaryControlCallback)
    {
      m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(scan_code));
    }
  }
  else
  {
    m_PressedThisFrame[scan_code] = false;
  }

  m_PressedState[scan_code] = pressed;
}

DelegateLink<void, bool, ControlId> KeyboardState::RegisterPassThroughDelegate(const Delegate<void, bool, ControlId> & del)
{
  return m_PassThroughCallbacks.AddDelegate(del);
}

czstr KeyboardState::GetKeyNameForScanCode(int scan_code)
{
  const char * key_name = SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode)scan_code));
  return key_name;
}

bool KeyboardState::ScanCodeBlockeByTextInput(int scan_code)
{
  if ((scan_code >= SDL_SCANCODE_A && scan_code <= SDL_SCANCODE_Z) ||
    (scan_code >= SDL_SCANCODE_1 && scan_code <= SDL_SCANCODE_0) ||
    (scan_code >= SDL_SCANCODE_SPACE && scan_code <= SDL_SCANCODE_SLASH) ||
    (scan_code >= SDL_SCANCODE_RIGHT && scan_code <= SDL_SCANCODE_UP))
  {
    return true;
  }

  return false;
}

int KeyboardState::ScanCodeFromJavascriptCode(int javascript_key_code)
{
  switch(javascript_key_code)
  {
  case 0:
  case 1:
  case 2:
    return SDL_SCANCODE_UNKNOWN;
  case 3:
    return SDL_SCANCODE_CANCEL;
  case 4:
  case 5:
    return SDL_SCANCODE_UNKNOWN;
  case 6:
    return SDL_SCANCODE_HELP;
  case 7:
    return SDL_SCANCODE_UNKNOWN;
  case 8:
    return SDL_SCANCODE_BACKSPACE;
  case 9:
    return SDL_SCANCODE_TAB;
  case 10:
  case 11:
    return SDL_SCANCODE_UNKNOWN;
  case 12:
    return SDL_SCANCODE_CLEAR;
  case 13:
    return SDL_SCANCODE_RETURN;
  case 14:
    return SDL_SCANCODE_RETURN2;
  case 15:
    return SDL_SCANCODE_UNKNOWN;
  case 16:
    return SDL_SCANCODE_LSHIFT;
  case 17:
    return SDL_SCANCODE_LCTRL;
  case 18:
    return SDL_SCANCODE_LALT;
  case 19:
    return SDL_SCANCODE_PAUSE;
  case 20:
    return SDL_SCANCODE_CAPSLOCK;
  case 21:
    return SDL_SCANCODE_INTERNATIONAL1;
  case 22:
    return SDL_SCANCODE_INTERNATIONAL2;
  case 23:
    return SDL_SCANCODE_INTERNATIONAL4;
  case 24:
    return SDL_SCANCODE_INTERNATIONAL5;
  case 25:
    return SDL_SCANCODE_INTERNATIONAL6;
  case 26:
    return SDL_SCANCODE_UNKNOWN;
  case 27:
    return SDL_SCANCODE_ESCAPE;
  case 28:
  case 29:
  case 30:
    return SDL_SCANCODE_UNKNOWN;
  case 31:
    return SDL_SCANCODE_MODE;
  case 32:
    return SDL_SCANCODE_SPACE;
  case 33:
    return SDL_SCANCODE_PAGEUP;
  case 34:
    return SDL_SCANCODE_PAGEDOWN;
  case 35:
    return SDL_SCANCODE_END;
  case 36:
    return SDL_SCANCODE_HOME;
  case 37:
    return SDL_SCANCODE_LEFT;
  case 38:
    return SDL_SCANCODE_UP;
  case 39:
    return SDL_SCANCODE_RIGHT;
  case 40:
    return SDL_SCANCODE_DOWN;
  case 41:
    return SDL_SCANCODE_UNKNOWN;
  case 42:
    return SDL_SCANCODE_UNKNOWN;
  case 43:
    return SDL_SCANCODE_EXECUTE;
  case 44:
    return SDL_SCANCODE_PRINTSCREEN;
  case 45:
    return SDL_SCANCODE_INSERT;
  case 46:
    return SDL_SCANCODE_DELETE;
  case 47:
    return SDL_SCANCODE_UNKNOWN;
  case 48:
    return SDL_SCANCODE_0;
  case 49:
    return SDL_SCANCODE_1;
  case 50:
    return SDL_SCANCODE_2;
  case 51:
    return SDL_SCANCODE_3;
  case 52:
    return SDL_SCANCODE_4;
  case 53:
    return SDL_SCANCODE_5;
  case 54:
    return SDL_SCANCODE_6;
  case 55:
    return SDL_SCANCODE_7;
  case 56:
    return SDL_SCANCODE_8;
  case 57:
    return SDL_SCANCODE_9;
  case 58:
    return SDL_SCANCODE_SEMICOLON;
  case 59:
    return SDL_SCANCODE_SEMICOLON;
  case 60:
    return SDL_SCANCODE_UNKNOWN;
  case 61:
    return SDL_SCANCODE_EQUALS;
  case 62:
    return SDL_SCANCODE_UNKNOWN;
  case 63:
    return SDL_SCANCODE_UNKNOWN;
  case 65:
    return SDL_SCANCODE_A;
  case 66:
    return SDL_SCANCODE_B;
  case 67:
    return SDL_SCANCODE_C;
  case 68:
    return SDL_SCANCODE_D;
  case 69:
    return SDL_SCANCODE_E;
  case 70:
    return SDL_SCANCODE_F;
  case 71:
    return SDL_SCANCODE_G;
  case 72:
    return SDL_SCANCODE_H;
  case 73:
    return SDL_SCANCODE_I;
  case 74:
    return SDL_SCANCODE_J;
  case 75:
    return SDL_SCANCODE_K;
  case 76:
    return SDL_SCANCODE_L;
  case 77:
    return SDL_SCANCODE_M;
  case 78:
    return SDL_SCANCODE_N;
  case 79:
    return SDL_SCANCODE_O;
  case 80:
    return SDL_SCANCODE_P;
  case 81:
    return SDL_SCANCODE_Q;
  case 82:
    return SDL_SCANCODE_R;
  case 83:
    return SDL_SCANCODE_S;
  case 84:
    return SDL_SCANCODE_T;
  case 85:
    return SDL_SCANCODE_U;
  case 86:
    return SDL_SCANCODE_V;
  case 87:
    return SDL_SCANCODE_W;
  case 88:
    return SDL_SCANCODE_X;
  case 89:
    return SDL_SCANCODE_Y;
  case 90:
    return SDL_SCANCODE_Z;
  case 91:
    return SDL_SCANCODE_RGUI;
  case 92:
    return SDL_SCANCODE_UNKNOWN;
  case 93:
    return SDL_SCANCODE_APPLICATION;
  case 94:
    return SDL_SCANCODE_UNKNOWN;
  case 95:
    return SDL_SCANCODE_SLEEP;
  case 96:
    return SDL_SCANCODE_KP_0;
  case 97:
    return SDL_SCANCODE_KP_1;
  case 98:
    return SDL_SCANCODE_KP_2;
  case 99:
    return SDL_SCANCODE_KP_3;
  case 100:
    return SDL_SCANCODE_KP_4;
  case 101:
    return SDL_SCANCODE_KP_5;
  case 102:
    return SDL_SCANCODE_KP_6;
  case 103:
    return SDL_SCANCODE_KP_7;
  case 104:
    return SDL_SCANCODE_KP_8;
  case 105:
    return SDL_SCANCODE_KP_9;
  case 106:
    return SDL_SCANCODE_KP_MULTIPLY;
  case 107:
    return SDL_SCANCODE_KP_PLUS;
  case 108:
    return SDL_SCANCODE_UNKNOWN;
  case 109:
    return SDL_SCANCODE_KP_MINUS;
  case 110:
    return SDL_SCANCODE_KP_PERIOD;
  case 111:
    return SDL_SCANCODE_KP_DIVIDE;
  case 112:
    return SDL_SCANCODE_F1;
  case 113:
    return SDL_SCANCODE_F2;
  case 114:
    return SDL_SCANCODE_F3;
  case 115:
    return SDL_SCANCODE_F4;
  case 116:
    return SDL_SCANCODE_F5;
  case 117:
    return SDL_SCANCODE_F6;
  case 118:
    return SDL_SCANCODE_F7;
  case 119:
    return SDL_SCANCODE_F8;
  case 120:
    return SDL_SCANCODE_F9;
  case 121:
    return SDL_SCANCODE_F10;
  case 122:
    return SDL_SCANCODE_F11;
  case 123:
    return SDL_SCANCODE_F12;
  case 124:
    return SDL_SCANCODE_F13;
  case 125:
    return SDL_SCANCODE_F14;
  case 126:
    return SDL_SCANCODE_F15;
  case 127:
    return SDL_SCANCODE_F16;
  case 128:
    return SDL_SCANCODE_F17;
  case 129:
    return SDL_SCANCODE_F18;
  case 130:
    return SDL_SCANCODE_F19;
  case 131:
    return SDL_SCANCODE_F20;
  case 132:
    return SDL_SCANCODE_F21;
  case 133:
    return SDL_SCANCODE_F22;
  case 134:
    return SDL_SCANCODE_F23;
  case 135:
    return SDL_SCANCODE_F24;
  case 136:
  case 137:
  case 138:
  case 139:
  case 140:
  case 141:
  case 142:
  case 143:
    return SDL_SCANCODE_UNKNOWN;
  case 144:
    return SDL_SCANCODE_NUMLOCKCLEAR;
  case 145:
    return SDL_SCANCODE_SCROLLLOCK;
  case 146:
  case 147:
  case 148:
  case 149:
  case 150:
  case 151:
  case 152:
  case 153:
  case 154:
  case 155:
  case 156:
  case 157:
  case 158:
  case 159:
  case 160:
  case 161:
  case 162:
  case 163:
  case 164:
  case 165:
  case 166:
  case 167:
  case 168:
  case 169:
  case 170:
  case 171:
  case 172:
  case 173:
  case 174:
  case 175:
  case 176:
  case 177:
  case 178:
  case 179:
  case 180:
  case 181:
    return SDL_SCANCODE_UNKNOWN;
  case 182:
    return SDL_SCANCODE_VOLUMEDOWN;
  case 183:
    return SDL_SCANCODE_VOLUMEUP;
  case 184:
  case 185:
    return SDL_SCANCODE_UNKNOWN;
  case 186:
    return SDL_SCANCODE_SEMICOLON;
  case 187:
    return SDL_SCANCODE_EQUALS;
  case 188:
    return SDL_SCANCODE_COMMA;
  case 189:
    return SDL_SCANCODE_MINUS;
  case 190:
    return SDL_SCANCODE_PERIOD;
  case 191:
    return SDL_SCANCODE_SLASH;
  case 192:
    return SDL_SCANCODE_GRAVE;
  case 193:
  case 194:
  case 195:
  case 196:
  case 197:
  case 198:
  case 199:
  case 200:
  case 201:
  case 202:
  case 203:
  case 204:
  case 205:
  case 206:
  case 207:
  case 208:
  case 209:
  case 210:
  case 211:
  case 212:
  case 213:
  case 214:
  case 215:
  case 216:
  case 217:
  case 218:
    return SDL_SCANCODE_UNKNOWN;
  case 219:
    return SDL_SCANCODE_LEFTBRACKET;
  case 220:
    return SDL_SCANCODE_BACKSLASH;
  case 221:
    return SDL_SCANCODE_RIGHTBRACKET;
  case 222:
    return SDL_SCANCODE_APOSTROPHE;

  case 10016:
    return SDL_SCANCODE_RSHIFT;
  case 10017:
    return SDL_SCANCODE_RCTRL;
  case 10018:
    return SDL_SCANCODE_RALT;

        //"", // [223]
        //"META", // [224]
        //"ALTGR", // [225]
        //"", // [226]
        //"WIN_ICO_HELP", // [227]
        //"WIN_ICO_00", // [228]
        //"", // [229]
        //"WIN_ICO_CLEAR", // [230]
        //"", // [231]
        //"", // [232]
        //"WIN_OEM_RESET", // [233]
        //"WIN_OEM_JUMP", // [234]
        //"WIN_OEM_PA1", // [235]
        //"WIN_OEM_PA2", // [236]
        //"WIN_OEM_PA3", // [237]
        //"WIN_OEM_WSCTRL", // [238]
        //"WIN_OEM_CUSEL", // [239]
        //"WIN_OEM_ATTN", // [240]
        //"WIN_OEM_FINISH", // [241]
        //"WIN_OEM_COPY", // [242]
        //"WIN_OEM_AUTO", // [243]
        //"WIN_OEM_ENLW", // [244]
        //"WIN_OEM_BACKTAB", // [245]
        //"ATTN", // [246]
        //"CRSEL", // [247]
        //"EXSEL", // [248]
        //"EREOF", // [249]
        //"PLAY", // [250]
        //"ZOOM", // [251]
        //"", // [252]
        //"PA1", // [253]
        //"WIN_OEM_CLEAR", // [254]
        //"" // [255]
  default:
    return SDL_SCANCODE_UNKNOWN;
  }
}

NullOptPtr<void> KeyboardState::GetControlBinding(const ControlHandle & handle)
{
  return m_KeyboardControls[handle.m_ControlId.m_Index].GetControlBinding(handle.m_Control);
}
