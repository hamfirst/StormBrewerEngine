
fullscreen_texture = loader:LoadTexture("./Images/UI/FullScreen.png")

FullScreenControl = Elem:construct()

function FullScreenControl:setup(o)
  Elem:setup(o)
  o.width, o.height = ui:GetTextureSize(fullscreen_texture)
end

function FullScreenControl:Draw()

  local texture_id = fullscreen_texture

  self.width, self.height = ui:GetTextureSize(texture_id)
  ui:DrawTexture(texture_id, 0, 0)
end

function FullScreenControl:Clicked()
  ui:ToggleFullscreen()
end
