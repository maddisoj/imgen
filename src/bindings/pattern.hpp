#ifndef BINDINGS_PATTERNS_HPP_
#define BINDINGS_PATTERNS_HPP_

#include "imgen/pattern.hpp"

#include <boost/python.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

struct pattern_wrapper : imgen::pattern, py::wrapper<imgen::pattern> {
    void draw(const imgen::image& img, imgen::context& ctx,
              const imgen::palette& palette)
    {
        this->get_override("draw")(img, ctx, boost::ref(palette));
    }
};

} } // namespace imgen::bindings

#endif // BINDINGS_PATTERNS_HPP_
