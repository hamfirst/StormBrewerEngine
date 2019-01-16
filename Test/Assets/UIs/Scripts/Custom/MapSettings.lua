
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
end
