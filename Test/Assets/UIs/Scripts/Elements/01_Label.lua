
Label = Elem:construct()
Label.text = ""
Label.r = default_text_r
Label.g = default_text_g
Label.b = default_text_b
Label.alpha = 1.0
Label.parent_alpha = 1.0
Label.scale = 1.0
Label.centered = true
Label.wrap = false
Label.font = font

function Label:Draw()

  local text = self.text
  local height = 0
  local alpha = self.alpha * self.parent_alpha

  if self.wrap then
    text, height = ui:WrapTextScaled(self.font, text, self.width, self.scale)
  end

  if self.centered then
    ui:DrawCenteredTextScaled(self.font, text, self.width / 2, self.height / 2 + 1, 
                              self.r, self.g, self.b, alpha, kNormal, self.scale);
  else
    local width, height = ui:MeasureTextScaled(self.font, text, self.scale)

    ui:DrawTextScaled(self.font, text, 0, self.height - height + 1, 
                              self.r, self.g, self.b, alpha, kNormal, self.scale);    
  end

end

