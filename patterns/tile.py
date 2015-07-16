import imgen
import math


class Pattern(imgen.Pattern):
    def draw(self, image, context, palette):
        num_tiles = 10
        num_colors = len(palette.colors)
        width = image.width() / num_tiles
        height = image.height() / num_tiles

        for tile in range(0, num_tiles ** 2):
            x = max(0, width * (tile % num_tiles))
            y = max(0, height * math.floor(tile / num_tiles))
            color = palette.colors[tile % num_colors]

            context.set_color(color)
            context.rectangle(x, y, x + width, y + height)
            context.fill()
