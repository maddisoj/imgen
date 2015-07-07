#ifndef WALLGEN_X_COLOUR_H_
#define WALLGEN_X_COLOUR_H_

#include <memory>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <cmath>

#include <xcb/xcb.h>
#include <format.h>

#include "util.h"

namespace wallgen {
namespace x {

typedef uint32_t Pixel;
typedef xcb_colormap_t ColourMap;

Pixel getColour(const Connection& conn, ColourMap map,
                uint16_t red, uint16_t green, uint16_t blue);

template<typename T>
Pixel getColour(const Connection& conn, ColourMap map, T red, T green, T blue) {
    auto max = std::numeric_limits<uint16_t>::max();
    auto r = static_cast<uint16_t>(std::floor(red * max));
    auto g = static_cast<uint16_t>(std::floor(green * max));
    auto b = static_cast<uint16_t>(std::floor(blue * max));

    return getColour(conn, map, r, g, b);
}

} // namespace x
} // namespace wallgen

#endif // WALLGEN_X_COLOUR_H_
