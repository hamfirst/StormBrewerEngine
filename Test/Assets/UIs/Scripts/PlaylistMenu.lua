
rank_sprites = loader:LoadSprite("./Sprites/RankIcons.sprite")

function InitCasualPlaylistMenu()
  InitPlaylistMenu(game.casual_playlist, "Casual")
end

function InitCompetitivePlaylistMenu()
  InitPlaylistMenu(game.competitive_playlist, "Competitive", {})
end

function InitPlaylistMenu(playlist_list, playlist_name, ranks)

  if playlist_list == nil then
    playlist_list = {}
    playlist_list.m_Elements = {}
    playlist_list.m_Elements[1] = {m_Name="1 v 1"}
    playlist_list.m_Elements[2] = {m_Name="2 v 2"}
  end

  local playlist_count = #playlist_list.m_Elements

  local button_width = 200
  local button_pad = 20
  local button_height = 100
  local total_width = playlist_count * (button_width + button_pad) - button_pad
  local button_start = -total_width / 2

  local header = PushMenuElement(HeaderContainer:new())
  header.x = -total_width / 2 - 100
  header.y = screen_start_y + 100
  header.height = screen_height - 200
  header.width = total_width + 200
  header.text = playlist_name

  local cancel = PushMenuElement(Button:new())
  cancel.x = screen_end_x - 100
  cancel.y = screen_start_y + 30
  cancel.width = 70
  cancel.height = 20
  cancel.text = "Cancel"
  cancel.back = true

  for k, v in pairs(playlist_list.m_Elements) do
    local button = PushMenuElement(Button:new())
    button.toggleable = true
    button.font = large_header_font
    button.scale = 1

    button.x = button_start + ((k - 1) * (button_width + button_pad))
    button.y = button_height / -2
    button.width = button_width
    button.height = button_height
    button.text = v.m_Name

    if ranks ~= nil then
      local rank = ranks[v.m_Name]
      if rank == nil then
        rank = -1
      end


      local rank_anim = "Unranked"
      local rank_frame = 0

      if rank >= 0 then
        if(rank < 4) then
          rank_anim = "Red"
          rank_frame = rank
        elseif rank < 8 then
          rank_anim = "White"
          rank_frame = rank - 4
        elseif rank < 12 then
          rank_anim = "Yellow"
          rank_frame = rank - 8
        elseif rank < 16 then
          rank_anim = "Blue"
          rank_frame = rank - 16
        else
          rank_anim = "Blue"
          rank_frame = 3
        end
      end

      local anim_index = ui:GetAnimationIndex(rank_sprites, rank_anim)
      local width, height = ui:GetSpriteSize(rank_sprites, rank_anim, rank_frame)

      button.text_offset_y = -height

      local sprite = StillSprite:new(button)
      sprite:SetSprite(rank_sprites, anim_index, rank_frame)
      sprite:SetClip(false)
      sprite.x = button_width / 2 - width / 2
      sprite.y = button_height / 2 - height / 2
    end
  end

  local search = PushMenuElement(Button:new())
  search.x = total_width / 2 - 100
  search.y = button_height / -2 - 40
  search.width = 100
  search.height = 20
  search.text = "Search"

  CreateDefualtControls();

  fader = PushMenuElement(Fader:new())
  fader:FadeToClear()

  FadeFromButtonPress(fader, cancel, function() CleanupMenu() InitMainMenu() end)
end


