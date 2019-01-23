
ConfirmPopup = Popup:construct()
ConfirmPopup.text = "Confirm?"
ConfirmPopup.text_r = default_text_r
ConfirmPopup.text_g = default_text_g
ConfirmPopup.text_b = default_text_b

function ConfirmPopup:CreateChildren()

  self.okay = self:PushChild(Button:new())
  self.okay.text = "Okay"
  self.cancel = self:PushChild(Button:new())
  self.cancel.text = "Cancel"
  self.cancel.back = true
  
  self.okay.Pressed = function () 
    self:FadeOut() 
    self:OkayPressed() 
  end

  self.cancel.Pressed = function () 
    self:FadeOut() 
    self:CancelPressed() 
  end

  local half_width = self.width / 2

  self.okay.x = half_width * 0.2
  self.okay.y = 20
  self.okay.width = half_width * 0.6
  self.okay.height = 20

  self.cancel.x = half_width * 1.2
  self.cancel.y = 20
  self.cancel.width = half_width * 0.6
  self.cancel.height = 20
end

function ConfirmPopup:Draw()
  Popup.Draw(self)

  ui:DrawCenteredText(font, self.text, self.width / 2, self.height - 50, self.text_r, self.text_g, self.text_b, self.alpha, kNormal)
end

function ConfirmPopup:OkayPressed()

end

function ConfirmPopup:CancelPressed()

end
