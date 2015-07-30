#ifndef IMGEN_PALETTE_HPP_
#define IMGEN_PALETTE_HPP_

#include "imgen/linker.hpp"
#include "imgen/color.hpp"

#include <boost/gil/gil_all.hpp>

#include <algorithm>
#include <cstdlib>
#include <vector>

namespace gil = boost::gil;

namespace imgen {

/**
 * A palette defines the colours available for the current image and
 * provides methods for mixing between those colours.
 */
struct palette {
    typedef gil::rgb32f_pixel_t color_t;

    std::vector<color_t> colors;

    /**
     * Linearly blends the colour at index `left` with the colour at index
     * `right`. The proportion is clamped to [0, 1] with 0 being the `left`
     * colour and 1 being the `right` colour.
     */
    virtual color_t blend(int left, int right, double proportion) const;

    /**
     * Gets the lightest colour in the palette, if the palette is empty returns
     * white.
     */
    virtual color_t lightest() const;

    /**
     * Gets the darkest colour in the palette, if the palette is empty returns
     * black.
     */
    virtual color_t darkest() const;

    /**
     * Gets a random color from this palette. If the palette is empty returns
     * a random color.
     */
    color_t random_color() const;
};

/**
 * The linker for extracting palettes
 */
struct palette_linker : linker<palette> {
    using linker<palette>::linker;

    const std::string python_class() const
    {
        return "Palette";
    }
};

} // namespace imgen

#endif // IMGEN_PALETTE_HPP_
