
class dot:

    def __init__(self):
        self.x = 0
        self.y = 0

    def incX(self):
        self.x += 1

    def incY(self):
        self.y += 1

# Example file showing a circle moving on screen
import pygame

# pygame setup
pygame.init()
screen = pygame.display.set_mode((512, 512))
clock = pygame.time.Clock()
running = True
dt = 0

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)
pygame.mouse.set_cursor(*pygame.cursors.arrow)

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("black")
    pygame.draw.circle(screen, "white", player_pos, 1)
    left, middle, right = pygame.mouse.get_pressed()

    if left:
        player_pos = pygame.mouse.get_pos()
        print(player_pos)


    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    dt = clock.tick(60) / 1000

pygame.quit()