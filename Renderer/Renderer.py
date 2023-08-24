import pygame

class Renderer:
    
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((1280, 720))
        self.screen.fill("blue")
        self.clock = pygame.time.Clock()
        self.running = True
        self.dt = 0
        print("ahhh")
    
    def updateScreen(self, points):
        
        # self.screen.fill("black")
        print(points)
        for point in points:
            x, y = map(int, point)  # Convert the coordinates to integers
            pygame.draw.circle(self.screen, "white", point, 1)
            
        
        pygame.display.update()

        # limits FPS to 60
        # dt is delta time in seconds since last frame, used for framerate-
        # independent physics.
        self.dt = self.clock.tick(60) / 1000
        pygame.time.delay(5)
    
    def __del__(self):
        pygame.quit()
