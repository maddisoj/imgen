import imgen
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        steps = 20
        x_step = image.width() / steps
        y_step = image.height() / steps
        grid = []

        for y in range(steps + 1):
            row = []

            for x in range(steps + 1):
                x_jitter = 0
                y_jitter = 0

                # Clamp the points on the edges to the edges
                if x != 0 and x != steps and y != 0 and y != steps:
                    x_jitter = random.uniform(-0.25, 0.25)
                    y_jitter = random.uniform(-0.25, 0.25)

                point = imgen.Point((x + x_jitter) * x_step,
                                    (y + y_jitter) * y_step)

                row.append(point)

            grid.append(row)

        context.clear()
        context.set_color(imgen.rgb(1, 1, 1))

        # We don't want to iterate over the last row & column as they should be
        # used to "close" the triangles
        for r, row in enumerate(grid[:-1]):
            next_row = grid[r + 1]

            for p, point in enumerate(row[:-1]):
                path = imgen.Path()

                path.move_to(point)
                path.line_to(row[p + 1])
                path.line_to(next_row[p])
                path.draw(context)
                context.stroke()
