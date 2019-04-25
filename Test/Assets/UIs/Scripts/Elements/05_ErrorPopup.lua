
ErrorPopup = Popup:construct()
ErrorPopup.text = "Error!"
ErrorPopup.text_r = default_text_r
ErrorPopup.text_g = default_text_g
ErrorPopup.text_b = default_text_b

function ErrorPopup:CreateChildren()

  self.okay = self:PushChild(Button:new())
  self.okay.text = "Okay"
  
  self.okay.Pressed = function () 
    self:FadeOut() 
    self:OkayPressed() 
  end

  local half_width = self.width / 2

  self.okay.x = half_width * 0.7
  self.okay.y = 20
  self.okay.width = half_width * 0.6
  self.okay.height = 20
end

function ErrorPopup:Draw()
  Popup.Draw(self)

  ui:DrawCenteredText(font, self.text, self.width / 2, self.height / 2 + 20, self.text_r, self.text_g, self.text_b, self.alpha, kNormal)
end

function ErrorPopup:OkayPressed()

end

function ShowErrorPopup(err_msg)
  local popup = PushMenuElement(ErrorPopup:new())
  popup.x = -200
  popup.y = -80
  popup.width = 400
  popup.height = 190
  popup.text = err_msg

  popup:FadeIn()
end
