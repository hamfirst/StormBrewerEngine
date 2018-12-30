
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

player_list_small_font = loader:LoadFont("./Fonts/basis33.ttf", 10)
player_list_big_font = loader:LoadFont("./Fonts/FFF.ttf", 12)

function PlayerList:VisitElements(visitor)
  local team_count = game:GetTeamCount()
  local y = self.height + self.scroll_offset

  local small_font_height = ui:GetLineHeight(player_list_small_font)
  local big_font_height = ui:GetLineHeight(player_list_big_font)

  for team = 0, team_count - 1 do

    local player_count = game:GetPlayerCount(team)

    y = y - small_font_height
    visitor(0, team, 0, y, small_font_height)
    y = y - 2
    
    for player = 0, player_count - 1 do

      y = y - 30
      visitor(1, team, player, y, 30)
      y = y - 2

    end

    y = y - 5
  end

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

      local r, g, b = game:GetTeamColor(team)

      local team_text = string.format("%s Team (%d/%d)", team_name, player_count, player_max_count) 
      ui:DrawText(player_list_small_font, team_text, 3, y, 0, 0, 0, 1, kNormal)

    elseif type == 1 then

      local player_name = game:GetPlayerName(team, player)
      local player_id = self:GetPlayerId(team, player)

      if player_id == self.selected_player_id then
        found_selected_player = true
      end

      if self.selectable and self.mouse_in and self.mouse_y >= y and self.mouse_y <= y + height and self.selected_player_id ~= player_id then
        self.highlighted_player_id = player_id
        self.highlighted_menu_pos = y + height / 2

        ui:DrawFilledRectangle(0, y, self.width - 2, 30, r, g, b, 1)
        ui:FlushGeometry()

        ui:DrawText(player_list_big_font, player_name, 10, y + 30 - big_font_height, 1, 1, 1, 1, kNormal)
      else

        if self.selected_player_id == player_id then
          ui:DrawFilledRectangle(0, y, self.width - 2, 30, r, g, b, 0.4)
        else
          ui:DrawFilledRectangle(0, y, self.width - 2, 30, r, g, b, 0.1)
        end

        ui:DrawRectangle(0, y, self.width - 2, 30, r, g, b, 1)
        ui:FlushGeometry()

        ui:DrawText(player_list_big_font, player_name, 10, y + 30 - big_font_height, r, g, b, 1, kNormal)
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
    self:SelectPlayer()
  end
end

function PlayerList:SelectPlayer()
  if self.highlighted_player_id ~= 0 then
    self.selected_player_id = self.highlighted_player_id
    self.selected_menu_pos = self.highlighted_menu_pos    

    ui:PlayAudio(click_audio)
  end
end

function PlayerList:DeselectPlayer()
  self.selected_player_id = 0
end

function PlayerList:GetPlayerId(team, player)
  if in_editor then
    return team * 100 + player + 1
  else
    return game:GetPlayerId(team, player)
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

