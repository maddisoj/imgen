#ifndef IMGEN_COLOR_HPP_
#define IMGEN_COLOR_HPP_

#include <boost/gil/gil_all.hpp>

namespace imgen {
    namespace gil = boost::gil;

    /** Alias to the GIL pixel type imgen is using as it's colour type. */
    typedef gil::rgb8_pixel_t color;

} // namespace imgen

#endif // IMGEN_COLOR_HPP_
