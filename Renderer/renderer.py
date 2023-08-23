import pygame
import math

G = 6.67430e-11
time_frame = 2


class Dot:

    def __init__(self, player_pos_vec, mass=1000, velocity=0.1, direction=0, acceleration=0, color="white"):
        self.vec = player_pos_vec
        self.mass = mass
        

# pygame setup
pygame.init()
screen = pygame.display.set_mode((512, 512))
clock = pygame.time.Clock()
running = True
dt = 0

dots = []
dots.append(Dot(pygame.Vector2(265, 120), mass=10 ** 7, ))
dots.append(Dot(pygame.Vector2(250, 250), mass=10 ** 9, color="red"))
dots.append(Dot(pygame.Vector2(150, 150), mass=10 ** 7))
dots.append(Dot(pygame.Vector2(10, 10), mass=10 ** 7))


def move_dot(dot):
    global time_frame
    pygame.draw.circle(screen, dot.color, dot.vec, 3)
    draw_velocity_direction(dot)

    left, middle, right = pygame.mouse.get_pressed()

    if left:
        time_frame += 10

    if right:
        time_frame -= 10


def draw_velocity_direction(dot):
    # Calculate the endpoint of the line based on velocity and direction
    end_point = ((dot.vec.x + 15 * dot.velocity * time_frame * math.cos(dot.direction)),
                 (dot.vec.y + 15 * dot.velocity * time_frame * math.sin(dot.direction)))
    pygame.draw.line(screen, "blue", dot.vec, end_point, 3)


while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill("black")

    for i in range(len(dots)):
        for j in range(len(dots)):
            if i != j:
                dots[i].update_pos(dots[j])

        move_dot(dots[i])
        print(i, dots[i].acceleration, dots[i].velocity, dots[i].vec.xy, dots[i].direction)

    # important shit to run
    pygame.display.flip()
    dt = clock.tick(60) / 1000

pygame.quit()
