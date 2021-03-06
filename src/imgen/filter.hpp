#ifndef IMGEN_FILTER_HPP_
#define IMGEN_FILTER_HPP_

#include "imgen/image.hpp"

#include <boost/gil/gil_all.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <format.h>

#include <functional>

namespace gil = boost::gil;
namespace ublas = boost::numeric::ublas;

namespace imgen {

/**
 * The filter type, for now this will just be a matrix of floats.
 *
 * TODO: look into using the pixel channel type? could have side effects if
 * channel type is scoped?
 */
typedef ublas::matrix<float> filter_t;

/**
 * Apply a function to each region of an image using a sliding neighbourhood.
 * This can be slow on large images. The neighbourhood is padded with 0s.
 *
 * img - the image to apply the function to
 * w - the width of the region
 * h - the height of the region
 * f - the function to apply to each region
 */
void nlfilter(image& img, std::size_t w, std::size_t h,
              std::function<image::pixel_t(const ublas::matrix<image::pixel_t>&)> f);

/**
 * Applies a filter to an image using sliding neighbourhood correlation. This
 * can be slow on large images. The neighbourhood is padded with 0s.
 *
 * TODO: Give a way to define the padding element.
 */
void filter(image& img, const filter_t& filter);

/**
 * Produces a square gaussian filter mask. The mask is calcualted using:
 *
 * g(x, y) = e ^ (-(x^2 + y^2) / (2 * σ^2))
 *
 * Where the center element of the matrix is the origin. The mask is then
 * normalized. σ defaults to 0.5.
 */
filter_t gaussian(filter_t::size_type size, filter_t::value_type sigma = 0.5);

} // namespace imgen

#endif // IMGEN_FILTER_HPP_
