
DefaultControls = Elem:construct()

function DefaultControls:setup(o)
  Elem:setup(o)

  o.audio = AudioControl:new()
  o.audio.x = 0
  o.audio:SetParent(o)

  o.music = MusicControl:new()
  o.music.x = 40
  o.music:SetParent(o)

  o.fullscreen = FullScreenControl:new()
  o.fullscreen.x = 80
  o.fullscreen:SetParent(o)

  o.width = 112
  o.height = 32
end

function CreateDefualtControls()
  local default_controls = PushMenuElement(DefaultControls:new())
  default_controls.x = half_screen_width - 120
  default_controls.y = half_screen_height - 40
  return default_controls
end