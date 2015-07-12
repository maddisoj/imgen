#ifndef IMGEN_PALETTE_HPP_
#define IMGEN_PALETTE_HPP_

#include "imgen/color.hpp"
#include "imgen/linker.hpp"

#include <boost/gil/gil_all.hpp>
namespace gil = boost::gil;

#include <vector>

namespace imgen {

/**
 * A palette defines the colours available for the current image and
 * provides methods for mixing between those colours.
 */
class palette {
public:
    std::vector<color_t> colors;
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
