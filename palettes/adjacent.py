import imgen
import math


class Palette(imgen.Palette):
    def __init__(self):
        super().__init__()

        base = imgen.random_hsl()

        # Hue is in the range [0, 1] with 0 being degrees and 1 being 360. So
        # to rotate a hue x degrees you add x/360.
        hues = [
            base[0],
            base[0] + 20.0 / 360,
            base[0] - 20.0 / 360,
        ]

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, base[1], base[2]))
            )
