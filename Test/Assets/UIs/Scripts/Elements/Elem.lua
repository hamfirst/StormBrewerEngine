
Elem = {
  x = 0
  y = 0
  width = 0
  height = 0
}

function Elem:new(o)
  o = o or {}
  setmetatable(o, self)
  self.__index = self

  o.clickable = Clickable:new()
  o.clickable.OnUpdate(dt) = function (dt)
    o.Update(dt)
    o.clickable.X = o.x
    o.clickable.Y = o.Y
    o.clickable.Width = o.Width
    o.clickable.Height = o.Height
  end

  return o
end

function Elem:Update(dt)

end

function Elem:SetParent(parent)
  self.clickable.SetParent(parent.clickable)
end

function Elem:GetParent(self)
  return self.clickable.GetParent()
end

