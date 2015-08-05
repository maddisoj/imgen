import imgen
import math
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        colors = palette.generate(lower=5)
        steps = random.randint(10, 50)
        smallest_dim = min(image.width(), image.height())
        step = smallest_dim / steps
        grid = []
        y = random.uniform(-0.5, 0) * step
        start_x = random.uniform(-0.5, 0) * step

        while y <= (image.height() + step):
            x = start_x
            row = []

            while x <= (image.width() + step):
                row.append(imgen.Point(x, y))
                x += step

            grid.append(row)
            y += step

        context.clear()
        breakpoints = len(colors)
        origin = imgen.Point(
            random.uniform(0, image.width()),
            random.uniform(0, image.height())
        )

        for r, row in enumerate(grid[:-1]):
            next_row = grid[r + 1]

            for p, point in enumerate(row[:-1]):
                corners = [
                    point, row[p + 1],
                    next_row[p], next_row[p + 1]
                ]

                for triangle in (corners[0:3], corners[1:4]):
                    path = imgen.Path()
                    distance = (triangle[0] - origin).length() / smallest_dim
                    t = random.uniform(0.0, 1.0) * distance
                    index = math.floor(distance / breakpoints)
                    color = imgen.blend(colors[index], colors[index + 1], t)

                    context.set_color(color)
                    path.move_to(triangle[0])
                    path.line_to(triangle[1])
                    path.line_to(triangle[2])
                    path.fill(context)
                    path.stroke(context)
