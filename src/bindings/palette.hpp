#ifndef BINDINGS_PALETTE_HPP_
#define BINDINGS_PALETTE_HPP_

#include "imgen/palette.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

struct palette_wrapper : palette, py::wrapper<palette> {
    palette::color_t blend(int left, int right, double proportion) const
    {
        auto o = this->get_override("blend");

        if(o) {
            return o(left, right, proportion);
        } else {
            return palette::blend(left, right, proportion);
        }
    }

    palette::color_t lightest() const
    {
        auto o = this->get_override("lightest");

        if(o) {
            return o();
        } else {
            return palette::lightest();
        }
    }

    palette::color_t darkest() const
    {
        auto o = this->get_override("darkest");

        if(o) {
            return o();
        } else {
            return palette::darkest();
        }
    }

    palette::color_t random_color() const
    {
        auto o = this->get_override("random_color");

        if(o) {
            return o();
        } else {
            return palette::random_color();
        }
    }
};

} } // namespace imgen::bindings

#endif // BINDINGS_PALETTE_HPP_
