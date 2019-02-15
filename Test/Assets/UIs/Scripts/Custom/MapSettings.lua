
MapSettings = HeaderContainer:construct()
MapSettings.text = "Map Settings"
MapSettings.alpha = 1
MapSettings.parent_alpha = 1

MapSettings.allow_send = false

default_map_image = loader:LoadTexture("./Images/UI/DefaultMapImage.png")

map_options = {}
num_map_options = 0

function ResetMapOptions()
  map_options = {}
  num_map_options = 0 
end

function PushMapOption(map_name)
  map_options[num_map_options] = map_name
  num_map_options = num_map_options + 1
end

function MapSettings:setup(o)
  HeaderContainer:setup(o)
 
  o.map_list = ListBox:new(o)
  o.map_list.SelectedOptionChanged = function ()
    game:LoadMap(o.map_list.selected_index)
    o:UpdateSettings()
  end

  if in_editor then
    o.map_list:PushOption("Map 1")
    o.map_list:PushOption("Map 2")
    o.map_list:PushOption("Map 3")
  else
    for i = 0, num_map_options - 1 do
      o.map_list:PushOption(map_options[i])
    end
  end

  o.map_image = Texture:new(o)
  o.map_image:SetTexture(game.map_image or default_map_image)
  o.map_image.draw_frame = true

  if game.player_count_enabled then
    o.player_count_label = Label:new(o)
    o.player_count_label.text = "Player Count: "
    o.player_count_label.centered = false

    o.player_count = ScrollButton:new(o)
    o.player_count.SelectedOptionChanged = function ()
      o:SendOptions()
    end
  end

  if game.score_limit_enabled then
    o.score_limit_label = Label:new(o)
    o.score_limit_label.text = "Score Limit: "
    o.score_limit_label.centered = false

    o.score_limit = ScrollButton:new(o)
    o.score_limit.SelectedOptionChanged = function ()
      o:SendOptions()
    end
  end

  if game.time_limit_enabled then
    o.time_limit_label = Label:new(o)
    o.time_limit_label.text = "Time Limit: "
    o.time_limit_label.centered = false

    o.time_limit = ScrollButton:new(o)
    o.time_limit.SelectedOptionChanged = function ()
      o:SendOptions()
    end
  end

  o.map_description_label = Label:new(o)
  o.map_description_label.text = "Map Description: "
  o.map_description_label.centered = false

  o.map_description = Label:new(o)
  o.map_description.scale = 0.8
  o.map_description.centered = false
  o.map_description.wrap = true

  o:UpdateSettings()
  o.allow_send = true
end

function MapSettings:UpdateSettings()

  if game.player_count_enabled then
    self.player_count:ClearOptions()

    local option_value = game.player_limit_min
    local index = 0

    while option_value <= game.player_limit_max do
      self.player_count:PushOption(string.format("%i", option_value))

      if game.player_limit_default == option_value then
        self.player_count:SetSelectedOption(index)
      end

      option_value = option_value + game.player_limit_increment
      index = index + 1
    end
  end

  if game.score_limit_enabled then
    self.score_limit:ClearOptions()

    local option_value = game.score_limit_min
    local index = 0

    while option_value <= game.score_limit_max do
      self.score_limit:PushOption(string.format("%i", option_value))

      if game.score_limit_default == option_value then
        self.score_limit:SetSelectedOption(index)
      end

      option_value = option_value + game.score_limit_increment
      index = index + 1
    end
  end

  if game.time_limit_enabled then
    self.time_limit:ClearOptions()

    local option_value = game.time_limit_min
    local index = 0

    while option_value <= game.time_limit_max do
      self.time_limit:PushOption(string.format("%i", option_value))

      if game.time_limit_default == option_value then
        self.time_limit:SetSelectedOption(index)
      end

      option_value = option_value + game.time_limit_increment
      index = index + 1
    end
  end

  self.map_description.text = game.map_description
end

function MapSettings:InitMapOptions()
  if game.GetCurrentOptions ~= nil then
    local map_index, player_limit, score_limit, time_limit = game:GetCurrentOptions()
    
    self.map_list:SetSelectedOption(map_index)

    if game.player_count_enabled then
      self.player_count:SetSelectedValue(player_limit)
    end

    if game.score_limit_enabled then
      self.score_limit:SetSelectedValue(score_limit)
    end

    if game.time_limit_enabled then
      self.time_limit:SetSelectedValue(time_limit)
    end
  end
end

function MapSettings:SendOptions()
  if self.allow_send then
    local player_count = 0
    local score_limit = 0
    local time_limit = 0

    if game.player_count_enabled then
      player_count = self.player_count:GetSelectedOption()
    end

    if game.score_limit_enabled then
      score_limit = self.score_limit:GetSelectedOption()
    end

    if game.time_limit_enabled then
      time_limit = self.time_limit:GetSelectedOption()
    end

    game:SetMapOptions(player_count, score_limit, time_limit)
  end
end



function MapSettings:Update(dt)

  local alpha = self.alpha * self.parent_alpha
  
  self.map_list.x = 10
  self.map_list.y = 10
  self.map_list.width = 140
  self.map_list.height = 200
  self.map_list.parent_alpha = alpha

  self.map_image.x = 10
  self.map_image.y = 215
  self.map_image.width = 140
  self.map_image.height = 100
  self.map_image.parent_alpha = alpha

  self.map_description_label.x = 180
  self.map_description_label.y = 290
  self.map_description_label.width = 200
  self.map_description_label.height = 16
  self.map_description_label.parent_alpha = alpha

  self.map_description.x = 180
  self.map_description.y = 200
  self.map_description.width = 300
  self.map_description.height = 90
  self.map_description.parent_alpha = alpha

  if game.player_count_enabled then
    self.player_count_label.x = 180
    self.player_count_label.y = 180
    self.player_count_label.width = 100
    self.player_count_label.height = 10
    self.player_count_label.parent_alpha = alpha

    self.player_count.x = 180
    self.player_count.y = 160
    self.player_count.width = 100
    self.player_count.height = 16
    self.player_count.parent_alpha = alpha
  end

  if game.score_limit_enabled then
    self.score_limit_label.x = 180
    self.score_limit_label.y = 130
    self.score_limit_label.width = 100
    self.score_limit_label.height = 10
    self.score_limit_label.parent_alpha = alpha

    self.score_limit.x = 180
    self.score_limit.y = 110
    self.score_limit.width = 100
    self.score_limit.height = 16
    self.score_limit.parent_alpha = alpha
  end

  if game.time_limit_enabled then
    self.time_limit_label.x = 180
    self.time_limit_label.y = 80
    self.time_limit_label.width = 100
    self.time_limit_label.height = 10
    self.time_limit_label.parent_alpha = alpha

    self.time_limit.x = 180
    self.time_limit.y = 60
    self.time_limit.width = 100
    self.time_limit.height = 16
    self.time_limit.parent_alpha = alpha
  end

end
