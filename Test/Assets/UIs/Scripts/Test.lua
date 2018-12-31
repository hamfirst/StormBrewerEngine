


function InitTestMenu()
  print("Testing menu ")

  local button = PushMenuElement(Button:new())
  button.x = 0
  button.y = 0
  button.width = 100
  button.height = 15
  button.text = "Test Chat"

  local button2 = PushMenuElement(Button:new())
  button2.x = 0
  button2.y = 20
  button2.width = 100
  button2.height = 15
  button2.text = "Test Fade"

  local button3 = PushMenuElement(Button:new())
  button3.x = 0
  button3.y = 40
  button3.width = 100
  button3.height = 15
  button3.text = "Test Menu"

  local button4 = PushMenuElement(Button:new())
  button4.x = 0
  button4.y = 60
  button4.width = 100
  button4.height = 15
  button4.text = "Test Popup"

  local input = PushMenuElement(TextInput:new())
  input.x = -80
  input.y = -220
  input.width = 200
  input.height = 15
  input.prompt = "Input"

  local scrollbar = PushMenuElement(ScrollBar:new())
  scrollbar.x = 120
  scrollbar.y = -200
  scrollbar.width = 20
  scrollbar.height = 100

  local chatdisplay = PushMenuElement(ChatDisplay:new())
  chatdisplay.x = -80
  chatdisplay.y = -200
  chatdisplay.width = 200
  chatdisplay.height = 100
  chatdisplay.font = chat_font
  chatdisplay.scroll_proxy = scrollbar
  chatdisplay:AddElement("test", "Test test test test test test test test test")
  chatdisplay:AddElement("test", "Test test test test test test test test test")
  chatdisplay:AddElement("test", "Test test test test test test test test test")

  scrollbar.ValueChanged = function()
    chatdisplay.scroll_offset = scrollbar.value
  end

  local update_chat = function()
    local scroll = scrollbar:IsScrolledToBottom()

    scrollbar:SetScrollArea(chatdisplay.height, chatdisplay.total_height)

    if scroll then
      scrollbar:ScrollToBottom()
    end
  end

  update_chat()

  local player_list = PushMenuElement(PlayerList:new())
  player_list.x = 250
  player_list.y = -200
  player_list.width = 150
  player_list.height = 350

  CreateDefualtControls();
  CreateContextMenu();

  local popup = PushMenuElement(ConfirmPopup:new())
  popup.x = -400
  popup.y = -100
  popup.width = 300
  popup.height = 150
  
  local fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  input.EnterPressed = function()
    local text = input:GetText()
    input:Clear()

    chatdisplay:AddElement("test", text)
    update_chat()
  end

  button.fade = false
  button.Pressed = function()
    chatdisplay:AddElement("test", "Test test test test test test test test test")
    update_chat()
  end

  button2.Pressed = function()
    fader:FadeToSolid()
  end

  button3.fade = false
  button3.Pressed = function()
    context_menu:Reset()
    context_menu:PushMenuAction("Option 1", function() print("Option 1") end)
    context_menu:PushMenuAction("Option 2", function() print("Option 2") end)
    context_menu:PushMenuAction("Option 3", function() print("Option 3") end)
    context_menu:Show(-80, 30)
  end

  button4.fade = false
  button4.Pressed = function()
    popup:FadeIn()
  end
end

