
fullscreen_texture = loader:LoadTexture("./Images/UI/FullScreen.png")

FullScreenControl = Elem:construct()
FullScreenControl.alpha = 1

function FullScreenControl:setup(o)
  Elem:setup(o)
  o.width, o.height = ui:GetTextureSize(fullscreen_texture)
end

function FullScreenControl:Draw()

  local texture_id = fullscreen_texture

  self.width, self.height = ui:GetTextureSize(texture_id)
  ui:DrawTextureTint(texture_id, 0, 0, 1, 1, 1, self.alpha * 0.4)
end

function FullScreenControl:Clicked()
  ui:ToggleFullscreen()
end
