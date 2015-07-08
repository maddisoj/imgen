#include "imgen/color.hpp"

namespace imgen {
    color_t random_color() {
        auto min = gil::channel_traits<channel_t>::min_value();
        auto max = gil::channel_traits<channel_t>::max_value();

        return color_t(min + std::rand() % (max - min),
                     min + std::rand() % (max - min),
                     min + std::rand() % (max - min));
    }
} // namespace imgen
