
Texture = Elem:construct()
Texture.alpha = 1
Texture.parent_alpha = 1
Texture.draw_frame = false

function Texture:SetTexture(texture_id)
  self.texture_id = texture_id
  self.width, self.height = ui:GetTextureSize(texture_id)
end

function Texture:Draw()

  local alpha = self.alpha * self.parent_alpha
  if alpha == 0 then
    return
  end

  local width, height = ui:GetTextureSize(self.texture_id)

  if width > 0 and height > 0 then
    local scale_x = self.width / width
    local scale_y = self.height / height
    ui:DrawTextureScaleTint(self.texture_id, 0, 0, scale_x, scale_y, 1, 1, 1, alpha)
  end

  if self.draw_frame then
    ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, 0, 0, 0, alpha)
    ui:FlushGeometry()
  end

end

