
MapSettings = HeaderContainer:construct()
MapSettings.text = "Map Settings"

default_map_image = loader:LoadTexture("./Images/UI/DefaultMapImage.png")

function MapSettings:setup(o)
  HeaderContainer:setup(o)
 
  o.map_list = ListBox:new(o)
  o.map_image = Texture:new(o)
  o.map_image.texture_id = default_map_image
  o.map_image.draw_frame = true

  if in_editor then
    o.map_list:PushOption("Map 1")
    o.map_list:PushOption("Map 2")
    o.map_list:PushOption("Map 3")
  end

  o.player_count_label = Label:new(o)
  o.player_count_label.text = "Player Count: "
  o.player_count_label.centered = false

  o.player_count = ScrollButton:new(o)
  if in_editor then
    o.player_count:PushOption(2)
    o.player_count:PushOption(4)
    o.player_count:PushOption(6)
  end

  o.score_limit_label = Label:new(o)
  o.score_limit_label.text = "Score Limit: "
  o.score_limit_label.centered = false

  o.score_limit = ScrollButton:new(o)
  if in_editor then
    o.score_limit:PushOption(2)
    o.score_limit:PushOption(4)
    o.score_limit:PushOption(6)
  end

  o.time_limit_label = Label:new(o)
  o.time_limit_label.text = "Time Limit: "
  o.time_limit_label.centered = false

  o.time_limit = ScrollButton:new(o)
  if in_editor then
    o.time_limit:PushOption(2)
    o.time_limit:PushOption(4)
    o.time_limit:PushOption(6)
  end

  o.map_description_label = Label:new(o)
  o.map_description_label.text = "Map Description: "
  o.map_description_label.centered = false

  o.map_description = Label:new(o)
  o.map_description.scale = 0.8
  o.map_description.text = "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?"
  o.map_description.centered = false
  o.map_description.wrap = true
  
end

function MapSettings:Update(dt)
  
  self.map_list.x = 10
  self.map_list.y = 10
  self.map_list.width = 140
  self.map_list.height = 200

  self.map_image.x = 10
  self.map_image.y = 215
  self.map_image.width = 140
  self.map_image.height = 100

  self.map_description_label.x = 180
  self.map_description_label.y = 290
  self.map_description_label.width = 200
  self.map_description_label.height = 16

  self.map_description.x = 180
  self.map_description.y = 200
  self.map_description.width = 300
  self.map_description.height = 90

  self.player_count_label.x = 180
  self.player_count_label.y = 180
  self.player_count_label.width = 100
  self.player_count_label.height = 10

  self.player_count.x = 180
  self.player_count.y = 160
  self.player_count.width = 100
  self.player_count.height = 16

  self.score_limit_label.x = 180
  self.score_limit_label.y = 130
  self.score_limit_label.width = 100
  self.score_limit_label.height = 10

  self.score_limit.x = 180
  self.score_limit.y = 110
  self.score_limit.width = 100
  self.score_limit.height = 16

  self.time_limit_label.x = 180
  self.time_limit_label.y = 80
  self.time_limit_label.width = 100
  self.time_limit_label.height = 10

  self.time_limit.x = 180
  self.time_limit.y = 60
  self.time_limit.width = 100
  self.time_limit.height = 16
end
