#ifndef BINDINGS_PALETTE_HPP_
#define BINDINGS_PALETTE_HPP_

#include "imgen/palette.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

struct palette_wrapper : imgen::palette, py::wrapper<imgen::palette> {
    void blend()
    {
        this->get_override("blend")();
    }
};

} } // namespace imgen::bindings

#endif // BINDINGS_PALETTE_HPP_
