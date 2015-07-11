#ifndef IMGEN_HSL_HPP_
#define IMGEN_HSL_HPP_

/**
 * The HSL implementation from the Boost GIL Contributions
 * (http://gil-contributions.googlecode.com/svn/sandbox/boost/gil/extension/toolbox/hsl.hpp)
 * doesn't correctly convert from HSL to RGB so this is my own implementation.
 *
 * You can test this by the below code:
 *
 * hsl32f_pixel_t hsl(0.33, 0.56, 0.64);
 * rgb8_pixel_t rgb;
 *
 * color_convert(hsl, rgb);
 *
 * rgb will erroneously be (163, 163, 163) when it should infact be (114, 215,
 * 112)
 *
 * The algorithms implemented here have been taken from:
 * http://axonflux.com/handy-rgb-to-hsl-and-rgb-to-hsv-color-model-c
 */

#include <boost/gil/gil_all.hpp>
#include <boost/mpl/vector_c.hpp>

#include <cstdlib>

namespace boost { namespace gil {

struct hue_t {};
struct saturation_t {};
struct lightness_t {};

typedef mpl::vector3<hue_t, saturation_t, lightness_t> hsl_t;
typedef layout<hsl_t> hsl_layout_t;

GIL_DEFINE_ALL_TYPEDEFS(32f, hsl)

namespace detail {

bits32f hue_to_rgb(bits32f p, bits32f q, bits32f t) {
    if(t < 0.0f || t > 1.0f) {
        t -= std::floor(t);
    }

    if(t < 1.0f/6.0f) {
        return p + (q - p) * 6.0f * t;
    } else if(t < 1.0f/2.0f) {
        return q;
    } else if(t < 2.0f/3.0f) {
        return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
    } else {
        return p;
    }
}

} // namespace detail

template <>
struct default_color_converter_impl<rgb_t, hsl_t> {
    template <typename P1>
    void operator()(const P1& src, hsl32f_pixel_t& dst) const {
        bits32f red = channel_convert<bits32f>(get_color(src, red_t()));
        bits32f green = channel_convert<bits32f>(get_color(src, green_t()));
        bits32f blue = channel_convert<bits32f>(get_color(src, blue_t()));
        bits32f hue, saturation, lightness;

        auto max = std::max(red, std::max(green, blue));
        auto min = std::min(red, std::min(green, blue));
        lightness = (max + min) / 2;

        if(max == min) {
            hue = 0.0f;
            saturation = 0.0f;
        } else {
            auto diff = max - min;

            if(lightness > 0.5f) {
                saturation = diff / (2 - max - min);
            } else {
                saturation = diff / (max + min);
            }

            if(red == max) {
                hue = (green - blue) / diff + (green < blue ? 6.0f : 0.0f);
            } else if(green == max) {
                hue = (blue - red) / diff + 2.0f;
            } else { // blue == max
                hue = (red - green) / diff + 4.0f;
            }

            hue /= 6.0f;
        }

        get_color(dst, hue_t()) = hue;
        get_color(dst, saturation_t()) = saturation;
        get_color(dst, lightness_t()) = lightness;
    }
};

template <>
struct default_color_converter_impl<hsl_t, rgb_t> {
    template <typename P2>
    void operator()(const hsl32f_pixel_t& src, P2& dst) const {
        bits32f hue = get_color(src, hue_t());
        bits32f saturation = get_color(src, saturation_t());
        bits32f lightness = get_color(src, lightness_t());
        bits32f red, green, blue;

        auto q = lightness < 0.5 ? lightness * (1 + saturation)
                                 : lightness + saturation - lightness * saturation;
        auto p = 2 * lightness - q;

        if(saturation == 0) {
            red = lightness;
            green = lightness;
            blue = lightness;
        } else {
            red   = detail::hue_to_rgb(p, q, hue + 1.0f/3.0f);
            green = detail::hue_to_rgb(p, q, hue);
            blue  = detail::hue_to_rgb(p, q, hue - 1.0/3.0);
        }

        get_color(dst, red_t()) = 
            channel_convert<typename color_element_type<P2, red_t>::type>(red);

        get_color(dst, green_t()) =
            channel_convert<typename color_element_type<P2, green_t>::type>(green);

        get_color(dst, blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t>::type>(blue);
    }
};

} } //namespace boost::gil

#endif // IMGEN_HSL_HPP_
