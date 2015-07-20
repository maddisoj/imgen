import imgen
import sys
import math
import random


def eucludean_distance(a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]

    return math.sqrt(dx ** 2 + dy ** 2)


def random_point(image, circles):
    while True:
        x = random.uniform(0, image.width())
        y = random.uniform(0, image.height())
        # Ensure that any distance is smaller than the starting distance
        closest_distance = sys.float_info.max

        for circle in circles:
            distance = eucludean_distance((circle["x"], circle["y"]),
                                          (x, y))

            if distance < circle["radius"]:
                closest_distance = sys.float_info.max

                break
            elif (distance - circle["radius"]) < closest_distance:
                closest_distance = distance - circle["radius"]
        else:
            return x, y, closest_distance


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        circles = []
        colors = list(palette.colors)
        bg_color = colors[random.randint(0, len(colors) - 1)]

        context.set_color(bg_color)
        context.rectangle(0, 0, image.width(), image.height())
        context.fill()
        colors.remove(bg_color)

        edges = [
            (0, 0, 0, image.height()),
            (0, 0, image.width(), 0),
            (image.width(), 0, image.width(), image.height()),
            (0, image.height(), image.width(), image.height())
        ]

        for i in range(random.randint(100, 1000)):
            x, y, circle_distance = random_point(image, circles)
            color = random.randint(0, len(colors) - 1)
            edge_distance = sys.float_info.max

            for edge in edges:
                ax, ay = (x - edge[0], y - edge[1])
                bx, by = (edge[2] - edge[0], edge[1] - edge[3])
                dot = ax * bx + ay * by
                t = dot / (bx ** 2 + by ** 2)
                cx, cy = (edge[0] + t * bx, edge[1] + t * by)

                edge_distance = min(edge_distance,
                                    eucludean_distance((x, y), (cx, cy)))

            max_radius = min(edge_distance, circle_distance)
            radius = random.uniform(0.8, 1.0) * max_radius

            context.set_color(colors[color])
            context.circle(x, y, radius)
            context.fill()

            circles.append({
                "x": x,
                "y": y,
                "radius": radius
            })
