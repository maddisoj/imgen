#include "imgen/color.hpp"
#include "imgen/palette.hpp"
#include "imgen/hsl.hpp"
#include "bindings/colors.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/gil/gil_all.hpp>

#include <vector>

namespace py = boost::python;
namespace gil = boost::gil;
namespace ib = imgen::bindings;

/** Colour Wrappers */
typedef std::vector<gil::rgb32f_pixel_t> color_vec_t;

/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    ib::def_color<gil::rgb32f_pixel_t>("rgb");
    ib::def_color<gil::hsl32f_pixel_t>("hsl");

    py::class_<color_vec_t>("ColorList")
        .def(py::vector_indexing_suite<color_vec_t>());

    py::class_<imgen::palette, boost::noncopyable>("Palette")
        .def_readwrite("colors", &imgen::palette::colors);

    py::def("random_rgb", &imgen::random_color<gil::rgb32f_pixel_t>);
    py::def("random_hsl", &imgen::random_color<gil::hsl32f_pixel_t>);
    py::def("rgb2hsl", &ib::color_convert<gil::rgb32f_pixel_t, gil::hsl32f_pixel_t>);
    py::def("hsl2rgb", &ib::color_convert<gil::hsl32f_pixel_t, gil::rgb32f_pixel_t>);
}
