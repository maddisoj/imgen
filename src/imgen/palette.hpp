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

    /**
     * Request a collection of colors from this palette.
     */
    virtual std::vector<color_t> generate() = 0;
    virtual std::vector<color_t> generate(int amount) = 0;
    virtual std::vector<color_t> generate(int min, int max) = 0;
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
