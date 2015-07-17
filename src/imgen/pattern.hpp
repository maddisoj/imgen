#ifndef IMGEN_PATTERN_HPP_
#define IMGEN_PATTERN_HPP_

#include "imgen/image.hpp"
#include "imgen/palette.hpp"
#include "imgen/linker.hpp"

namespace imgen {

struct pattern {
    virtual void draw(const image& img, context& ctx, const palette& palette) = 0;
};

struct pattern_linker : linker<pattern> {
    using linker<pattern>::linker;

    const std::string python_class() const
    {
        return "Pattern";
    }
};

} //namespace imgen

#endif // IMGEN_PATTERN_HPP_
