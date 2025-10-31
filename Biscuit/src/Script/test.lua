test = 
{
    speed = 300
    update = function(self, dt)
       self.transform.x += Input.horizontal * speed * dt
       self.transform.y += Input.vertical * speed * dt
    end
}
