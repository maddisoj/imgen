import imgen
import math
from random import uniform


class Palette(imgen.Palette):
    def __init__(self):
        imgen.Palette.__init__(self)

        base = imgen.rgb2hsl(imgen.random_color())
        hues = [
            base[0],
            base[0] + 0.33,
            base[0] - 0.33
        ]
        saturation = base[1] if base[1] >= 0.5 else uniform(0.5, 1.0)

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, saturation, base[2]))
            )

        def blend(left, right, proportion):
            return imgen.random_color()


if __name__ == "__main__":
    palette = Palette()

    for color in palette.colors:
        print(color[0], color[1], color[2])
