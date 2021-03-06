#include "bindings/colors.hpp"
#include "bindings/pattern.hpp"
#include "bindings/palette.hpp"
#include "bindings/path.hpp"
#include "bindings/image.hpp"
#include "bindings/point.hpp"
#include "imgen/color.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/gil/gil_all.hpp>

#include <vector>

/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    namespace py = boost::python;
    namespace gil = boost::gil;
    namespace ib = imgen::bindings;

    ib::def_color<ib::rgb_t>("rgb");
    ib::def_color<ib::hsl_t>("hsl");

    py::class_<imgen::image>("Image", py::no_init)
        .def("width", &imgen::image::width)
        .def("height", &imgen::image::height);

    py::class_<imgen::context>("Context", py::no_init)
        .def("set_color", &ib::context_set_color_tuple)
        .def("set_color", &ib::context_set_color_channels)
        .def("set_color", &imgen::context::set_color)
        .def("translate", &imgen::context::translate)
        .def("scale", &imgen::context::scale)
        .def("rotate", &imgen::context::rotate)
        .def("arc", &imgen::context::arc)
        .def("circle", &imgen::context::circle)
        .def("rectangle", &imgen::context::rectangle)
        .def("stroke", &imgen::context::stroke)
        .def("fill", &imgen::context::fill)
        .def("clear", &imgen::context::clear, ib::context_clear_overloads());

    py::class_<imgen::point_t>("Point", py::init<double, double>())
        .def_readwrite("x", &imgen::point_t::x)
        .def_readwrite("y", &imgen::point_t::y)
        .def("length", &imgen::point_t::length)
        .def(py::self + py::self)
        .def(py::self - py::self)
        .def(py::self * imgen::point_t::coord_t())
        .def(py::self / imgen::point_t::coord_t());

    py::def("dot_product", &imgen::dot_product<imgen::point_t::coord_t>);
    py::def("normal", &imgen::normal<imgen::point_t::coord_t>);
    py::def("distance", ib::distance_point_point);
    py::def("distance", &ib::distance_point_line);

    py::class_<imgen::path>("Path")
        .def(py::init<double>())
        .def("move_to", &imgen::path::move_to)
        .def("line_to", &imgen::path::line_to)
        .def("curve_to", &ib::path_curve_to)
        .def("set_line_width", &imgen::path::set_line_width)
        .def("fill", &imgen::path::fill, ib::path_fill_overloads())
        .def("stroke", &imgen::path::stroke, ib::path_stroke_overloads());

    py::class_<ib::palette_wrapper, boost::noncopyable>("Palette")
        .def("generate", py::pure_virtual(ib::palette_generate));

    py::class_<ib::pattern_wrapper, boost::noncopyable>("Pattern")
        .def("draw", py::pure_virtual(&imgen::pattern::draw));

    py::def("random_rgb", &imgen::random_color<ib::rgb_t>);
    py::def("random_hsl", &imgen::random_color<ib::hsl_t>);
    py::def("blend", &imgen::blend<ib::rgb_t>);
    py::def("blend", &imgen::blend<ib::hsl_t>);
    py::def("rgb2hsl", &ib::color_convert<ib::rgb_t, ib::hsl_t>);
    py::def("hsl2rgb", &ib::color_convert<ib::hsl_t, ib::rgb_t>);
}
