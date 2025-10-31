function test:on_update(dt)
    a = self.sprite:get_pos()
    a.x = a.x + dt * 100
    print(1)
    self.sprite:set_pos(a)
end

function test:on_attached()
   self.sprite:set_scale(0.2) 
end


