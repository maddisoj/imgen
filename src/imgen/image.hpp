#ifndef IMGEN_SURFACE_HPP_
#define IMGEN_SURFACE_HPP_

#include "color.hpp"

#include <boost/detail/endian.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <cairo/cairo.h>
#include <format.h>

#include <string>
#include <exception>
#include <cmath>

namespace fs = boost::filesystem;
namespace gil = boost::gil;

namespace imgen {

/**
 * Wrapper around cairo_surface_t which ensures the proper freeing of the
 * cairo_surface_t. Also helps hide the long ugly function names that the cairo
 * library tends to introduce.
 */
class image {
    /**
     * Smart pointer to the underlying cairo handle.
     */
    boost::shared_ptr<cairo_surface_t> surface;

public:
    /**
     * Create an ARGB image with dimensions width x height.
     */
    image(int width, int height);

    /**
     * Determines whether the given coordinates are contained within the
     * boundaries of the image. The top left of the image is (0, 0)
     */
    bool in_bounds(int x, int y) const;

    /**
     * Writes the image to a path in PNG format.
     */
    void write_png(const fs::path& path) const;

    /**
     * Returns the width of this image.
     */
    int width() const;

    /**
     * Returns the height of this image.
     */
    int height() const;

    /**
     * Returns the pixel value at the specified x and y coordinates.
     *
     * Throws std::out_of_range if the given coordinates are out of the image
     * boundaries.
     */
    gil::rgb32f_pixel_t get(int x, int y) const;

    /**
     * Set a pixel to a value.
     *
     * Throws std::out_of_range if the given coordinates are out of the image
     * boundaries.
     */
    void set(int x, int y, const gil::rgb32f_pixel_t& pixel);

    /**
     * Returns a smart pointer to the underlying cairo handle.
     */
    boost::shared_ptr<cairo_surface_t> data();

private:
    /**
     * Calculates the index of the pixel at coordinates (x, y).
     */
    int index_for(int x, int y) const;
};

/**
 * Provides drawing methods for an image.
 */
class context {
    /**
     * Reference to the image that this context is for.
     */
    image& img;

    /**
     * Smart pointer to the underlying cairo handle.
     */
    boost::shared_ptr<cairo_t> ctx;

public:
    context(image& img);

    /**
     * Sets the color that any subsequent operations will be in.
     */
    void set_color(const gil::rgb32f_pixel_t& color);

    // Transformation Functions
    void translate(double x, double y);
    void scale(double x, double y);
    void rotate(double angle);

    // Drawing Functions
    void arc(double x, double y, double radius, double start, double end);
    void circle(double x, double y, double radius);
    void rectangle(double x, double y, double width, double height);

    /**
     * Strokes the current path.
     */
    void stroke();

    /**
     * Fills the current path.
     */
    void fill();

    /**
     * Sets the entire image to a color, if no color is provided then black is
     * used.
     */
    void clear(const gil::rgb32f_pixel_t& color = {0, 0, 0});

    /**
     * Return a smart pointer to the underlying cairo handle.
     */
    boost::shared_ptr<cairo_t> data();
};

} // namespace imgen

#endif // IMGEN_SURFACE_HPP_
