#ifndef BINDINGS_IMAGE_HPP_
#define BINDINGS_IMAGE_HPP_

#include "imgen/image.hpp"

#include <boost/python.hpp>
#include <boost/gil/gil_all.hpp>

namespace py = boost::python;
namespace gil = boost::gil;

namespace imgen { namespace bindings {

void context_set_color_channels(context& c, float r, float g, float b)
{
    c.set_color({r, g, b});
}

void context_set_color_tuple(context& c, const py::tuple& color)
{
    context_set_color_channels(c,
        py::extract<float>(color[0]),
        py::extract<float>(color[1]),
        py::extract<float>(color[2])
    );
}

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(
    context_clear_overloads, clear, 0, 1
);

} } // namespace imgen::bindings

#endif // BINGINGS_IMAGE_HPP_
