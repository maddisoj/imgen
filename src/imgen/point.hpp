#ifndef IMGEN_POINT_HPP_
#define IMGEN_POINT_HPP_

#include <array>
#include <cmath>
#include <utility>

namespace imgen {

/**
 * Simple construct for representing a point in 2D space.
 */
template<typename Coord>
struct point {
    typedef Coord coord_t;

    coord_t x, y;

    point(coord_t x, coord_t y) :
        x(std::move(x)), y(std::move(y)) {}

    coord_t length() const
    {
        return std::sqrt(x * x + y * y);
    }
};

typedef point<double> point_t;

template<typename Coord>
point<Coord> operator-(const point<Coord>& left, const point<Coord>& right)
{
    return point<Coord>(left.x - right.x, left.y - right.y);
}

template<typename Coord>
point<Coord> operator+(const point<Coord>& left, const point<Coord>& right)
{
    return point<Coord>(left.x + right.x, left.y + right.y);
}

template<typename Coord>
point<Coord> operator*(const point<Coord>& left, const Coord& factor)
{
    return point<Coord>(left.x * factor, left.y * factor);
}

template<typename Coord>
point<Coord> operator/(const point<Coord>& left, const Coord& factor)
{
    return point<Coord>(left.x / factor, left.y / factor);
}

/**
 * Calculates the dot product of two points.
 */
template<typename Coord>
Coord dot_product(const point<Coord>& a, const point<Coord>& b)
{
    return a.x * b.x + a.y * b.y;
}

/**
 * Calculates the normalized vector of a point.
 */
template<typename Coord>
point<Coord> normal(const point<Coord>& p)
{
    auto length = p.length();

    // Prevent division by zero
    if(length != 0) {
        return p / length;
    } else {
        return p;
    }
}

/**
 * Finds the euclidean distance between two points.
 *
 * The distance is calculated by Pythagoras theorem.
 */
template<typename Coord>
Coord distance(const point<Coord>& a, const point<Coord>& b)
{
    auto dx = a.x - b.x;
    auto dy = a.y - b.y;

    return std::sqrt(dx * dx + dy * dy);
}

/**
 * Finds the shortest euclidean distance between a point and a line.
 *
 * The distance is calculated by projecting the vector from the point to the
 * start of the line onto the line. A full explanation can be found here:
 * http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
 */
template<typename Coord>
Coord distance(const point<Coord>& p, const std::array<point<Coord>, 2>& line)
{
    auto r = line[0] - p;
    auto perp = normal(point<Coord>(
        line[1].y - line[0].y,
        -(line[1].x - line[0].x)
    ));

    return std::abs(dot_product(r, perp));
}

} // namespace imgen

#endif // IMGEN_POINT_HPP_
