
function InitTestMenu()
  print("Testing menu ")

  local button = PushMenuElement(Button:new())
  button.x = 0
  button.y = 0
  button.width = 100
  button.height = 15
  button.text = "Test"

  local button2 = PushMenuElement(Button:new())
  button2.x = 0
  button2.y = 20
  button2.width = 100
  button2.height = 15
  button2.text = "Test2"

  local input = PushMenuElement(TextInput:new())
  input.x = 0
  input.y = -40
  input.width = 100
  input.height = 15
  input.prompt = "Input"

  local scrollbar = PushMenuElement(ScrollBar:new())
  scrollbar.x = 380
  scrollbar.y = -40
  scrollbar.width = 20
  scrollbar.height = 200

  local chatdisplay = PushMenuElement(ChatDisplay:new())
  chatdisplay.x = 180
  chatdisplay.y = -40
  chatdisplay.width = 200
  chatdisplay.height = 200
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

  CreateDefualtControls();

  local popup = PushMenuElement(ConfirmPopup:new())
  popup.x = -400
  popup.y = -100
  popup.width = 300
  popup.height = 150
  --popup:SetEnabled(false)
  
  local fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  button.fade = false
  button.Pressed = function()
    chatdisplay:AddElement("test", "Test test test test test test test test test")
    update_chat()
  end

  button2.Pressed = function()
    fader:FadeToSolid()
  end
end

