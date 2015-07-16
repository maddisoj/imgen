#ifndef IMGEN_SURFACE_HPP_
#define IMGEN_SURFACE_HPP_

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/gil_all.hpp>
#include <cairo/cairo.h>

#include <string>
#include <exception>

namespace fs = boost::filesystem;
namespace gil = boost::gil;

namespace imgen {

// forward declaration
class context;

/**
 * Thin wrapper around cairo_surface_t which ensures the proper freeing of the
 * cairo_surface_t. Also helps hide the long ugly function names that the cairo
 * library tends to introduce.
 */
class image {
    boost::shared_ptr<cairo_surface_t> surface;

public:
    image(int width, int height);

    void write_png(const fs::path& path) const;
    int width() const;
    int height() const;
    boost::shared_ptr<cairo_surface_t> data();
};

class context {
    boost::shared_ptr<cairo_t> ctx;

public:
    context(image& img);

    void set_color(const gil::rgb32f_pixel_t& color);
    void rectangle(float x, float y, float width, float height);
    void stroke();
    void fill();
};

} // namespace imgen

#endif // IMGEN_SURFACE_HPP_
