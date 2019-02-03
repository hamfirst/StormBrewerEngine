
function InitStagingMenu()

  local quit = PushMenuElement(Button:new())
  quit.x = 250
  quit.y = -220
  quit.width = 150
  quit.height = 20
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
        game:Ready(true)
      else
        self.text = "Ready Up"
        game:Ready(false)
      end

      Button.Draw(self)

      if self.toggled then
        ui:DrawTextureTint(player_ready_icon, 40, 11, 0, 0, 0, 0.6)
      end
    end
  end

  if game.allow_map_change then
    mapchange = PushMenuElement(Button:new())
    mapchange.x = 250
    mapchange.y = -160
    mapchange.width = 150
    mapchange.height = 20
    mapchange.text = "Change Map Settings"

    if not game.allow_ready then
      mapchange.height = 60
    end
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
    game_code.text = "Game Code: " .. game.game_code
    game_code.x = -380
    game_code.y = 155
    game_code.width = 500
    game_code.height = 50
    game_code.centered = false
  end

  if game.allow_gametimer ~= nil then
    local game_timer = PushMenuElement(Label:new())
    game_timer.x = 220
    game_timer.y = 145
    game_timer.width = 200
    game_timer.height = 50

    function game_timer:Update(dt)
      game_timer.text = "Game Starts In: " .. game:GetGameTimer()
    end
  end

  if game.allow_loadout then
    local loadout = PushMenuElement(Loadout:new())
    loadout.x = -402
    loadout.y = -90
    loadout.width = 640
    loadout.height = 250

    if not game.allow_chat then
      loadout.y = -220
      loadout.height = 380
    end
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

    if not game.allow_loadout then
      frame.height = frame.height + 260
      scrollbar.height = scrollbar.height + 260
      chatdisplay.height = chatdisplay.height + 260
    end

    scrollbar.ValueChanged = function()
      chatdisplay.scroll_offset = scrollbar.value
    end

    scrollbar:SetScrollArea(chatdisplay.height, chatdisplay.total_height)
    scrollbar:ScrollToBottom()

    AddChatMessage = function(name, text)
      chatdisplay:AddElement(name, text)
      local scroll = scrollbar:IsScrolledToBottom()

      scrollbar:SetScrollArea(chatdisplay.height, chatdisplay.total_height)

      if scroll then
        scrollbar:ScrollToBottom()
      end
    end

    input.EnterPressed = function()
      local text = input:GetText()
      input:Clear()
      game:SendChat(text)

      if in_editor then
        AddChatMessage("test", text)
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

  if game.allow_mapsettings then
    local map_settings = PushMenuElement(MapInfo:new())
    map_settings.x = 88
    map_settings.y = 170
    map_settings.width = 150
    map_settings.height = 60
    map_settings.header_padding = 2
  end

  CreateDefualtControls()
  CreateContextMenu()
  CreatePopupFader()

  if game.allow_map_change then
    local mappopup = PushMenuElement(Popup:new())
    mappopup.x = -250
    mappopup.y = -200
    mappopup.width = 500
    mappopup.height = 420

    function mappopup:CreateChildren()
      ConfirmPopup.CreateChildren(self)

      self.mapsettings = self:PushChild(MapSettings:new())
      self.mapsettings.x = 5
      self.mapsettings.width = self.width - 10
      self.mapsettings.y = 50
      self.mapsettings.height = self.height - 55
    end

    function mappopup:OkayPressed()
      game:CommitMapChanges()
    end

    function mappopup:CancelPressed()
      game:CancelMapChanges()
    end

    mapchange.fade = false
    mapchange.Pressed = function()
      mappopup:FadeIn()
      mappopup.mapsettings:InitMapOptions()
    end
  end

  local quitpopup = PushMenuElement(ConfirmPopup:new())
  quitpopup.x = -150
  quitpopup.y = -75
  quitpopup.width = 300
  quitpopup.height = 150
  quitpopup.text = "Quick Back to Main Menu?"
  
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
