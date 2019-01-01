
Label = Elem:construct()
Label.text = ""
Label.r = 0
Label.g = 0
Label.b = 0
Label.alpha = 1.0
Label.scale = 1.0
Label.centered = true
Label.font = font

function Label:Draw()

  if self.centered then
    ui:DrawCenteredTextScaled(self.font, self.text, self.width / 2, self.height / 2 + 1, 
                              self.r, self.g, self.b, self.alpha, kNormal, self.scale);
  else
    local width, height = ui:MeasureTextScaled(self.font, self.text, self.scale)

    ui:DrawTextScaled(self.font, self.text, 0, self.height - height + 1, 
                              self.r, self.g, self.b, self.alpha, kNormal, self.scale);    
  end

end

