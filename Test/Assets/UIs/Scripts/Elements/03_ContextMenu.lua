
ContextMenu = Elem:construct()
ContextMenu.content_width = 0
ContextMenu.content_height = 0
ContextMenu.alpha = 1
ContextMenu.fading = false
ContextMenu.show_id = 0

function ContextMenu:setup(o)
  Elem:setup(o)

  o.elems = {}
  o.next_elem_id = 0
end

function ContextMenu:Destoyed()
  self:Reset()
end

function ContextMenu:Update(dt)
  if self.fading == false then    
    self:RepositionElements()
  end
end

function ContextMenu:Reset(show_id)

  if show_id ~= self.show_id and show_id ~= nil then
    return
  end

  for k, v in pairs(self.elems) do
    v:destroy()
  end

  self.elems = {}
  self.next_elem_id = 0
  self.content_width = 0
  self.content_height = 0
  self.alpha = 1
  self.fading = false
  self.show_id = self.show_id + 10
  self.x = 0
  self.y = 0
  self.width = 0
  self.height = 0

  ClearLerp(self, "alpha")

  context_menu_fader:SetAlpha(0)
end

function ContextMenu:PushMenuAction(text, func)
  local button = Button:new()
  button:SetParent(self)
  button.text = text
  button.Pressed = function()

    self.fading = true

    for k, v in pairs(self.elems) do
      v.pressable = false
      if v ~= button then
        AddLerp(v, "alpha", 0, 0.1, nil, EaseInCubic)
      end
    end

    AddLerp(self, "alpha", 0, 0.3, function() self:Reset() end, EaseInCubic)

    func()

  end

  local width, height = ui:MeasureText(font, text)

  self.elems[self.next_elem_id] = button
  self.next_elem_id = self.next_elem_id + 1

  self.content_width = math.max(self.content_width, width + 20)
  self.content_height = self.content_height + 15
 
end

function ContextMenu:Show(x, y, ondismissed)

  self.show_id = self.show_id + 1

  self.x = x
  self.y = y
  self.width = 0
  self.height = self.content_height
  self.alpha = 0
  self.ondismissed = ondismissed

  AddLerp(self, "width", self.content_width, 0.1, nil, EaseInCubic)
  AddLerp(self, "alpha", 1, 0.1, nil, EaseInCubic)

  context_menu_fader:FadeToSolid()

  return self.show_id
end

function ContextMenu:RepositionElements()

  local y = self.height

  for k, v in pairs(self.elems) do
    y = y - 15

    v.x = 0
    v.y = y
    v.height = 15
    v.width = self.width - 1
    v.alpha = self.alpha
  end
end

function CreateContextMenu()
  context_menu_fader = PushMenuElement(Fader:new())
  context_menu_fader:SetAlpha(0)
  context_menu_fader.target_alpha = 0.05
  context_menu_fader.fade_time = 0.1

  context_menu = PushMenuElement(ContextMenu:new())

  function context_menu_fader:Clicked()
    context_menu:Reset()
    
    if context_menu.ondismissed ~= nil then
      context_menu.ondismissed()
    end
  end
end

