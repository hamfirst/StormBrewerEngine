
DefaultControls = Elem:construct()

function DefaultControls:setup(o)
  Elem:setup(o)

  o.audio = AudioControl:new()
  o.audio.x = 0

  o.music = MusicControl:new()
  o.music.x = 40

  o.fullscreen = FullScreenControl:new()
  o.fullscreen.x = 80

  o.width = 112
  o.height = 32
end
