// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include "imgen/color.hpp"
#include "imgen/hsl.hpp"

#include <Python.h>
#include <boost/filesystem.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/program_options.hpp>
#include <boost/python.hpp>
#include <format.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

namespace po  = boost::program_options;
namespace gil = boost::gil;
namespace py  = boost::python;
namespace fs  = boost::filesystem;

int main(int argc, char** argv) {
    std::srand(std::time(0));

    po::options_description desc("Options");
    po::variables_map vm;

    desc.add_options()
        ("help", "Print the usage message")
        ("width,w", po::value<int>()->required(), "The generated image's width")
        ("height,h", po::value<int>()->required(), "The generated image's height")
        ("dest,d", po::value<std::string>()->required(), "The output path for the image");

    po::store(po::parse_command_line(argc, argv, desc), vm);

    if(vm.count("help")) {
        fmt::print("{}", desc);
    } else {
        try {
            po::notify(vm);
            Py_Initialize();

            auto dest = vm["dest"].as<std::string>();
            auto width = vm["width"].as<int>();
            auto height = vm["height"].as<int>();
            auto main_module = py::import("__main__");
            auto main_nmspc = main_module.attr("__dict__");
            std::vector<fs::path> palettes;
            fs::path exec_dir = fs::canonical(fs::system_complete(argv[0])).parent_path();
            fs::path palettes_dir = exec_dir / "palettes";

            main_nmspc["sys"] = py::import("sys");
            main_nmspc["sys"].attr("path").attr("append")(palettes_dir.string());

            std::for_each(
                fs::directory_iterator(palettes_dir), fs::directory_iterator(),
                [&palettes](const fs::directory_entry& entry) {
                    if(fs::is_regular_file(entry) && entry.path().extension() == ".py") {
                        palettes.push_back(entry);
                    }
                }
            );

            std::copy(palettes.begin(), palettes.end(),
                      std::ostream_iterator<fs::path>(std::cout, "\n"));
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
