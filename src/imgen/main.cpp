// Fix issues with Boost GIL and libpng 1.2+
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_bytep_NULL (png_bytep)NULL

#include <boost/program_options.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <format.h>

namespace po = boost::program_options;
namespace gil = boost::gil;

int main(int argc, char** argv) {
    po::options_description desc("Options");
    po::variables_map vm;

    desc.add_options()
        ("help", "Print the usage message")
        ("width,w", po::value<int>()->required(), "The generated image's width")
        ("height,h", po::value<int>()->required(), "The generated image's height")
        ("dest,d", po::value<std::string>()->required(), "The output path for the image");

    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        fmt::print("{}", desc);
    } else {
        auto dest = vm["dest"].as<std::string>();
        auto width = vm["width"].as<int>();
        auto height = vm["height"].as<int>();

        gil::rgb8_image_t img(width, height);
        gil::rgb8_pixel_t red(255, 0, 0);

        gil::fill_pixels(gil::view(img), red);
        gil::png_write_view(dest, gil::const_view(img));
    }

    return 0;
}
