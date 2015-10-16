#include "imgen/filter.hpp"

namespace imgen {

void filter(image& img, const filter_t& filter)
{
    auto iw = img.width();
    auto ih = img.height();
    auto fw = filter.size1();
    auto fh = filter.size2();
    auto num_channels = gil::num_channels<image::pixel_t>();

    // The number of rows above/aside the center element
    auto top = static_cast<decltype(fh)>(std::floor(fh / 2.0));
    auto left = static_cast<decltype(fw)>(std::floor(fw / 2.0));

    ublas::matrix<image::pixel_t> result(iw, ih);

    for(decltype(iw) x = 0; x < iw; ++x) {
        for(decltype(ih) y = 0; y < ih; ++y) {
            auto neighborhood = img.region(x - left, y - top, fw, fh);
            image::pixel_t correlation;

            for(decltype(fw) i = 0; i < fw; ++i) {
                for(decltype(fh) j = 0; j < fh; ++j) {
                    const auto& src = neighborhood(i, j);

                    for(auto c = 0; c < num_channels; ++c) {
                        auto element_corr = src[c] * filter(i, j);

                        if(i == 0 && j == 0) {
                            correlation[c] = element_corr;
                        } else {
                            correlation[c] += element_corr;
                        }
                    }
                }
            }

            result(x, y) = std::move(correlation);
        }
    }

    img.set(0, 0, result);
}

filter_t gaussian(filter_t::size_type size, filter_t::value_type sigma)
{
    filter_t filter(size, size);
    auto sum = 0.0;
    auto radius = std::floor(size / 2.0);
    auto sigma2 = sigma * sigma;

    for(decltype(size) x = 0; x < size; ++x) {
        auto dx = x - radius;
        auto dx2 = dx * dx;

        for(decltype(size) y = 0; y < size; ++y) {
            auto dy = y - radius;
            auto dy2 = dy * dy;
            auto value = std::exp(-(dx2 + dy2) / (2.0 * sigma2));

            filter(x, y) = value;
            sum += value;
        }
    }

    filter /= sum;

    return filter;
}

} // namesapce imgen
