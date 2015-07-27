#ifndef BINDINGS_PATH_HPP_
#define BINDINGS_PATH_HPP_

#include "imgen/path.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

struct path_wrapper : path {
    void curve_to(const py::tuple& points)
    {
        path::curve_to({
            py::extract<path::point_t>(points[0]),
            py::extract<path::point_t>(points[1]),
            py::extract<path::point_t>(points[2]),
        });
    }
};

} } // namespace imgen::bindings

#endif // BINDINGS_PATH_HPP_
