
QuickMenu = Elem:construct()
QuickMenu.alpha = 1
QuickMenu.fading = false

function QuickMenu:setup(o)
  Elem:setup(o)

  o.elems = {}
  o.next_elem_id = 0

  o.buttons = {}
  o.next_button_id = 0

  o.x = screen_start_x + 50
  o.y = screen_start_y + 40
  o.width = 140
  o.height = 140

  o:SetEnabled(false)
  o:SetClip(false)
end

function QuickMenu:Update()
  for k, v in pairs(self.buttons) do
    v.parent_alpha = self.alpha
  end
end

function QuickMenu:Destoyed()
  self:Reset()
end

function QuickMenu:Reset(show_id)

  for k, v in pairs(self.buttons) do
    v:destroy()
  end

  self.buttons = {}
  self.next_button_id = 0
  self.bottom_button = nil

  self.alpha = 1
  self.fading = false

end

function QuickMenu:PushMenuAction(text, func)

  local elem = { text = text, func = func }

  self.elems[self.next_elem_id] = elem
  self.next_elem_id = self.next_elem_id + 1
end

function QuickMenu:PushSubMenu(text, menu)

  local elem = { text = text, menu = menu }

  self.elems[self.next_elem_id] = elem
  self.next_elem_id = self.next_elem_id + 1

  menu:AddBackButton(self)
end

function QuickMenu:SetBottomButton(text, func, back)
  local elem = { text = text, func = func, back = back }
  self.bottom_elem = elem
end

function QuickMenu:AddBackButton(prev_menu)

  self:SetBottomButton("Back", function() 
    self:TransitionOut(-1)
    prev_menu:TransitionBack()
  end, true)

end

function QuickMenu:CreateButton(elem)
  local button = Button:new()
  button:SetParent(self)
  button:SetClip(false)
  button.text = elem.text

  if elem.func ~= nil then

    if elem.back ~= nil then
      button.fade = false
      button.back = true

      button.Pressed = function()
        elem.func()
      end      
    else
      button.Pressed = function()
        fader:FadeToSolidThen(function() elem.func() end)
        for k, v in pairs(self.buttons) do
          v.pressable = false
          if v ~= button then
            AddLerp(v, "alpha", 0, 0.2, nil, EaseInCubic)    
          end
        end
      end
    end
  end


  if elem.menu ~= nil then
    button.fade = false
    button.Hovered = function()
      elem.menu:ShowPreview()
    end

    button.Unhovered = function()
      elem.menu:Reset()
    end

    button.Pressed = function()
      self:TransitionOut()
      elem.menu:TransitionIn()
    end
  end

  self.buttons[self.next_button_id] = button
  self.next_button_id = self.next_button_id + 1
  return button
end

function QuickMenu:CreateButtons()
  local y = self.height - 20

  for i=0, self.next_elem_id - 1 do
    local button = self:CreateButton(self.elems[i])

    button.x = 0
    button.y = y
    button.height = 20
    button.width = self.width - 1

    y = y - 25
  end

  if self.bottom_elem ~= nil then
    local button = self:CreateButton(self.bottom_elem)

    button.x = 0
    button.y = 0
    button.width = self.width - 1
    button.height = 20

    self.bottom_button = button
  end

end

function QuickMenu:Show()
  self:Reset()
  self:SetEnabled(true)

  self:CreateButtons()
end

function QuickMenu:ShowPreview()
  self:Reset()
  self:SetEnabled(true)
  self:CreateButtons()

  for k, v in pairs(self.buttons) do
    v.x = 150
    v.pressable = false
  end

  self.alpha = 0
  self.bottom_button.alpha = 0

  AddLerp(self, "alpha", 0.5, 0.1, nil, EaseInCubic)
end

function QuickMenu:TransitionIn()

  for k, v in pairs(self.buttons) do
    AddLerp(v, "alpha", 1, 0.15, nil, EaseInCubic)
    AddLerp(v, "x", 0, 0.15, nil, EaseInCubic)
  end

  AddLerp(self, "alpha", 1, 0.3, function() 
    for k, v in pairs(self.buttons) do
      v.pressable = true
    end
  end, EaseInCubic)
end

function QuickMenu:TransitionOut(dir)
  for k, v in pairs(self.buttons) do
    v.pressable = false
  end

  local target_x = -70
  if dir == -1 then
    target_x = 70
  end

  for k, v in pairs(self.buttons) do
    AddLerp(v, "alpha", 0, 0.15, nil, EaseInCubic)    
    AddLerp(v, "x", target_x, 0.15, nil, EaseInCubic)
  end

  AddLerp(self, "alpha", 0, 0.3, function() 
    self:Reset()
    self:SetEnabled(false)
  end, EaseInCubic)
end

function QuickMenu:TransitionBack()
  self:Reset()
  self:SetEnabled(true)
  self:CreateButtons()

  for k, v in pairs(self.buttons) do
    v.pressable = false
  end

  for k, v in pairs(self.buttons) do
    AddLerp(v, "alpha", 1, 0.15, nil, EaseInCubic)

    v.x = -70
    AddLerp(v, "x", 0, 0.15, nil, EaseInCubic)
  end

  self.alpha = 0
  AddLerp(self, "alpha", 1, 0.15, function() 
    for k, v in pairs(self.buttons) do
      v.pressable = true
    end
  end, EaseInCubic)


end



