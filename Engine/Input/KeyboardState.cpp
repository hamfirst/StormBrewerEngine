
#include "Engine/EngineCommon.h"
#include "Engine/Input/KeyboardState.h"
#include "Engine/Input/InputState.h"

#include <SDL2/SDL_keyboard.h>

KeyboardState::KeyboardState(NotNullPtr<InputState> input_state) :
  m_InputState(input_state)
{

}

void KeyboardState::CheckDeltaState(bool in_focus, bool text_input_active, bool query_state)
{
  if (query_state)
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

      if (m_PressedLastFrame[index] == 0 && pressed)
      {
        m_PressedThisFrame[index] = true;
      }
      else if (m_PressedThisFrame[index])
      {
        m_PressedThisFrame[index] = false;
      }

      m_PressedLastFrame[index] = pressed;
      m_KeyboardControls[index].SetControlValue(pressed);

      if (m_PressedState[index] = pressed)
      {
        if (m_InputState->m_BinaryControlCallback)
        {
          m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(index));
        }
      }

      m_PressedState[index] = pressed;
    }
  }
  else
  {
    for (int index = 0; index < kNumKeyboardKeys; index++)
    {
      if (m_PressedLastFrame[index] == false && m_PressedState[index] == true)
      {
        m_PressedThisFrame[index] = true;
      }
      else
      {
        m_PressedThisFrame[index] = false;
      }

      m_PressedLastFrame[index] = m_PressedState[index];
    }
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

  m_PressedState[scan_code] = pressed;

  if (m_InputState->m_BinaryControlCallback)
  {
    m_InputState->m_BinaryControlCallback(CreateKeyboardBinding(scan_code));
  }
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

int KeyboardState::ScanCodeFromQtCode(int qt_key_code)
{
  switch (qt_key_code)
  {
  case 0x01000000: //Qt::Key_Escape:
    return SDL_SCANCODE_ESCAPE;
  case 0x01000001: // Qt::Key_Tab:
    return SDL_SCANCODE_TAB;
  case 0x01000002://Qt::Key_Backtab:
    return SDL_SCANCODE_UNKNOWN;
  case 0x01000003://Qt::Key_Backspace:
    return SDL_SCANCODE_BACKSPACE;
  case 0x01000004://Qt::Key_Return:
    return SDL_SCANCODE_RETURN;
  case 0x01000005://Qt::Key_Enter:
    return SDL_SCANCODE_RETURN2;
  case 0x01000006://Qt::Key_Insert:
    return SDL_SCANCODE_INSERT;
  case 0x01000007://Qt::Key_Delete:
    return SDL_SCANCODE_DELETE;
  case 0x01000008://Qt::Key_Pause:
    return SDL_SCANCODE_PAUSE;
  case 0x01000009://Qt::Key_Print:
    return SDL_SCANCODE_PRINTSCREEN;
  case 0x0100000b://Qt::Key_Clear:
    return SDL_SCANCODE_CLEAR;
  case 0x01000010://Qt::Key_Home:
    return SDL_SCANCODE_HOME;
  case 0x01000011://Qt::Key_End:
    return SDL_SCANCODE_END;
  case 0x01000012://Qt::Key_Left:
    return SDL_SCANCODE_LEFT;
  case 0x01000013://Qt::Key_Up:
    return SDL_SCANCODE_UP;
  case 0x01000014://Qt::Key_Right:
    return SDL_SCANCODE_RIGHT;
  case 0x01000015://Qt::Key_Down:
    return SDL_SCANCODE_DOWN;
  case 0x01000016://Qt::Key_PageUp:
    return SDL_SCANCODE_PAGEUP;
  case 0x01000017://Qt::Key_PageDown:
    return SDL_SCANCODE_PAGEDOWN;
  case 0x01000020://Qt::Key_Shift:
    return SDL_SCANCODE_LSHIFT;
  case 0x01000021://Qt::Key_Control:
    return SDL_SCANCODE_LCTRL;
  case 0x01000022://Qt::Key_Meta:
    return SDL_SCANCODE_MENU;
  case 0x01000023://Qt::Key_Alt:
    return SDL_SCANCODE_LALT;
  case 0x01000024://Qt::Key_CapsLock:
    return SDL_SCANCODE_CAPSLOCK;
  case 0x01000025://Qt::Key_NumLock:
    return SDL_SCANCODE_NUMLOCKCLEAR;
  case 0x01000026://Qt::Key_ScrollLock:
    return SDL_SCANCODE_SCROLLLOCK;
  case 0x01000030://Qt::Key_F1:
    return SDL_SCANCODE_F1;
  case 0x01000031://Qt::Key_F2:
    return SDL_SCANCODE_F2;
  case 0x01000032://Qt::Key_F3:
    return SDL_SCANCODE_F3;
  case 0x01000033://Qt::Key_F4:
    return SDL_SCANCODE_F4;
  case 0x01000034://Qt::Key_F5:
    return SDL_SCANCODE_F5;
  case 0x01000035://Qt::Key_F6:
    return SDL_SCANCODE_F6;
  case 0x01000036://Qt::Key_F7:
    return SDL_SCANCODE_F7;
  case 0x01000037://Qt::Key_F8:
    return SDL_SCANCODE_F8;
  case 0x01000038://Qt::Key_F9:
    return SDL_SCANCODE_F9;
  case 0x01000039://Qt::Key_F10:
    return SDL_SCANCODE_F10;
  case 0x0100003a://Qt::Key_F11:
    return SDL_SCANCODE_F11;
  case 0x0100003b://Qt::Key_F12:
    return SDL_SCANCODE_F12;
  case 0x0100003c://Qt::Key_F13:
    return SDL_SCANCODE_F13;
  case 0x0100003d://Qt::Key_F14:
    return SDL_SCANCODE_F14;
  case 0x0100003e://Qt::Key_F15:
    return SDL_SCANCODE_F15;
  case 0x0100003f://Qt::Key_F16:
    return SDL_SCANCODE_F16;
  case 0x01000040://Qt::Key_F17:
    return SDL_SCANCODE_F17;
  case 0x01000041://Qt::Key_F18:
    return SDL_SCANCODE_F18;
  case 0x01000042://Qt::Key_F19:
    return SDL_SCANCODE_F19;
  case 0x01000043://Qt::Key_F20:
    return SDL_SCANCODE_F20;
  case 0x01000044://Qt::Key_F21:
    return SDL_SCANCODE_F21;
  case 0x01000045://Qt::Key_F22:
    return SDL_SCANCODE_F22;
  case 0x01000046://Qt::Key_F23:
    return SDL_SCANCODE_F23;
  case 0x01000047://Qt::Key_F24:
    return SDL_SCANCODE_F24;
  case 0x01000055://Qt::Key_Menu:
    return SDL_SCANCODE_APPLICATION;
  case 0x01000058://Qt::Key_Help:
    return SDL_SCANCODE_HELP;
  case 0x20://Qt::Key_Space:
    return SDL_SCANCODE_SPACE;
  case 0x2a://Qt::Key_Asterisk:
    return SDL_SCANCODE_KP_MULTIPLY;
  case 0x2b://Qt::Key_Plus:
    return SDL_SCANCODE_KP_PLUS;
  case 0x2c://Qt::Key_Comma:
    return SDL_SCANCODE_COMMA;
  case 0x2d://Qt::Key_Minus:
    return SDL_SCANCODE_MINUS;
  case 0x2e://Qt::Key_Period:
    return SDL_SCANCODE_PERIOD;
  case 0x2f://Qt::Key_Slash:
    return SDL_SCANCODE_SLASH;
  case 0x30://Qt::Key_0:
    return SDL_SCANCODE_0;
  case 0x31://Qt::Key_1:
    return SDL_SCANCODE_1;
  case 0x32://Qt::Key_2:
    return SDL_SCANCODE_2;
  case 0x33://Qt::Key_3:
    return SDL_SCANCODE_3;
  case 0x34://Qt::Key_4:
    return SDL_SCANCODE_4;
  case 0x35://Qt::Key_5:
    return SDL_SCANCODE_5;
  case 0x36://Qt::Key_6:
    return SDL_SCANCODE_6;
  case 0x37://Qt::Key_7:
    return SDL_SCANCODE_7;
  case 0x38://Qt::Key_8:
    return SDL_SCANCODE_8;
  case 0x39://Qt::Key_9:
    return SDL_SCANCODE_9;
  case 0x3a://Qt::Key_Colon:
    return SDL_SCANCODE_UNKNOWN;
  case 0x3b://Qt::Key_Semicolon:
    return SDL_SCANCODE_SEMICOLON;
  case 0x41://Qt::Key_A:
    return SDL_SCANCODE_A;
  case 0x42://Qt::Key_B:
    return SDL_SCANCODE_B;
  case 0x43://Qt::Key_C:
    return SDL_SCANCODE_C;
  case 0x44://Qt::Key_D:
    return SDL_SCANCODE_D;
  case 0x45://Qt::Key_E:
    return SDL_SCANCODE_E;
  case 0x46://Qt::Key_F:
    return SDL_SCANCODE_F;
  case 0x47://Qt::Key_G:
    return SDL_SCANCODE_G;
  case 0x48://Qt::Key_H:
    return SDL_SCANCODE_H;
  case 0x49://Qt::Key_I:
    return SDL_SCANCODE_I;
  case 0x4a://Qt::Key_J:
    return SDL_SCANCODE_J;
  case 0x4b://Qt::Key_K:
    return SDL_SCANCODE_K;
  case 0x4c://Qt::Key_L:
    return SDL_SCANCODE_L;
  case 0x4d://Qt::Key_M:
    return SDL_SCANCODE_M;
  case 0x4e://Qt::Key_N:
    return SDL_SCANCODE_N;
  case 0x4f://Qt::Key_O:
    return SDL_SCANCODE_O;
  case 0x50://Qt::Key_P:
    return SDL_SCANCODE_P;
  case 0x51://Qt::Key_Q:
    return SDL_SCANCODE_Q;
  case 0x52://Qt::Key_R:
    return SDL_SCANCODE_R;
  case 0x53://Qt::Key_S:
    return SDL_SCANCODE_S;
  case 0x54://Qt::Key_T:
    return SDL_SCANCODE_T;
  case 0x55://Qt::Key_U:
    return SDL_SCANCODE_U;
  case 0x56://Qt::Key_V:
    return SDL_SCANCODE_V;
  case 0x57://Qt::Key_W:
    return SDL_SCANCODE_W;
  case 0x58://Qt::Key_X:
    return SDL_SCANCODE_X;
  case 0x59://Qt::Key_Y:
    return SDL_SCANCODE_Y;
  case 0x5a://Qt::Key_Z:
    return SDL_SCANCODE_Z;
  case 0x0100117e://Qt::Key_Mode_switch:
    return SDL_SCANCODE_MODE;
  case 0x01000061://Qt::Key_Back:
    return SDL_SCANCODE_AC_BACK;
  case 0x01000062://Qt::Key_Forward:
    return SDL_SCANCODE_AC_FORWARD;
  case 0x01000063://Qt::Key_Stop:
    return SDL_SCANCODE_AC_STOP;
  case 0x01000064://Qt::Key_Refresh:
    return SDL_SCANCODE_AC_REFRESH;
  case 0x01000070://Qt::Key_VolumeDown:
    return SDL_SCANCODE_VOLUMEDOWN;
  case 0x01000071://Qt::Key_VolumeMute:
    return SDL_SCANCODE_MUTE;
  case 0x01000072://Qt::Key_VolumeUp:
    return SDL_SCANCODE_VOLUMEUP;
  }

  return SDL_SCANCODE_UNKNOWN;
}

NullOptPtr<void> KeyboardState::GetControlBinding(const ControlHandle & handle)
{
  return m_KeyboardControls[handle.m_ControlId.m_Index].GetControlBinding(handle.m_Control);
}
