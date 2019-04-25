
Elem = {
  x = 0,
  y = 0,
  width = 0,
  height = 0
}

function Elem:construct(o)
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  return o
end

function Elem:setup(o)

  o.clickable = Clickable:new()
  o.clickable.OnUpdate = function (dt)
    o:Update(dt)
    o.clickable.X = o.x
    o.clickable.Y = o.y
    o.clickable.Width = o.width
    o.clickable.Height = o.height
  end

  o.clickable.OnDraw = function()
    o:Draw()
  end

  o.clickable.OnStateChange = function(old_state, new_state)
    o:StateChanged(old_state, new_state)
  end

  o.clickable.OnMouseEnter = function(x, y)
    o:MouseEntered(x, y)
  end

  o.clickable.OnMouseMove = function(x, y)
    o:MouseMoved(x, y)
  end

  o.clickable.OnMouseLeave = function()
    o:MouseLeft()
  end

  o.clickable.OnMouseScroll = function(dv)
    o:MouseScrolled(dv)
  end

  o.clickable.OnClick = function()
    o:Clicked()
  end

  return o
end

function Elem:new(parent)
  local o = self:construct(nil)
  self:setup(o)

  if parent ~= nil then
    o.clickable:SetParent(parent.clickable)  
    o.parent = parent
  end
  return o
end

function Elem:destroy()
  self:Destroyed()

  if self.clickable ~= nil then
      self.clickable:delete()
      self.clickable = nil
  end

  if self.context ~= nil then
      self.context:delete()
      self.context = nil
  end

  RemoveAllLerps(self)
end

function Elem:Update(dt)

end

function Elem:Draw()

end

function Elem:StateChanged(old_state, new_state)

end

function Elem:MouseEntered(x, y)

end

function Elem:MouseMoved(x, y)

end

function Elem:MouseLeft()

end

function Elem:MouseScrolled(dv)
  if self.scroll_proxy ~= nil then
    self.scroll_proxy:MouseScrolled(dv)
  end
end

function Elem:Clicked()

end

function Elem:SetParent(parent)

  if parent ~= nil then
    self.clickable:SetParent(parent.clickable)  
    self.parent = parent
  else
    self.clickable:SetParent(nil)  
    self.parent = nil
  end
end

function Elem:GetParent(self)
  return self.parent
end

function Elem:GetState()
  return self.clickable:GetState()
end

function Elem:SetEnabled(enabled)
  self.clickable.Enabled = enabled
end

function Elem:SetClip(enabled)
  self.clickable.Clip = enabled
end

function Elem:SetWantsInput(enabled)
  self.clickable.WantsInput = enabled
end

function Elem:Destroyed()

end

