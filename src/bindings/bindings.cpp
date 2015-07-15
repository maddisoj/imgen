#include "bindings/colors.hpp"
#include "imgen/color.hpp"
#include "imgen/palette.hpp"
#include "imgen/pattern.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/gil/gil_all.hpp>
#include <pycairo/py3cairo.h>

#include <vector>

/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    namespace py = boost::python;
    namespace gil = boost::gil;
    namespace ib = imgen::bindings;

    import_cairo();

    typedef std::vector<ib::rgb_t> color_vec_t;

    ib::def_color<ib::rgb_t>("rgb");
    ib::def_color<ib::hsl_t>("hsl");

    py::class_<color_vec_t>("ColorList")
        .def(py::vector_indexing_suite<color_vec_t>());

    py::class_<imgen::palette, boost::noncopyable>("Palette")
        .def_readwrite("colors", &imgen::palette::colors);

    py::def("random_rgb", &imgen::random_color<ib::rgb_t>);
    py::def("random_hsl", &imgen::random_color<ib::hsl_t>);
    py::def("rgb2hsl", &ib::color_convert<ib::rgb_t, ib::hsl_t>);
    py::def("hsl2rgb", &ib::color_convert<ib::hsl_t, ib::rgb_t>);
}
