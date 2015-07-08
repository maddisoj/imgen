#ifndef IMGEN_PALETTE_HPP_
#define IMGEN_PALETTE_HPP_

#include <boost/gil/gil_all.hpp>
#include <vector>

#include "colour.hpp"

namespace imgen {
    /** alias for boost gil */
    namespace gil = boost::gil;

    /**
     * A palette defines the colours available for the current image and
     * provides methods for mixing between those colours.
     */
    class palette {
        public:
            std::vector<colour> colours;

            /** Proptionally blends two colours in the palette. */
            virtual colour blend(int left, int right, float proportion) = 0;
    };

} // namespace imgen

#endif // IMGEN_PALETTE_HPP_
