#ifndef IMGEN_POINT_HPP_
#define IMGEN_POINT_HPP_

#include <utility>

namespace imgen {

template<typename Coord>
struct point {
    Coord x, y;

    point(Coord x, Coord y) :
        x(std::move(x)), y(std::move(y)) {}
};

} // namespace imgen

#endif // IMGEN_POINT_HPP_
