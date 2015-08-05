import imgen
import math
import random


# Generates colours whose hues are evenly distributed around the colour wheel.
# The saturation and lightness are the same for each colour with both being
# clamped to a subset to prevent murky colours.
class Palette(imgen.Palette):
    def generate(self, **kwargs):
        colors = []
        lower = kwargs['lower'] if 'lower' in kwargs else 1
        upper = kwargs['upper'] if 'upper' in kwargs else 10
        amount = kwargs['amount'] if 'amount' in kwargs else random.randint(lower, upper)
        step = 1 / amount
        base = random.uniform(0.0, 1.0)
        lightness = random.uniform(0.2, 0.8)
        saturation = random.uniform(0.4, 0.8)
        hues = [base + i * step for i in range(amount)]

        for hue in hues:
            if hue < 0.0 or hue > 1.0:
                hue -= math.floor(hue)

            colors.append(imgen.hsl2rgb(imgen.hsl(hue, saturation, lightness)))

        return colors
