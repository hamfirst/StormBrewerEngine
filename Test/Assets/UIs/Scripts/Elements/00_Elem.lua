
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

  o.clickable.OnRender = function()
    o:Render()
  end

  o.clickable.OnStateChange = function(old_state, new_state)
    o:StateChanged(old_state, new_state)
  end

  o.clickable.OnClick = function()
    o:Clicked()
  end

  return o
end

function Elem:new(o)
  o = self:construct(o)
  self:setup(o)
  return o
end

function Elem:Update(dt)

end

function Elem:Render()

end

function Elem:StateChanged(old_state, new_state)

end

function Elem:Clicked()

end

function Elem:SetParent(parent)
  self.clickable:SetParent(parent.clickable)
  self.parent = parent
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

