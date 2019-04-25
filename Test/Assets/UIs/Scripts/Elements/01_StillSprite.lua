
StillSprite = Elem:construct()
StillSprite.alpha = 1
StillSprite.parent_alpha = 1
StillSprite.anim_index = 0
StillSprite.anim_frame = 0
StillSprite.draw_frame = false

function StillSprite:SetSprite(sprite_id, anim_index, anim_frame)
    self.sprite_id = sprite_id
    self.anim_index = anim_index
    self.anim_frame = anim_frame
    self.width, self.height = ui:GetSpriteSize(sprite_id, anim_index, anim_frame)
end

function StillSprite:Draw()
    local alpha = self.alpha * self.parent_alpha
    
    if alpha == 0 then
        return
    end

    local width, height = ui:GetSpriteSize(self.sprite_id, self.anim_index, self.anim_frame)

    if width > 0 and height > 0 then
        ui:DrawSprite(self.sprite_id, width / 2, height / 2, false, false, self.anim_index, self.anim_frame, alpha)
    end

    if self.draw_frame then
        ui:DrawRectangle(0, 0, self.width - 1, self.height - 1, 0, 0, 0, alpha)
        ui:FlushGeometry()
    end

end

