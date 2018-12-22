
fullscreen_texture = loader:LoadTexture("./Images/UI/FullScreen.png")

FullScreenControl = Elem:construct()

function FullScreenControl:setup(o)
  Elem:setup(o)
  o.width, o.height = ui:GetTextureSize(fullscreen_texture)
end

function FullScreenControl:Render()

  local texture_id = fullscreen_texture

  self.width, self.height = ui:GetTextureSize(texture_id)
  ui:RenderTexture(texture_id, 0, 0)
end

function FullScreenControl:Clicked()
  if ui:GetFullScreenVolume() > 0 then
    texture_id = ui:SetFullScreenVolume(0)
  else
    texture_id = ui:SetFullScreenVolume(0.85)
  end
end
