#include "imgen/filter.hpp"

namespace imgen {

void nlfilter(image& img, std::size_t w, std::size_t h,
              std::function<image::pixel_t(const ublas::matrix<image::pixel_t>&)> f)
{
    auto iw = img.width();
    auto ih = img.height();
    // The number of rows above/aside the center element
    auto top = static_cast<std::size_t>(std::floor(h / 2.0));
    auto left = static_cast<std::size_t>(std::floor(w / 2.0));
    // We must store the result and set the image to it after we have processed
    // the image as subsequent regions may need to use the unchanged pixel at
    // a location we have already modified.
    ublas::matrix<image::pixel_t> result(iw, ih);

    for(decltype(iw) x = 0; x < iw; ++x) {
        for(decltype(ih) y = 0; y < ih; ++y) {
            // img.region works from the top left of the region so we must
            // offset it so that (x, y) is at the center.
            result(x, y) = f(img.region(x - left, y - top, w, h));
        }
    }

    img.set(0, 0, result);
}

void filter(image& img, const filter_t& filter)
{
    auto fw = filter.size1();
    auto fh = filter.size2();
    auto num_channels = gil::num_channels<image::pixel_t>();

    // Calculates the correlation result for each region. The correlation result
    // is calculated by multiplying the respective elements in neighbourhood and
    // filter mask and then taking the sum of those elements. This is done for
    // each channel of the pixel.
    nlfilter(img, fw, fh, [&](const ublas::matrix<image::pixel_t>& neighbourhood) {
        image::pixel_t correlation;

        for(decltype(fw) i = 0; i < fw; ++i) {
            for(decltype(fh) j = 0; j < fh; ++j) {
                const auto& src = neighbourhood(i, j);

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

        return correlation;
    });
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
