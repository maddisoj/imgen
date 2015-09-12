#ifndef BINDINGS_PALETTE_HPP_
#define BINDINGS_PALETTE_HPP_

#include "imgen/palette.hpp"
#include "bindings/util.hpp"

#include <boost/python.hpp>

#include <vector>

namespace py = boost::python;

namespace imgen { namespace bindings {

struct palette_wrapper : palette, py::wrapper<palette> {
    using palette::color_t;

    std::vector<color_t> generate()
    {
        return list_to_vector<color_t>(generate(py::dict{}));
    }

    std::vector<color_t> generate(int amount)
    {
        py::dict kwargs;

        kwargs["exactly"] = amount;

        return list_to_vector<color_t>(generate(kwargs));
    }

    std::vector<color_t> generate(int min, int max)
    {
        py::dict kwargs;

        kwargs["at_least"] = min;
        kwargs["at_most"] = max;

        return list_to_vector<color_t>(generate(kwargs));
    }

    py::list generate(py::dict kwargs)
    {
        return this->get_override("generate")(**kwargs);
    }
};

py::list (palette_wrapper::*palette_generate)(py::dict)
    = &palette_wrapper::generate;

} } // namespace imgen::bindings

#endif // BINDINGS_PALETTE_HPP_
