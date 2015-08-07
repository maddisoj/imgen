// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include "imgen/image.hpp"
#include "imgen/palette.hpp"
#include "imgen/pattern.hpp"

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

/**
 * Sets the python and C++ random number generator seed.
 */
void set_seed(py::dict& main_nmspc, unsigned seed)
{
    if(!main_nmspc.has_key("random")) {
        main_nmspc["random"] = py::import("random");
    }

    main_nmspc["random"].attr("seed")(seed);
    std::srand(seed);
}

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

            Py_Initialize();

            // Python Environment
            auto main_module = py::import("__main__");
            py::dict main_nmspc = py::extract<py::dict>(main_module.attr("__dict__"));

            // Directories
            auto exec_dir = fs::canonical(fs::system_complete(argv[0])).parent_path();
            auto palettes_dir = exec_dir / "palettes";
            auto patterns_dir = exec_dir / "patterns";

            // Set the seed for this generation.
            set_seed(main_nmspc, seed);

            // Linkers
            imgen::palette_linker palette_linker(palettes_dir, main_nmspc);
            imgen::pattern_linker pattern_linker(patterns_dir, main_nmspc);

            // Palette and Pattern selection
            std::string palette_name, pattern_name;

            if(vm.count("palette")) {
                palette_name = vm["palette"].as<std::string>();
            } else {
                auto palettes = palette_linker.get_names();
                palette_name = palettes[std::rand() % palettes.size()];
            }

            if(vm.count("pattern")) {
                pattern_name = vm["pattern"].as<std::string>();
            } else {
                auto patterns = pattern_linker.get_names();
                pattern_name = patterns[std::rand() % patterns.size()];
            }

            // Image
            imgen::image img(width, height);
            imgen::context ctx(img);

            // Drawing Objects
            auto palette = palette_linker.extract(palette_name);
            auto pattern = pattern_linker.extract(pattern_name);

            pattern->draw(img, ctx, *palette);

            img.write_png(dest);
            fmt::print("Seed: {}", seed);
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
