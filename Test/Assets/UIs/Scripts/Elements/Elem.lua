
Elem = {
  new = function(elem_meta)
    elem = {
      clickable = Clickable:new()

      x = 0
      y = 0
      width = 0
      height = 0

      SetParent = function(self, parent)
        self.clickable.SetParent(parent.clickable)
      end

      GetParent = function(self)
        return self.clickable.GetParent()
      end
    }

    elem.clickable.OnUpdate = function(dt)
      elem.clickable.X = elem.x
      elem.clickable.Y = elem.y
      elem.clickable.Width = elem.width
      elem.clickable.Height = elem.height
    end

    setmetatable(elem, elem_meta)
    return elem;
  end
}

