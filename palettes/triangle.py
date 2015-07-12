import imgen
import math


class Palette(imgen.Palette):
    def __init__(self):
        imgen.Palette.__init__(self)

        base = imgen.random_hsl()
        hues = [
            base[0],
            base[0] + 0.33,
            base[0] - 0.33
        ]
        saturation = base[1]

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, saturation, base[2]))
            )
