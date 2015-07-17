#include "imgen/hsl.hpp"

namespace boost { namespace gil { namespace detail {

bits32f hue_to_rgb(bits32f p, bits32f q, bits32f t)
{
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


} } } // namespace boost::gil::detail
