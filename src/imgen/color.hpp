#ifndef IMGEN_COLOR_HPP_
#define IMGEN_COLOR_HPP_

#include <boost/gil/gil_all.hpp>

#include <string>
#include <ostream>

namespace imgen {
    namespace gil = boost::gil;

    typedef gil::rgb8_pixel_t color_t;
    typedef gil::channel_type<color_t>::type channel_t;

    /** Creates a random color */
    color_t random_color();
} // namespace imgen

template<typename ChannelValue, typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const boost::gil::pixel<ChannelValue, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<ChannelValue, Layout> >();

    os << "(";
    for(auto i = 0; i < num_channels; ++i) {
        os << color[i] << ((i == num_channels - 1) ? "" : ", ");
    }
    os << ")";

    return os;
}

template<typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const boost::gil::pixel<unsigned char, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<unsigned char, Layout> >();

    os << "(";
    for(auto i = 0; i < num_channels; ++i) {
        os << static_cast<int>(color[i]) << ((i == num_channels - 1) ? "" : ", ");
    }
    os << ")";

    return os;
}

#endif // IMGEN_COLOR_HPP_
