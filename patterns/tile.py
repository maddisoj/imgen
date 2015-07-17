import imgen
import random


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        num_colors = len(palette.colors)
        cols = random.randint(1, 10)

        if cols % num_colors == 0:
            cols += 1

        rows = cols
        ratio = image.width() / image.height()

        if ratio < 1.0:
            cols = round(cols / ratio)
        else:
            rows = round(rows / ratio)

        width = image.width() / cols
        height = image.height() / rows

        for c in range(cols):
            for r in range(rows):
                x = width * c
                y = height * r

                color = palette.colors[(c * cols + r) % num_colors]

                context.set_color(color)
                context.rectangle(x, y, x + width, y + height)
                context.fill()
