#include "bindings/colors.hpp"
#include "bindings/pattern.hpp"
#include "bindings/palette.hpp"
#include "imgen/color.hpp"
#include "imgen/image.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/gil/gil_all.hpp>

#include <vector>

/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    namespace py = boost::python;
    namespace gil = boost::gil;
    namespace ib = imgen::bindings;

    typedef std::vector<ib::rgb_t> color_vec_t;

    ib::def_color<ib::rgb_t>("rgb");
    ib::def_color<ib::hsl_t>("hsl");

    py::class_<color_vec_t>("ColorList")
        .def(py::vector_indexing_suite<color_vec_t>());

    py::class_<imgen::image>("Image", py::no_init)
        .def("width", &imgen::image::width)
        .def("height", &imgen::image::height);

    py::class_<imgen::context>("Context", py::no_init)
        .def("set_color", &imgen::context::set_color)
        .def("rectangle", &imgen::context::rectangle)
        .def("stroke", &imgen::context::stroke)
        .def("fill", &imgen::context::fill);

    py::class_<ib::palette_wrapper, boost::noncopyable>("Palette")
        .def_readwrite("colors", &imgen::palette::colors)
        .def("blend", py::pure_virtual(&imgen::palette::blend));

    py::class_<ib::pattern_wrapper, boost::noncopyable>("Pattern")
        .def("draw", py::pure_virtual(&imgen::pattern::draw));

    py::def("random_rgb", &imgen::random_color<ib::rgb_t>);
    py::def("random_hsl", &imgen::random_color<ib::hsl_t>);
    py::def("rgb2hsl", &ib::color_convert<ib::rgb_t, ib::hsl_t>);
    py::def("hsl2rgb", &ib::color_convert<ib::hsl_t, ib::rgb_t>);
}
