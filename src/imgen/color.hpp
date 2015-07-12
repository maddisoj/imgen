#ifndef IMGEN_COLOR_HPP_
#define IMGEN_COLOR_HPP_

#include <boost/gil/gil_all.hpp>
#include <format.h>

#include <string>
#include <ostream>
#include <cstdlib>

namespace imgen {

namespace gil = boost::gil;

typedef gil::rgb8_pixel_t color_t;
typedef gil::channel_type<color_t>::type channel_t;

template<typename ColorBase>
ColorBase random_color() {
    /** Use bits8 to generate the random number so we can take advantage of
     *  the modulus operator.
     */
    auto min = gil::channel_traits<gil::bits8>::min_value();
    auto max = gil::channel_traits<gil::bits8>::max_value();
    auto num_channels = gil::num_channels<ColorBase>();
    ColorBase color;

    for(auto i = 0; i < num_channels; ++i) {
        auto value = static_cast<gil::bits8>(min + std::rand() % (max - min + 1));

        color[i] =
            gil::channel_convert<typename gil::channel_type<ColorBase>::type>(
                value
            );
    }

    return color;
}

} // namespace imgen

template<typename ChannelValue, typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const boost::gil::pixel<ChannelValue, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<ChannelValue, Layout> >();

    for(auto i = 0; i < num_channels; ++i) {
        os << color[i] << ((i == num_channels - 1) ? "" : ", ");
    }

    return os;
}

template<typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const boost::gil::pixel<unsigned char, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<unsigned char, Layout> >();

    for(auto i = 0; i < num_channels; ++i) {
        os << static_cast<int>(color[i]) << ((i == num_channels - 1) ? "" : ", ");
    }

    return os;
}

#endif // IMGEN_COLOR_HPP_
