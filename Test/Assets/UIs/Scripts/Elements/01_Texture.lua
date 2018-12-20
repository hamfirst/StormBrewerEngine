
Texture = Elem:construct()
Texture.alpha = 1

function Texture:SetTexture(texture_id)
  self.texture_id = texture_id
  self.width, self.height = ui:GetTextureSize(texture_id)
end

function Texture:Render()

  if self.alpha == 0 then
    return
  end

  ui:RenderTextureTint(self.texture_id, 0, 0, 1, 1, 1, self.alpha)

end

