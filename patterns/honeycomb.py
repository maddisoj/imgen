import imgen
import math
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        colors = palette.generate(exactly=2)
        steps = random.randint(10, 50)
        smallest_dim = min(image.width(), image.height())
        step = smallest_dim / steps
        vertices = [
            imgen.Point(0.2, 0) * step,
            imgen.Point(0.8, 0) * step,
            imgen.Point(1.0, 0.5) * step,
            imgen.Point(0.8, 1.0) * step,
            imgen.Point(0.2, 1.0) * step,
            imgen.Point(0.0, 0.5) * step
        ]
        comb = imgen.Path(2)
        top_color = colors.pop(random.randint(0, len(colors) - 1))
        bottom_color = colors.pop(random.randint(0, len(colors) - 1))

        for i, vertex in enumerate(vertices):
            if i == 0:
                comb.move_to(vertex)
            else:
                comb.line_to(vertex)

        start = -0.5 * step
        x_step = 0.8 * step
        column = 0
        pos = imgen.Point(start, start)
        bottom_edge = (
            imgen.Point(0, image.height()),
            imgen.Point(image.width(), image.height())
        )

        context.clear()
        context.translate(start, start)

        while pos.x <= (image.width() + step):
            pos.x += x_step
            pos.y = start
            column += 1

            if column % 2 == 0:
                context.translate(0, 0.5 * step)
                pos.y += 0.5 * step

            while pos.y <= (image.height() + step):
                distance = imgen.distance(pos, bottom_edge)
                t = (distance / image.height()) + random.uniform(0, 1)
                color = imgen.blend(bottom_color, top_color, t)

                context.set_color(0, 0, 0)
                comb.stroke(context)
                context.set_color(color)
                comb.fill(context)
                context.translate(0, step)

                pos.y += step

            context.translate(x_step, -(pos.y + abs(start)))
