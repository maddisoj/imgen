#include "imgen/color.hpp"
#include "imgen/palette.hpp"
#include "bindings/colors.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/toolbox/hsl.hpp>

#include <vector>

namespace py = boost::python;
namespace gil = boost::gil;
namespace ib = imgen::bindings;

/** Palette Wrappers */
struct palette_wrapper : imgen::palette, py::wrapper<imgen::palette> {
    imgen::color_t blend(int left, int right, float proportion) {
        return this->get_override("blend")(left, right, proportion);
    }
};

/** Colour Wrappers */
typedef std::vector<imgen::color_t> color_vec_t;

/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    ib::def_color<gil::rgb8_pixel_t>("rgb");
    ib::def_color<gil::hsl32f_pixel_t>("hsl");

    py::class_<color_vec_t>("ColorList")
        .def(py::vector_indexing_suite<color_vec_t>());

    py::class_<palette_wrapper, boost::noncopyable>("Palette")
        .def_readwrite("colors", &imgen::palette::colors)
        .def("blend", py::pure_virtual(&imgen::palette::blend));

    py::def("random_color", &imgen::random_color);
    py::def("rgb2hsl", &ib::color_convert<gil::rgb8_pixel_t, gil::hsl32f_pixel_t>);
    py::def("hsl2rgb", &ib::color_convert<gil::hsl32f_pixel_t, gil::rgb8_pixel_t>);
}
