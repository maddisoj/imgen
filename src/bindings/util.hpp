#ifndef BINDINGS_UTIL_HPP_
#define BINDINGS_UTIL_HPP_

#include <string>
#include <sstream>

namespace imgen { namespace bindings {

template<class C>
inline std::string print_wrapper(const C& obj)
{
    std::ostringstream os;

    os << obj;

    return os.str();
}

} } // namespace imgen::bindings

#endif // BINDINGS_UTIL_HPP_
