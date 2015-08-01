import imgen
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        steps = 20
        num_colors = len(palette.colors)
        x_step = image.width() / steps
        y_step = image.height() / steps
        grid = []

        # First we construct a grid to use as the corners of our triagnles, the
        # location of each point on the grid is moved by a random percentage
        # each way to make things less ordered.
        for y in range(steps + 1):
            row = []

            for x in range(steps + 1):
                point = imgen.Point(x, y)

                # Clamp the points on the edges to the edges
                if x != 0 and x != steps and y != 0 and y != steps:
                    point.x += random.uniform(-0.25, 0.25)
                    point.y += random.uniform(-0.25, 0.25)

                point.x *= x_step
                point.y *= y_step

                row.append(point)
            grid.append(row)

        context.clear()

        # We don't want to iterate over the last row & column as they should
        # only exist to "close" the triangles.
        for r, row in enumerate(grid[:-1]):
            next_row = grid[r + 1]

            for p, point in enumerate(row[:-1]):
                corners = [
                    point, row[p + 1], next_row[p], next_row[p + 1]
                ]

                for triangle in (corners[0:3], corners[1:4]):
                    path = imgen.Path()

                    context.set_color(palette.random_color())
                    path.move_to(triangle[0])
                    path.line_to(triangle[1])
                    path.line_to(triangle[2])
                    path.fill(context)

                    # Also stroke the path to prevent a small transparent
                    # border between the triangles due to subpixel precision.
                    path.stroke(context)
