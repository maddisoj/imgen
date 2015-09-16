#ifndef IMGEN_COLOR_HPP_
#define IMGEN_COLOR_HPP_

#include "imgen/hsl.hpp"

#include <boost/gil/gil_all.hpp>
#include <format.h>

#include <string>
#include <ostream>
#include <cstdlib>

namespace gil = boost::gil;

namespace imgen {

/**
 * Generates a random color in the desired format.
 */
template<typename ColorBase>
ColorBase random_color()
{
    /**
     * Use bits8 to generate the random number so we can take advantage of
     * the modulus operator.
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

/**
 * Linearly blends the colour `left` with the colour `right`. The proportion is
 * clamped to [0, 1] with 0 being the `left` colour and 1 being the `right`
 * colour.
 */
template<typename ColorBase>
ColorBase blend(const ColorBase& left, const ColorBase& right, double proportion)
{
    if(proportion >= 1.0) {
        return right;
    } else if(proportion <= 0.0) {
        return left;
    } else {
        ColorBase color;

        for(auto i = 0; i < gil::num_channels<ColorBase>(); ++i) {
            color[i] = left[i] + proportion * (right[i] - left[i]);
        }

        return color;
    }
}

} // namespace imgen

/**
 * Overload to be able to stream pixels. Each channel is output in sequential
 * order seperated by spaces.
 */
template<typename ChannelValue, typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const gil::pixel<ChannelValue, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<ChannelValue, Layout> >();

    for(auto i = 0; i < num_channels; ++i) {
        os << color[i] << ((i == num_channels - 1) ? "" : " ");
    }

    return os;
}

/**
 * Specialized overload for pixels using unsigned chars to ensure they're output
 * as numbers. Each channel is output in sequential order seperated by spaces.
 */
template<typename Layout>
std::ostream& operator<<(std::ostream& os,
                         const gil::pixel<unsigned char, Layout>& color) {
    auto num_channels
        = boost::gil::num_channels<boost::gil::pixel<unsigned char, Layout> >();

    for(auto i = 0; i < num_channels; ++i) {
        os << static_cast<int>(color[i]) << ((i == num_channels - 1) ? "" : " ");
    }

    return os;
}

#endif // IMGEN_COLOR_HPP_
