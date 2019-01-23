
Frame = Elem:construct()
Frame.alpha = 1
Frame.r = default_frame_r
Frame.g = default_frame_g
Frame.b = default_frame_b

function Frame:SetFrame(texture_id)
  self.texture_id = texture_id
  self.width, self.height = ui:GetFrameSize(texture_id)
end

function Frame:Draw()

  if self.alpha == 0 then
    return
  end

  ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, self.r, self.g, self.b, self.alpha)
  ui:FlushGeometry()
end

