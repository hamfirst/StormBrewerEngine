
function InitStagingMenu()

  local quit = PushMenuElement(Button:new())
  quit.x = screen_end_x - 80
  quit.y = screen_start_y + 5
  quit.width = 70
  quit.height = font_height
  quit.text = "Quit"

  if game.allow_ready then
    local ready = PushMenuElement(Button:new())
    ready.x = screen_end_x - 140
    ready.y = screen_start_y + 60
    ready.width = 130
    ready.height = 25
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
        ui:DrawTextureTint(player_ready_icon, ready.width / 2 - 35, ready.height / 2 - 7, 0, 0, 0, 0.6)
      end
    end

    function ready:ToggleOn()
      game:Ready(true)
    end

    function ready:ToggleOff()
      game:Ready(false)
    end
  end

  if game.allow_map_change then
    mapchange = PushMenuElement(Button:new())
    mapchange.x = screen_end_x - 140
    mapchange.y = screen_start_y + 60 - font_height - 2
    mapchange.width = 130
    mapchange.height = font_height
    mapchange.text = "Settings"

    if not game.allow_ready then
      mapchange.y = screen_start_y + 60
    end
  end

  if game.game_name ~= nil and game.game_name ~= "" then
    local game_name = PushMenuElement(Label:new())
    game_name.font = large_header_font
    game_name.text = game.game_name
    game_name.x = screen_start_x + 5
    game_name.y = screen_end_y - large_header_font_height
    game_name.width = 500
    game_name.height = large_header_font_height
    game_name.centered = false
  end

  if game.game_code ~= nil and game.game_code ~= "" then
    local game_code = PushMenuElement(Label:new())
    game_code.text = "Game Code: " .. game.game_code
    game_code.x = screen_start_x + 5
    game_code.y = screen_end_y - large_header_font_height - font_height - 2
    game_code.width = 500
    game_code.height = font_height
    game_code.centered = false
  end

  if game.allow_gametimer ~= nil then
    local game_timer = PushMenuElement(Label:new())
    game_timer.x = screen_end_x - 150
    game_timer.y = screen_end_y - font_height
    game_timer.width = 150
    game_timer.height = font_height

    function game_timer:Update(dt)

      local game_timer_text = game:GetGameTimer();
      if game_timer_text ~= "" then
        game_timer.text = "Game Starts In: " .. game:GetGameTimer()
      else
        game_timer.text = ""
      end
    end
  end

  if game.allow_loadout then
    local loadout = PushMenuElement(Loadout:new())
    loadout.x = screen_start_x
    loadout.y = -30
    loadout.width = screen_width - 150
    loadout.height = screen_height / 2 - 10

    if not game.allow_chat then
      loadout.y = screen_start_y + 10
      loadout.height = screen_height - 50
    end
  end

  if game.allow_chat then
    local frame = PushMenuElement(Frame:new())
    frame.x = screen_start_x + 5
    frame.y = screen_start_y + 5
    frame.width = screen_width - 160
    frame.height = screen_height / 2 - 40

    if not game.allow_loadout then
      frame.height = screen_height - 50
    end

    local input = PushMenuElement(TextInput:new())
    input.x = frame.x
    input.y = frame.y
    input.width = frame.width
    input.height = chat_font_height
    input.prompt = "Enter Chat Here"

    local scrollbar = PushMenuElement(ScrollBar:new())
    scrollbar.x = frame.x + frame.width - 10
    scrollbar.y = frame.y + input.height
    scrollbar.width = 10
    scrollbar.height = frame.height - input.height

    local chatdisplay = PushMenuElement(ChatDisplay:new())
    chatdisplay.x = frame.x
    chatdisplay.y = frame.y + input.height
    chatdisplay.width = frame.width
    chatdisplay.height = frame.height - input.height
    chatdisplay.font = chat_font
    chatdisplay.scroll_proxy = scrollbar

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
    player_list.x = screen_end_x - 140
    player_list.y = screen_start_y + 90
    player_list.width = 130
    player_list.height = screen_height - 90 - font_height
  end

  if game.allow_mapsettings then
    local map_settings = PushMenuElement(MapInfo:new())
    map_settings.x = screen_end_x - 270
    map_settings.y = screen_end_y - 40
    map_settings.width = 120
    map_settings.height = 40
    map_settings.header_padding = 2
  end

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
  quitpopup.text = "Quit Out Of The Game?"
  
  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  quit.fade = false
  quit.Pressed = function()
    quitpopup:FadeIn()
  end

  quitpopup.OkayPressed = function()
    fader:FadeToSolidThen(function() game:Quit() end)
  end
end
