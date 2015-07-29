#ifndef BINDINGS_IMAGE_HPP_
#define BINDINGS_IMAGE_HPP_

#include "imgen/image.hpp"

#include <boost/python.hpp>
#include <boost/gil/gil_all.hpp>

namespace py = boost::python;

namespace imgen { namespace bindings {

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(
    context_clear_overloads, clear, 0, 1
);

} } // namespace imgen::bindings

#endif // BINGINGS_IMAGE_HPP_
