#ifndef IMGEN_COLOR_HPP_
#define IMGEN_COLOR_HPP_

#include <boost/gil/gil_all.hpp>

namespace imgen {
    namespace gil = boost::gil;

    typedef gil::rgb8_pixel_t color_t;
    typedef gil::channel_type<color_t>::type channel_t;

    /** Creates a random colour */
    color_t random_colour();
} // namespace imgen

#endif // IMGEN_COLOR_HPP_
