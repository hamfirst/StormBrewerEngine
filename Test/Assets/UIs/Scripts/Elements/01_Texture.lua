
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

  local width, height = ui:GetTextureSize(self.texture_id)

  if width > 0 and height > 0 then
    local scale_x = self.width / width
    local scale_y = self.height / height
    ui:RenderTextureScaleTint(self.texture_id, 0, 0, scale_x, scale_y, 1, 1, 1, self.alpha)
  end

end

