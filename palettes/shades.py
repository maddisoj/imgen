import imgen
import random


class Palette(imgen.Palette):
    def __init__(self):
        super().__init__()

        lightnesses = [
            random.uniform(0.2, 0.8) for i in range(random.randint(3, 6))
        ]

        hue = random.uniform(0.0, 1.0)
        saturation = random.uniform(0.4, 1.0)

        for lightness in lightnesses:
            self.colors.append(
                imgen.hsl2rgb(imgen.hsl(hue, saturation, lightness))
            )
