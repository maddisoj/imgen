import imgen


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        num_colors = len(palette.colors)
        width = image.width() / num_colors
        height = image.height()
        x = 0

        for color in palette.colors:
            context.set_color(color)
            context.rectangle(x, 0.0, x + width, height)
            context.fill()

            x += width
