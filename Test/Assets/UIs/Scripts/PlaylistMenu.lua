
rank_sprites = loader:LoadSprite("./Sprites/RankIcons.sprite")

function InitCasualPlaylistMenu()
  InitPlaylistMenu(game.casual_playlist, "Casual")
end

function InitCompetitivePlaylistMenu()
  InitPlaylistMenu(game.competitive_playlist, "Ranked", game.competitive_ranks)
end

function InitPlaylistMenu(playlist_list, playlist_name, ranks)

  if playlist_list == nil then
    playlist_list = {}
    playlist_list.m_Elements = {}
    playlist_list.m_Elements[1] = {m_Name="1 v 1"}
    playlist_list.m_Elements[2] = {m_Name="2 v 2"}
  end

  local playlist_count = #playlist_list.m_Elements
  local playlist_mask = 0

  if playlist_count <= 1 then
    game:Search(1)
    return
  end

  local button_width = 100
  local button_pad = 5
  local button_height = 60
  local total_width = playlist_count * (button_width + button_pad) - button_pad
  local button_start = -total_width / 2

  local header = PushMenuElement(HeaderContainer:new())
  header.x = -total_width / 2 - 40
  header.y = button_height / -2 - 50
  header.height = button_height + 100
  header.width = total_width + 80
  header.text = playlist_name

  local search = PushMenuElement(Button:new())
  search.x = total_width / 2 - 100 + 20
  search.y = button_height / -2 - 40
  search.width = 100
  search.height = 20
  search.text = "Search"

  local cancel = PushMenuElement(Button:new())
  cancel.x = screen_end_x - 80
  cancel.y = screen_start_y + 10
  cancel.width = 70
  cancel.height = font_height
  cancel.text = "Cancel"
  cancel.back = true
  
  local instructions = PushMenuElement(Label:new())
  instructions.x = screen_start_x
  instructions.y = screen_start_y + 50
  instructions.width = screen_width
  instructions.height = 60
  instructions.text = "Please Select At Least One Play List"

  local buttons = {}
  local next_button_id = 0

  function CheckIfAnyPlaylistsEnabled()
    local enabled = playlist_mask ~= 0

    search.pressable = enabled
    if(enabled) then
      AddLerp(instructions, "alpha", 0, 0.2, nil, EaseInCubic)
    else
      AddLerp(instructions, "alpha", 1, 0.2, nil, EaseInCubic)
    end
  end

  for k, v in pairs(playlist_list.m_Elements) do
    local button = PushMenuElement(Button:new())
    button.toggleable = true

    if ranks == nil then
      button.font = large_header_font
    else
      button.font = small_header_font
    end

    button.scale = 1

    button.x = button_start + ((k - 1) * (button_width + button_pad))
    button.y = button_height / -2
    button.width = button_width
    button.height = button_height
    button.text = v.m_Name

    buttons[next_button_id] = button
    next_button_id = next_button_id + 1

    local playlist_maks_val = 1 << (k - 1)

    function button:ToggleOn()
      playlist_mask = playlist_mask | playlist_maks_val
      CheckIfAnyPlaylistsEnabled()
    end

    function button:ToggleOff()
      playlist_mask = playlist_mask & (~playlist_maks_val)
      CheckIfAnyPlaylistsEnabled()
    end

    if ranks ~= nil then
      local rank = ranks[v.m_Name]
      if rank == nil then
        rank = -1
      end


      local rank_anim = "Unranked"
      local rank_desc = "Unranked"
      local rank_frame = 0

      if rank >= 0 then
        if(rank < 4) then
          rank_anim = "Red"
          rank_frame = rank
          rank_desc = "Bronze "
        elseif rank < 8 then
          rank_anim = "White"
          rank_frame = rank - 4
          rank_desc = "Silver "
        elseif rank < 12 then
          rank_anim = "Yellow"
          rank_frame = rank - 8
          rank_desc = "Gold "
        elseif rank < 16 then
          rank_anim = "Blue"
          rank_frame = rank - 16
          rank_desc = "Master "
        else
          rank_anim = "Blue"
          rank_frame = 3
          rank_desc = "Master "
        end

        if rank_frame == 0 then
          rank_desc = rank_desc .. "I"
        elseif rank_frame == 1 then
          rank_desc = rank_desc .. "II"
        elseif rank_frame == 2 then
          rank_desc = rank_desc .. "III"
        elseif rank_frame == 3 then
          rank_desc = rank_desc .. "IV"
        end
      end

      local anim_index = ui:GetAnimationIndex(rank_sprites, rank_anim)
      local width, height = ui:GetSpriteSize(rank_sprites, rank_anim, rank_frame)

      button.text_offset_y = -20

      local sprite = StillSprite:new(button)
      sprite:SetWantsInput(false)
      sprite:SetSprite(rank_sprites, anim_index, rank_frame)
      sprite:SetClip(false)
      sprite.x = button_width / 2 - width / 2
      sprite.y = button_height / 2 - height / 2 + 25

      local label = Label:new(button)
      label:SetWantsInput(false)
      label.x = 0
      label.y = button_height / 2 - 5
      label.width = button_width
      label.height = 20
      label.text = rank_desc
    end
  end

  CheckIfAnyPlaylistsEnabled()
  CreateDefualtControls()

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  FadeFromButtonPress(fader, search, function() game:Search(playlist_mask) end)
  FadeFromButtonPress(fader, cancel, function() game:Back() end)
end


