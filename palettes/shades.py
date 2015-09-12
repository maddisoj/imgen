import imgen
import math
import random


# Generates colours whose lightnesses are evenly distributed around the colour
# wheel. The hue and saturation remain the same for each colour. The
# saturation and lightness are clamped to a subset to prevent murky colours
class Palette(imgen.Palette):
    def generate(self, **kwargs):
        colors = []
        lower = kwargs['at_least'] if 'at_least' in kwargs else 3
        upper = kwargs['at_most'] if 'at_most' in kwargs else 6
        amount = kwargs['exactly'] if 'exactly' in kwargs else random.randint(lower, upper)
        base = random.uniform(0.2, 0.8)
        hue = random.uniform(0.0, 1.0)
        saturation = random.uniform(0.4, 0.8)
        lightnesses = [
            base + (i / amount) for i in range(amount)
        ]

        for lightness in lightnesses:
            if lightness < 0.0 or lightness > 1.0:
                lightness -= math.floor(lightness)

            colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, saturation, lightness))
            )

        return colors
