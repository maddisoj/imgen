// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include "imgen/color.hpp"

#include <boost/program_options.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <format.h>

#include <cstdlib>
#include <iostream>

namespace po = boost::program_options;
namespace gil = boost::gil;

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

            auto dest = vm["dest"].as<std::string>();
            auto width = vm["width"].as<int>();
            auto height = vm["height"].as<int>();

            gil::rgb8_image_t img(width, height);
            auto color = imgen::random_color();

            std::cout << color << std::endl;

            gil::fill_pixels(gil::view(img), color);
            gil::png_write_view(dest, gil::const_view(img));
        } catch(po::error& e) {
            fmt::print("Error: {}\n{}", e.what(), desc);
        }
    }

    return 0;
}
