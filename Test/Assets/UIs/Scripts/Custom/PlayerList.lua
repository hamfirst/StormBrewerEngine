
PlayerList = Elem:construct()
PlayerList.selectable = true
PlayerList.scroll_offset = 0
PlayerList.mouse_x = 0
PlayerList.mouse_y = 0
PlayerList.mouse_in = false
PlayerList.highlighted_player_id = 0
PlayerList.highlighted_menu_pos = 0
PlayerList.selected_player_id = 0
PlayerList.selected_menu_pos = 0

player_list_small_font = loader:LoadFont("./Fonts/basis33.ttf", 12)
player_list_big_font = loader:LoadFont("./Fonts/FFF.ttf", 9)
game_leader_icon = loader:LoadTexture("./Images/UI/GameLeader.png")
player_ready_icon = loader:LoadTexture("./Images/UI/PlayerReady.png")

PushPostLoadFunc(function()
  if in_editor then
    if game.GetPlayerId == nil then
      function game:GetPlayerId(team, player)
        return team * 100 + player + 1
      end
    end

    if game.GetTeamName == nil then
      function game:GetTeamName(team)
        if team == 0 then
          return "Red Team"
        elseif team == 1 then
          return "Blue Team"
        end

        return "Observers"
      end
    end

    if game.GetTeamColor == nil then
      function game:GetTeamColor(team)

        if team == 0 then
          return 0.9, 0.3, 0.33
        elseif team == 1 then
          return 0.33, 0.3, 0.9
        end

        return 0.4, 0.4, 0.4
      end
    end

    if game.GetPlayerName == nil then
      function game:GetPlayerName(player_id)
        return "Player" .. player_id
      end
    end

    if game.GetPlayerState == nil then
      function game:GetPlayerState(player_id)
        if player_id == 1 then return 1 end
        return 0
      end      
    end

    if game.GetPlayerReady == nil then
      function game:GetPlayerReady(player_id)
        if player_id % 3 == 1 then return 1 end
        return 0
      end      
    end

    if game.GetPlayerActions == nil then
      function game:GetPlayerActions(player_id)
        local actions = {}
        actions["Kick"] = "KickPlayer"
        actions["Switch To Red"] = "SwitchTo0"
        actions["Switch To Blue"] = "SwitchTo1"
        return actions
      end
    end
  end
end)


function PlayerList:setup(o)
  Elem:setup(o)
  o.scrollbar = PushMenuElement(ScrollBar:new())
  o.scrollbar.ValueChanged = function()
    o.scroll_offset = o.scrollbar.value
    o:RepositionMenu()
  end

  o.scroll_proxy = o.scrollbar
end

function PlayerList:RepositionMenu()
  local visitor = function(type, team, player, y, height)
    if type == 1 then

      local player_id = game:GetPlayerId(team, player)

      if self.selected_player_id == player_id then
        self.selected_menu_pos = y + height / 2

        if self.selected_menu_pos < 0 then
          self.selected_menu_pos = 0
        end

        if self.selected_menu_pos > self.height then
          self.selected_menu_pos = self.height
        end

        if self.context_show_id ~= nil and self.context_show_id == context_menu.show_id then
          context_menu.y = self.y + self.selected_menu_pos - context_menu.content_height / 2
          context_menu.clickable.Y = context_menu.y
        end
      end
    end
  end

  self:VisitElements(visitor)
end

function PlayerList:Update()
  self.scrollbar:SetScrollArea(self.height, self.content_height)
  self.scrollbar.x = self.x + self.width + 1
  self.scrollbar.y = self.y
  self.scrollbar.width = 15
  self.scrollbar.height = self.height
end

function PlayerList:VisitElements(visitor)
  local team_count = game:GetTeamCount()
 
  local y = self.height + self.scroll_offset
  local iniital_y = y

  local small_font_height = ui:GetLineHeight(player_list_small_font)
  local big_font_height = ui:GetLineHeight(player_list_big_font)

  for team = 0, team_count - 1 do

    local player_count = game:GetPlayerCount(team)

    y = y - small_font_height
    visitor(0, team, 0, y, small_font_height)
    y = y - 2
    
    for player = 0, player_count - 1 do

      local height = (big_font_height + 8)
      y = y - height
      visitor(1, team, player, y, height)
      y = y - 2

    end

    y = y - 5
  end

  if game.allow_observers then
    local player_count = game:GetPlayerCount(-1)

    y = y - small_font_height
    visitor(0, -1, 0, y, small_font_height)
    y = y - 2
    
    for player = 0, player_count - 1 do

      local height = (big_font_height + 8)
      y = y - height
      visitor(1, -1, player, y, height)
      y = y - 2

    end
  end

  y = y - 5

  self.content_height = iniital_y - y
end

function PlayerList:Draw()

  local small_font_height = ui:GetLineHeight(player_list_small_font)
  local big_font_height = ui:GetLineHeight(player_list_big_font)

  local prev_highlighted_player_id = self.highlighted_player_id
  self.highlighted_player_id = 0
  self.highlighted_menu_pos = 0

  local found_selected_player = false

  local visitor = function(type, team, player, y, height)
    if type == 0 then

      local player_count = game:GetPlayerCount(team)
      local player_max_count = game:GetPlayerMaxCount(team)
      local team_name = game:GetTeamName(team)

      local team_text = ""
      if team == -1 then
        team_text = string.format("%s (%d)", team_name, player_count) 
      else
        team_text = string.format("%s (%d/%d)", team_name, player_count, player_max_count) 
      end

      ui:DrawText(player_list_small_font, team_text, 3, y, 0, 0, 0, 1, kNormal)

    elseif type == 1 then

      local r, g, b = game:GetTeamColor(team)
      local player_id = game:GetPlayerId(team, player)
      local player_name = game:GetPlayerName(player_id)

      if player_id == self.selected_player_id then
        found_selected_player = true
      end

      if self.selectable and self.mouse_in and self.mouse_y >= y and self.mouse_y <= y + height and self.selected_player_id ~= player_id then
        self.highlighted_player_id = player_id
        self.highlighted_menu_pos = y + height / 2

        ui:DrawFilledRectangle(0, y, self.width - 2, height, r, g, b, 1)
        ui:FlushGeometry()

        ui:DrawText(player_list_big_font, player_name, 32, y + height / 2 - big_font_height / 2, 1, 1, 1, 1, kNormal)

        if game:GetPlayerState(player_id) == 1 then
          ui:DrawTextureTint(game_leader_icon, 16, y + height / 2 - 8, 1, 1, 1, 1)
        end

        if game:GetPlayerReady(player_id) == 1 then
          ui:DrawTextureTint(player_ready_icon, 1, y + height / 2 - 8, 1, 1, 1, 1)
        end
      else

        if self.selected_player_id == player_id then
          ui:DrawFilledRectangle(0, y, self.width - 2, height, r, g, b, 0.4)
        else
          ui:DrawFilledRectangle(0, y, self.width - 2, height, r, g, b, 0.1)
        end

        ui:DrawRectangle(0, y, self.width - 2, height, r, g, b, 1)
        ui:FlushGeometry()

        ui:DrawText(player_list_big_font, player_name, 32, y + height / 2 - big_font_height / 2, r, g, b, 1, kNormal)

        if game:GetPlayerState(player_id) == 1 then
          ui:DrawTextureTint(game_leader_icon, 16, y + height / 2 - 8, 1, 1, 1, 1)
        end

        if game:GetPlayerReady(player_id) == 1 then
          ui:DrawTextureTint(player_ready_icon, 1, y + height / 2 - 8, r, g, b, 1)
        end
      end
    end
  end


  self:VisitElements(visitor)

  if self.selected_player_id ~= 0 and self.found_selected_player == false then
    self:DeselectPlayer()
  end

  if self.highlighted_player_id ~= 0 and self.highlighted_player_id ~= prev_highlighted_player_id then
    ui:PlayAudio(hover_audio)
  end
end

function PlayerList:StateChanged(old_state, new_state)
  if new_state == kPressed then
    if self.selected_player_id ~= 0 and self.selected_player_id == self.highlighted_player_id then
      self:DeselectPlayer()
    else
      self:SelectPlayer()
    end
  end
end

function PlayerList:SelectPlayer()
  if self.highlighted_player_id ~= 0 then
    self.selected_player_id = self.highlighted_player_id
    self.selected_menu_pos = self.highlighted_menu_pos    

    ui:PlayAudio(click_audio)

    local player_id = self.selected_player_id
    local actions = game:GetPlayerActions(player_id)

    context_menu:Reset()

    local sorted_actions = {}
    local num = 0
    for k, v in pairs(actions) do
      sorted_actions[num] = { text=k, func=v }
      num = num + 1
    end

    table.sort(sorted_actions, function (left, right) return left.text < right.text end)

    for i = 0, num - 1 do
      local v = sorted_actions[i]
      local func = v.func
      local text = v.text

      context_menu:PushMenuAction(text, function() 
        if game[func] ~= nil then
          game[func](game, player_id) 
        else
          print("Context action not found " .. text)
        end
      end)
    end

    self.context_show_id = context_menu:Show(self.x - context_menu.content_width - 5, self.y + self.highlighted_menu_pos - context_menu.content_height / 2)

  end
end

function PlayerList:DeselectPlayer()
  self.selected_player_id = 0

  if self.context_show_id ~= nil then
    context_menu:Reset(self.context_show_id)
  end
end

function PlayerList:MouseEntered(x, y)
  self.mouse_in = true
  self.mouse_x = x
  self.mouse_y = y
end

function PlayerList:MouseLeft()
  self.mouse_in = false
end

function PlayerList:MouseMoved(x, y)
  self.mouse_x = x
  self.mouse_y = y
end

