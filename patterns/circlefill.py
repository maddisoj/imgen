import imgen
import sys
import random


def random_point(image, circles):
    while True:
        point = imgen.Point(random.uniform(0, image.width()),
                            random.uniform(0, image.height()))
        # Ensure that any distance is smaller than the starting distance
        closest_distance = sys.float_info.max

        for circle in circles:
            distance = imgen.distance(circle["center"], point)

            if distance < circle["radius"]:
                closest_distance = sys.float_info.max

                break
            elif (distance - circle["radius"]) < closest_distance:
                closest_distance = distance - circle["radius"]
        else:
            return point, closest_distance


# Fill most of the image with non-overlapping circles of variant radiuses.
class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        circles = []
        colors = palette.generate(lower=2)
        bg_color = colors[random.randint(0, len(colors) - 1)]

        context.clear(bg_color)
        colors.remove(bg_color)

        edges = [
            # Top
            (imgen.Point(0, 0),
             imgen.Point(image.width(), 0)),
            # Bottom
            (imgen.Point(0, image.height()),
             imgen.Point(image.width(), image.height())),
            # Left
            (imgen.Point(0, 0),
             imgen.Point(0, image.height())),
            # Right
            (imgen.Point(image.width(), 0),
             imgen.Point(image.width(), image.height())),
        ]

        for i in range(random.randint(200, 1000)):
            point, circle_distance = random_point(image, circles)
            color = colors[random.randint(0, len(colors) - 1)]
            edge_distance = min(imgen.distance(point, edge) for edge in edges)
            max_radius = min(edge_distance, circle_distance)
            radius = random.uniform(0.8, 1.0) * max_radius

            context.set_color(color)
            context.circle(point.x, point.y, radius)
            context.fill()

            circles.append({
                "center": point,
                "radius": radius
            })
