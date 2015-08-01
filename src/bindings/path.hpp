#ifndef BINDINGS_PATH_HPP_
#define BINDINGS_PATH_HPP_

#include "imgen/path.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

void path_curve_to(path& p, const py::tuple& points)
{
    p.curve_to({
        py::extract<point_t>(points[0]),
        py::extract<point_t>(points[1]),
        py::extract<point_t>(points[2]),
    });
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(
    path_fill_overloads, fill, 1, 2
);

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(
    path_stroke_overloads, stroke, 1, 2
);

} } // namespace imgen::bindings

#endif // BINDINGS_PATH_HPP_
