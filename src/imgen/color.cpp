#include "imgen/color.hpp"

namespace imgen {
    color random_colour() {
        auto min = gil::channel_traits<channel>::min_value();
        auto max = gil::channel_traits<channel>::max_value();

        return color(min + std::rand() % (max - min),
                     min + std::rand() % (max - min),
                     min + std::rand() % (max - min));
    }
} // namespace imgen
