
function InitStagingMenu()

  local quit = PushMenuElement(Button:new())
  quit.x = 250
  quit.y = -220
  quit.width = 150
  quit.height = 15
  quit.text = "Back To Main Menu"

  if game.allow_ready then
    local ready = PushMenuElement(Button:new())
    ready.x = 250
    ready.y = -140
    ready.width = 150
    ready.height = 40
    ready.text = "Ready Up"
    ready.toggleable = true

    function ready:Draw()

      if self.toggled then
        self.text = "Ready"
      else
        self.text = "Ready Up"
      end

      Button.Draw(self)

      if self.toggled then
        ui:DrawTextureTint(player_ready_icon, 24, 11, 0, 0, 0, 0.6)
      end
    end
  end

  if game.allow_map_change then
    mapchange = PushMenuElement(Button:new())
    mapchange.x = 250
    mapchange.y = -160
    mapchange.width = 150
    mapchange.height = 15
    mapchange.text = "Change Map Settings"
  end

  if game.game_name ~= nil and game.game_name ~= "" then
    local game_name = PushMenuElement(Label:new())
    game_name.font = large_header_font
    game_name.text = game.game_name
    game_name.x = -380
    game_name.y = 180
    game_name.width = 500
    game_name.height = 50
    game_name.centered = false
  end

  if game.game_code ~= nil and game.game_code ~= "" then
    local game_code = PushMenuElement(Label:new())
    game_code.text = "Game Code: " ..game.game_code
    game_code.x = -350
    game_code.y = 155
    game_code.width = 500
    game_code.height = 50
    game_code.centered = false
  end

  if game.allow_loadout then
    local loadout = PushMenuElement(Loadout:new())
    loadout.x = -402
    loadout.y = -90
    loadout.width = 640
    loadout.height = 250
  end

  if game.allow_chat then
    local frame = PushMenuElement(Frame:new())
    frame.x = -402
    frame.y = -222
    frame.width = 640
    frame.height = 124

    local input = PushMenuElement(TextInput:new())
    input.x = -400
    input.y = -220
    input.width = 636
    input.height = 15
    input.prompt = "Enter Chat Here"

    local scrollbar = PushMenuElement(ScrollBar:new())
    scrollbar.x = 220
    scrollbar.y = -205
    scrollbar.width = 16
    scrollbar.height = 105

    local chatdisplay = PushMenuElement(ChatDisplay:new())
    chatdisplay.x = -398
    chatdisplay.y = -200
    chatdisplay.width = 446
    chatdisplay.height = 100
    chatdisplay.font = chat_font
    chatdisplay.scroll_proxy = scrollbar

    scrollbar.ValueChanged = function()
      chatdisplay.scroll_offset = scrollbar.value
    end

    if in_editor then
      chatdisplay:AddElement("test", "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
      chatdisplay:AddElement("test", "test")
    end

    scrollbar:SetScrollArea(chatdisplay.height, chatdisplay.total_height)
    scrollbar:ScrollToBottom()

    input.EnterPressed = function()
      local text = input:GetText()
      input:Clear()
      game:SendChat(text)
    end

    AddChatMessage = function(name, text)
      chatdisplay:AddElement(name, text)
      local scroll = scrollbar:IsScrolledToBottom()

      scrollbar:SetScrollArea(chatdisplay.height, chatdisplay.total_height)

      if scroll then
        scrollbar:ScrollToBottom()
      end
    end
  end

  if game.allow_playerlist then
    local player_list = PushMenuElement(PlayerList:new())
    player_list.x = 250
    player_list.y = -90
    player_list.width = 150
    player_list.height = 250
  end

  CreateDefualtControls()
  CreateContextMenu()
  CreatePopupFader()

  if game.allow_map_change then
    local mappopup = PushMenuElement(Popup:new())
    mappopup.x = -250
    mappopup.y = -175
    mappopup.width = 500
    mappopup.height = 350

    function mappopup:CreateChildren()
      ConfirmPopup.CreateChildren(self)

      self.mapsettings = self:PushChild(MapSettings:new())
      self.mapsettings.x = 5
      self.mapsettings.width = self.width - 10
      self.mapsettings.y = 50
      self.mapsettings.height = self.height - 55
    end

    function mappopup:OkayPressed()
    end

    function mappopup:CancelPressed()
    end

    mapchange.fade = false
    mapchange.Pressed = function()
      mappopup:FadeIn()
    end
  end

  local quitpopup = PushMenuElement(ConfirmPopup:new())
  quitpopup.x = -150
  quitpopup.y = -75
  quitpopup.width = 300
  quitpopup.height = 150
  
  local fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  quit.fade = false
  quit.Pressed = function()
    quitpopup:FadeIn()
  end

  quitpopup.OkayPressed = function()
    fader:FadeToSolidThen(function() game:Quit() end)
  end
end
