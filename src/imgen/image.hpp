#ifndef IMGEN_SURFACE_HPP_
#define IMGEN_SURFACE_HPP_

#include "color.hpp"

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/detail/endian.hpp>
#include <cairo/cairo.h>
#include <format.h>

#include <string>
#include <exception>
#include <cmath>

namespace fs = boost::filesystem;
namespace gil = boost::gil;

namespace imgen {

/**
 * Thin wrapper around cairo_surface_t which ensures the proper freeing of the
 * cairo_surface_t. Also helps hide the long ugly function names that the cairo
 * library tends to introduce.
 */
class image {
    boost::shared_ptr<cairo_surface_t> surface;

public:
    image(int width, int height);

    bool in_bounds(int x, int y) const;
    void write_png(const fs::path& path) const;
    int width() const;
    int height() const;
    gil::rgb32f_pixel_t get(int x, int y) const;
    void set(int x, int y, const gil::rgb32f_pixel_t& pixel);

    boost::shared_ptr<cairo_surface_t> data();

private:
    int index_for(int x, int y) const;
};

class context {
    image& img;
    boost::shared_ptr<cairo_t> ctx;

public:
    context(image& img);

    void set_color(const gil::rgb32f_pixel_t& color);

    // Transformation Functions
    void translate(double x, double y);
    void scale(double x, double y);
    void rotate(double angle);

    // Drawing Functions
    void arc(double x, double y, double radius, double start, double end);
    void circle(double x, double y, double radius);
    void rectangle(double x, double y, double width, double height);
    void stroke();
    void fill();
    void clear(const gil::rgb32f_pixel_t& color = {0, 0, 0});

    boost::shared_ptr<cairo_t> data();
};

} // namespace imgen

#endif // IMGEN_SURFACE_HPP_
