#ifndef BINDINGS_COLORS_HPP_
#define BINDINGS_COLORS_HPP_

#include <boost/python.hpp>
#include <boost/gil/gil_all.hpp>

namespace imgen { namespace bindings {
    namespace py = boost::python;
    namespace gil = boost::gil;

    namespace detail {
        template<typename Channel>
        struct base_channel_value {
            typedef Channel type;
        };

        template<typename Channel, typename MinV, typename MaxV>
        struct base_channel_value<gil::scoped_channel_value<Channel, MinV, MaxV> > {
            typedef Channel type;
        };
    }

    template<typename ColorBase>
    void color_check_range(std::size_t index) {
        if(index < 0 || index > gil::num_channels<ColorBase>()) {
            PyErr_SetString(PyExc_IndexError, "Index out of range");
            py::throw_error_already_set();
        }
    }

    template<typename ColorBase,
             typename Channel = typename detail::base_channel_value<
                typename gil::channel_type<ColorBase>::type>::type >
    Channel color_get_item(ColorBase& c, std::size_t index) {
        color_check_range<ColorBase>(index);

        return c[index];
    }

    template<typename ColorBase,
             typename Channel = typename detail::base_channel_value<
                typename gil::channel_type<ColorBase>::type>::type >
    void color_set_item(ColorBase& c, std::size_t index, Channel value) {
        color_check_range<ColorBase>(index);

        c[index] = value;
    }

    template<typename ColorBase,
             typename Channel = typename detail::base_channel_value<
                typename gil::channel_type<ColorBase>::type>::type >
    void def_color(const char* name) {
        py::class_<ColorBase>(name, py::init<Channel, Channel, Channel>())
            .def("__getitem__", &color_get_item<ColorBase, Channel>)
            .def("__setitem__", &color_set_item<ColorBase, Channel>);
    }
} } // namespace imgen::bindings

#endif // BINDINGS_COLORS_HPP_
