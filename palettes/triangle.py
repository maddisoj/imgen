import imgen
import math
import random


class Palette(imgen.Palette):
    def __init__(self):
        super().__init__()

        base = random.uniform(0.0, 1.0)
        hues = [
            base,
            base + 0.33,
            base - 0.33
        ]
        # Clamp lightness to [0.2, 0.8] to stop really dark or really light
        # colours
        lightness = random.uniform(0.2, 0.8)

        # Clamp saturation to prevent washed out colours.
        saturation = random.uniform(0.2, 0.8)

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, saturation, lightness))
            )
