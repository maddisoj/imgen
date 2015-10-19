#ifndef IMGEN_IMGEN_HPP_
#define IMGEN_IMGEN_HPP_

#include "imgen/image.hpp"
#include "imgen/palette.hpp"
#include "imgen/pattern.hpp"

#include <Python.h>
#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <string>

namespace py = boost::python;
namespace fs = boost::filesystem;

namespace imgen {

class imgen {
    py::object main_module;
    py::dict main_nmspc;
    fs::path working_dir;
    palette_linker pal_linker;
    pattern_linker pat_linker;
    boost::shared_ptr<palette> pal;
    boost::shared_ptr<pattern> pat;

public:
    imgen(fs::path wdir);

    void set_seed(unsigned seed);
    void generate(const fs::path& dest, unsigned width, unsigned height);
    void set_palette(const std::string& name);
    void set_pattern(const std::string& name);
    std::string random_palette();
    std::string random_pattern();

private:
    static constexpr auto MODULE_DIR  = "python/";
    static constexpr auto PALETTE_DIR = "palettes/";
    static constexpr auto PATTERN_DIR = "patterns/";

    void import(const std::string& module);
    void add_to_path(const fs::path& dir);
};

} // namespace imgen

#endif // IMGEN_IMGEN_HPP_
