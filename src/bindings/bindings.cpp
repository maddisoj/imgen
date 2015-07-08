#include "imgen/colour.hpp"
#include "imgen/palette.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <vector>

namespace py = boost::python;

/** Palette Wrappers */
struct palette_wrapper : imgen::palette, py::wrapper<imgen::palette> {
    imgen::colour blend(int left, int right, float proportion) {
        return this->get_override("blend")(left, right, proportion);
    }
};

/** Colour Wrappers */
typedef std::vector<imgen::colour> colour_vec_t;
typedef boost::gil::channel_type<imgen::colour>::type channel_t;

inline void colour_check_range(int index) {
    if(index < 0 || index > boost::gil::num_channels<imgen::colour>()) {
        PyErr_SetString(PyExc_IndexError, "Index out of range");
        py::throw_error_already_set();
    }
}

channel_t colour_getitem(imgen::colour& c, int index) {
    colour_check_range(index);

    return c[index];
}

void colour_setitem(imgen::colour& c, int index, channel_t value) {
    colour_check_range(index);

    c[index] = value;
}


/** Bindings */
BOOST_PYTHON_MODULE(imgen) {
    py::class_<imgen::colour>("Colour", py::init<int, int, int>())
        .def("__getitem__", &colour_getitem)
        .def("__setitem__", &colour_setitem);

    py::class_<colour_vec_t>("ColourList")
        .def(py::vector_indexing_suite<colour_vec_t>());

    py::class_<palette_wrapper, boost::noncopyable>("Palette")
        .def_readwrite("colours", &imgen::palette::colours)
        .def("blend", py::pure_virtual(&imgen::palette::blend));
}
