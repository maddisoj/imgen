#ifndef IMGEN_PALETTE_HPP_
#define IMGEN_PALETTE_HPP_

#include "imgen/linker.hpp"

#include <boost/gil/gil_all.hpp>

#include <vector>

namespace gil = boost::gil;

namespace imgen {

/**
 * A palette defines the colours available for the current image and
 * provides methods for mixing between those colours.
 */
class palette {
public:
    std::vector<gil::rgb32f_pixel_t> colors;
};

/**
 * The linker for extracting palettes
 */
struct palette_linker : linker<palette> {
    using linker<palette>::linker;

    const std::string python_class() {
        return "Palette";
    }
};

} // namespace imgen

#endif // IMGEN_PALETTE_HPP_
