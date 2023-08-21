import pygame


class Dot:

    def __init__(self, player_pos_vec, mass):
        self.vec = player_pos_vec
        self.mass = mass


# pygame setup
pygame.init()
screen = pygame.display.set_mode((512, 512))
clock = pygame.time.Clock()
running = True
dt = 0

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)
pygame.mouse.set_cursor(*pygame.cursors.arrow)


def move_dot():
    pygame.draw.circle(screen, "white", player_pos, 1)

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        player_pos.y -= 300 * dt
    if keys[pygame.K_s]:
        player_pos.y += 300 * dt
    if keys[pygame.K_a]:
        player_pos.x -= 300 * dt
    if keys[pygame.K_d]:
        player_pos.x += 300 * dt

    left, middle, right = pygame.mouse.get_pressed()

    if left:
        player_pos.xy = pygame.mouse.get_pos()


while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill("black")

    move_dot()

    # important shit to run
    pygame.display.flip()
    dt = clock.tick(60) / 1000

pygame.quit()
