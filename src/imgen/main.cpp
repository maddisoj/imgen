// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include "imgen/color.hpp"
#include "imgen/hsl.hpp"
#include "imgen/palette.hpp"

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
            // po::notify(vm);
            // auto dest = vm["dest"].as<std::string>();
            // auto width = vm["width"].as<int>();
            // auto height = vm["height"].as<int>();

            Py_Initialize();

            auto main_module = py::import("__main__");
            py::dict main_nmspc = py::extract<py::dict>(main_module.attr("__dict__"));
            auto exec_dir = fs::canonical(fs::system_complete(argv[0])).parent_path();
            auto palettes_dir = exec_dir / "palettes";
            imgen::palette_linker palette_linker(palettes_dir, main_nmspc);

            auto names = palette_linker.get_names();
            auto palette = palette_linker.extract(names[0]);

            gil::rgb8_image_t img(512, 100);
            auto view = gil::view(img);
            gil::fill_pixels(view, gil::rgb8_pixel_t(0, 0, 0));

            for(int x = 0; x < img.width(); ++x) {
                auto p = static_cast<float>(x) / static_cast<float>(img.width());
                auto index = static_cast<int>(std::ceil(p * 3.0f));
                auto color = palette->colors[index];

                for(int y = 0; y < img.height(); ++y) {
                    view(x, y) = color;
                }
            }

            gil::png_write_view("test.png", gil::const_view(img));
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
