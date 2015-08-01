#ifndef BINDINGS_POINT_HPP_
#define BINDINGS_POINT_HPP_

#include "imgen/point.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

point_t::coord_t (*distance_point_point)(const point_t&, const point_t&)
    = &distance<point_t::coord_t>;

point_t::coord_t distance_point_line(const point_t& point, const py::tuple& line)
{
    return distance(point, {
        py::extract<point_t>(line[0]),
        py::extract<point_t>(line[1])
    });
}

} } // namespace imgen::bindings

#endif // BINDINGS_POINT_HPP_
