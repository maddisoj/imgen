import imgen
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        colors = list(palette.colors)
        bg_color = colors.pop(random.randint(0, len(colors) - 1))

        context.set_color(bg_color)
        context.rectangle(0, 0, image.width(), image.height())
        context.fill()

        while colors:
            color = colors.pop(random.randint(0, len(colors) - 1))
            direction = random.randint(0, 1)
            position = random.uniform(0, 1)
            path = imgen.Path(1)

            if direction == 0:  # Horizontal
                y = position * image.height()

                path.move_to(imgen.Point(0, y))
                path.line_to(imgen.Point(image.width(), y))
            else:  # Vertical
                x = position * image.width()

                path.move_to(imgen.Point(x, 0))
                path.line_to(imgen.Point(x, image.height()))

            context.set_color(color)
            path.draw(context)
            context.stroke()
