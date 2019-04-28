
music_on_texture = loader:LoadTexture("./Images/UI/MusicOn.png")
music_off_texture = loader:LoadTexture("./Images/UI/MusicOff.png")

MusicControl = Elem:construct()
MusicControl.alpha = 1

function MusicControl:setup(o)
  Elem:setup(o)
  o.width, o.height = ui:GetTextureSize(music_on_texture)
end

function MusicControl:Draw()

  local texture_id = 0
  if ui:GetMusicVolume() > 0 then
    texture_id = music_on_texture
  else
    texture_id = music_off_texture
  end

  self.width, self.height = ui:GetTextureSize(texture_id)
  ui:DrawTextureTint(texture_id, 0, 0, 1, 1, 1, self.alpha * 0.4)
end

function MusicControl:Clicked()
  if ui:GetMusicVolume() > 0 then
    texture_id = ui:SetMusicVolume(0)
  else
    texture_id = ui:SetMusicVolume(0.85)
  end
end
