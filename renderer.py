import pygame
import math

G = 6.67430e-11
time_frame = 1


class Dot:

    def __init__(self, player_pos_vec, mass=100000000000, velocity=0, direction=0, acceleration=0):
        self.vec = player_pos_vec
        self.mass = mass
        self.velocity = velocity
        self.direction = direction
        self.acceleration = acceleration

    def calc_force(self, other_dot):
        r_squared = self.vec.distance_to(other_dot.vec) ** 2
        force = G * (self.mass * other_dot.mass) / r_squared
        return force

    def calc_acc(self, other_dot):
        self.acceleration = self.calc_force(other_dot)/self.mass
        return self.acceleration

    def update_velocity(self, other_dot):
        self.velocity = self.velocity + self.calc_acc(other_dot) * time_frame

    def update_direction(self, other_dot):
        dx = other_dot.vec.x - self.vec.x
        dy = other_dot.vec.y - self.vec.y
        self.direction = math.atan2(dy, dx)

    def update_pos(self, other_dot):
        self.update_velocity(other_dot)
        self.update_direction(other_dot)
        self.vec.x = self.vec.x + self.velocity * time_frame * math.cos(self.direction)
        self.vec.y = self.vec.y + self.velocity * time_frame * math.sin(self.direction)


# pygame setup
pygame.init()
screen = pygame.display.set_mode((512, 512))
clock = pygame.time.Clock()
running = True
dt = 0

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)
pygame.mouse.set_cursor(*pygame.cursors.arrow)


dot1 = Dot(pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2))
dot2 = Dot(pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2))
dot2.vec.xy = (200, 200)
dot1.vec.xy = (10, 10)


def move_dot(dot):
    pygame.draw.circle(screen, "white", dot.vec, 1)

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

    dot1.update_pos(dot2)
    dot2.update_pos(dot1)
    move_dot(dot1)
    move_dot(dot2)
    print(dot1.velocity)
    print(dot1.vec.xy)

    # important shit to run
    pygame.display.flip()
    dt = clock.tick(60) / 1000

pygame.quit()
