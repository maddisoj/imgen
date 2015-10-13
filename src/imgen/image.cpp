#include "imgen/image.hpp"

namespace imgen {

image::image(int width, int height) {
    surface = boost::shared_ptr<cairo_surface_t>(
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height),
        cairo_surface_destroy
    );
}

bool image::in_bounds(int x, int y) const
{
    return (x > 0 && x < width() && y > 0 && y < height());
}

void image::write_png(const fs::path& path) const
{
    auto status = cairo_surface_write_to_png(surface.get(), path.c_str());

    if(status != CAIRO_STATUS_SUCCESS) {
        throw std::runtime_error(cairo_status_to_string(status));
    }
}

int image::width() const
{
    return cairo_image_surface_get_width(surface.get());
}

int image::height() const
{
    return cairo_image_surface_get_height(surface.get());
}

image::pixel_t image::get(int x, int y) const
{
    if(!in_bounds(x, y)) {
        throw std::out_of_range("image::get");
    }

    cairo_surface_flush(surface.get());

    auto format = cairo_image_surface_get_format(surface.get());

    if(format != CAIRO_FORMAT_ARGB32 && format != CAIRO_FORMAT_RGB24) {
        throw std::logic_error("image::get only supports ARGB32 and RGB24");
    }

    return read_pixel(x, y);
}

void image::set(int x, int y, const pixel_t& pixel)
{
    if(!in_bounds(x, y)) {
        throw std::out_of_range("image::set");
    }

    auto format = cairo_image_surface_get_format(surface.get());

    if(format != CAIRO_FORMAT_ARGB32 && format != CAIRO_FORMAT_RGB24) {
        throw std::logic_error("image::set only supports ARGB32 and RGB24");
    }

    write_pixel(x, y, pixel);
    cairo_surface_mark_dirty_rectangle(surface.get(), x, y, 1, 1);
}

int image::index_for(int x, int y) const
{
    auto stride = cairo_image_surface_get_stride(surface.get());

    // Each row contains `stride` elements and each pixel is 4 elements wide.
    return y * stride + (x * 4);
}

boost::shared_ptr<cairo_surface_t> image::data()
{
    return boost::shared_ptr<cairo_surface_t>(surface);
}

image::pixel_t image::read_pixel(int x, int y) const
{
    auto pixels = cairo_image_surface_get_data(surface.get());
    auto index = index_for(x, y);

    // Depending on the endianess of the machine the pixel's channel order can
    // be reversed. This ensures the channels use the correct index.
#ifdef BOOST_BIG_ENDIAN
    gil::bits8 r = pixels[index + 1];
    gil::bits8 g = pixels[index + 2];
    gil::bits8 b = pixels[index + 3];
#else
    gil::bits8 r = pixels[index + 2];
    gil::bits8 g = pixels[index + 1];
    gil::bits8 b = pixels[index];
#endif

    return pixel_t{
        gil::channel_convert<channel_t>(r),
        gil::channel_convert<channel_t>(g),
        gil::channel_convert<channel_t>(b)
    };
}

void image::write_pixel(int x, int y, const pixel_t& pixel)
{
    auto pixels = cairo_image_surface_get_data(surface.get());
    auto index = index_for(x, y);
    auto r = gil::channel_convert<gil::bits8>(gil::get_color(pixel, gil::red_t()));
    auto g = gil::channel_convert<gil::bits8>(gil::get_color(pixel, gil::green_t()));
    auto b = gil::channel_convert<gil::bits8>(gil::get_color(pixel, gil::blue_t()));

    // Depending on the endianess of the machine the pixel's channel order can
    // be reversed. This ensures the channels use the correct index.
#ifdef BOOST_BIG_ENDIAN
    pixels[index] = 0xFF;
    pixels[index + 1] = r;
    pixels[index + 2] = g;
    pixels[index + 3] = b;
#else
    pixels[index + 3] = 0xFF;
    pixels[index + 2] = r;
    pixels[index + 1] = g;
    pixels[index] = b;
#endif
}

context::context(image& img) : img(img)
{
    ctx = boost::shared_ptr<cairo_t>(
        cairo_create(img.data().get()), cairo_destroy
    );
}

void context::translate(double x, double y)
{
    cairo_translate(ctx.get(), x, y);
}

void context::scale(double x, double y)
{
    cairo_scale(ctx.get(), x, y);
}

void context::rotate(double angle)
{
    cairo_rotate(ctx.get(), angle);
}

void context::set_color(const image::pixel_t& color)
{
    cairo_set_source_rgb(
        ctx.get(),
        gil::get_color(color, gil::red_t()),
        gil::get_color(color, gil::green_t()),
        gil::get_color(color, gil::blue_t())
    );
}

void context::arc(double x, double y, double radius, double start, double end)
{
    cairo_arc(ctx.get(), x, y, radius, start, end);
}

void context::circle(double x, double y, double radius)
{
    arc(x, y, radius, 0, 2 * M_PI);
}

void context::rectangle(double x, double y, double width, double height)
{
    cairo_rectangle(ctx.get(), x, y, width, height);
}

void context::stroke()
{
    cairo_stroke(ctx.get());
}

void context::fill()
{
    cairo_fill(ctx.get());
}

void context::clear(const image::pixel_t& color)
{
    set_color(color);
    rectangle(0, 0, img.width(), img.height());
    fill();
}

boost::shared_ptr<cairo_t> context::data()
{
    return boost::shared_ptr<cairo_t>(ctx);
}

} // namespace imgen
