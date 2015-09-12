import imgen
import math
import random


# Generates colours whose hues are distributed in 2/5 of the colour wheel. The
# saturation and lightness are the same for each colour with both being clamped
# to a subset to prevent murky colours.
class Palette(imgen.Palette):
    def generate(self, **kwargs):
        colors = []
        lower = kwargs['at_least'] if 'at_least' in kwargs else 1
        upper = kwargs['at_most'] if 'at_most' in kwargs else 10
        amount = kwargs['exactly'] if 'exactly' in kwargs else random.randint(lower, upper)
        base = random.uniform(0.0, 1.0)
        lightness = random.uniform(0.2, 0.8)
        saturation = random.uniform(0.4, 1.0)
        step = 0.4 / amount
        hues = [base + i * step for i in range(amount)]

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, lightness, saturation))
            )

        return colors
