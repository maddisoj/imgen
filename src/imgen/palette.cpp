#include "imgen/palette.hpp"

namespace imgen {

palette::color_t palette::blend(int left, int right, double proportion) const
{
    auto left_color = colors[left];
    auto right_color = colors[right];

    if(proportion >= 1.0) {
        return right_color;
    } else if(proportion <= 0.0) {
        return left_color;
    } else {
        color_t color;

        for(auto i = 0; i < gil::num_channels<color_t>(); ++i) {
            color[i] = left_color[i] + proportion * (right_color[i] - left_color[i]);
        }

        return color;
    }
}

palette::color_t palette::lightest() const
{
    if(colors.empty()) {
        return color_t(1.0f, 1.0f, 1.0f);
    } else {
        return *std::min_element(
            colors.begin(), colors.end(),
            [](const color_t& a, const color_t& b) {
                return (lightness(a) < lightness(b));
            }
        );
    }
}

palette::color_t palette::darkest() const
{
    if(colors.empty()) {
        return color_t(0.0f, 0.0f, 0.0f);
    } else {
        return *std::max_element(
            colors.begin(), colors.end(),
            [](const color_t& a, const color_t& b) {
                return (lightness(a) < lightness(b));
            }
        );
    }

}

palette::color_t palette::random_color() const
{
    if(colors.empty()) {
        return imgen::random_color<color_t>();
    }

    return colors[std::rand() % colors.size()];
}

} // namespace imgen
