// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include "imgen/image.hpp"
#include "imgen/palette.hpp"
#include "imgen/pattern.hpp"
#include "imgen/imgen.hpp"

#include <Python.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/python.hpp>
#include <cairo/cairo.h>
#include <format.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

namespace po  = boost::program_options;
namespace gil = boost::gil;
namespace py  = boost::python;
namespace fs  = boost::filesystem;

int main(int argc, char** argv)
{
    po::options_description desc("Options");
    po::variables_map vm;

    desc.add_options()
        ("help", "Print the usage message")
        ("width,w", po::value<int>()->required(), "The generated image's width")
        ("height,h", po::value<int>()->required(), "The generated image's height")
        ("dest,d", po::value<std::string>()->required(),
            "The output path for the image")
        ("palette", po::value<std::string>(),
            "The palette to use, if ommited a random palette is chosen.")
        ("pattern", po::value<std::string>(),
            "The pattern to use, if ommited a random pattern is chosen.")
        ("seed", po::value<unsigned>(),
            "The seed for the random number generator. If ommited the current "
            "unix time is used.");

    po::store(po::parse_command_line(argc, argv, desc), vm);

    if(vm.count("help")) {
        fmt::print("{}", desc);
    } else {
        try {
            po::notify(vm);

            auto dest = vm["dest"].as<std::string>();
            auto width = vm["width"].as<int>();
            auto height = vm["height"].as<int>();
            auto seed = vm.count("seed") ? vm["seed"].as<unsigned>()
                                         : std::time(nullptr);
            auto exec_dir = fs::canonical(fs::system_complete(argv[0])).parent_path();
            imgen::imgen prog(exec_dir);

            // Set the seed for this generation.
            prog.set_seed(seed);

            // Palette and Pattern selection
            std::string palette_name, pattern_name;

            if(vm.count("palette")) {
                palette_name = vm["palette"].as<std::string>();
            } else {
                palette_name = prog.random_palette();
            }

            if(vm.count("pattern")) {
                pattern_name = vm["pattern"].as<std::string>();
            } else {
                pattern_name = prog.random_pattern();
            }

            prog.set_palette(palette_name);
            prog.set_pattern(pattern_name);
            prog.generate(dest, width, height);

            fmt::print("Palette: {}\nPattern: {}\nSize: {}x{}\nSeed: {}",
                       palette_name, pattern_name, width, height, seed);
        } catch(const po::error& e) {
            fmt::print("Error: {}\n{}", e.what(), desc);
        } catch(const py::error_already_set& e) {
            PyErr_Print();
            py::handle_exception();
        } catch(const std::exception& e) {
            fmt::print("{}", e.what());
        }
    }

    return 0;
}
