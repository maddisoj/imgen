#ifndef BINDINGS_UTIL_HPP_
#define BINDINGS_UTIL_HPP_

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include <vector>

namespace py = boost::python;

namespace imgen { namespace bindings {

template<typename T>
inline py::list vector_to_list(const std::vector<T>& v)
{
    return py::list(py::iterator<std::vector<T> >()(v));
}

template<typename T>
inline std::vector<T> list_to_vector(const py::list& list)
{
    return std::vector<T>(py::stl_input_iterator<T>(list),
                          py::stl_input_iterator<T>());
}

} } // namespace imgen::bindings

#endif // BINDINGS_UTIL_HPP_
