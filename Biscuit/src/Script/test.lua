function test:on_update(dt)
    speed = 500.0;
    pos = self.sprite:get_pos();
    if Input.is_key_pressed(key.KEY_A) then
        pos.x = pos.x - dt * speed
    end
    if Input.is_key_pressed(key.KEY_D) then
        pos.x = pos.x + dt * speed
    end
    if Input.is_key_pressed(key.KEY_W) then
        pos.y = pos.y - dt * speed
    end
    if Input.is_key_pressed(key.KEY_S) then
        pos.y = pos.y + dt * speed
    end
    self.sprite:set_pos(pos);
end

function test:on_attached()
   self.sprite:set_scale(1.25)
end

