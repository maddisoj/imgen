#include "imgen/image.hpp"

namespace imgen {

image::image(int width, int height) {
    surface = boost::shared_ptr<cairo_surface_t>(
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height),
        cairo_surface_destroy
    );
}

void image::write_png(const fs::path& path) const
{
    auto status = cairo_surface_write_to_png(surface.get(), path.c_str());

    if(status != CAIRO_STATUS_SUCCESS) {
        throw new std::runtime_error(cairo_status_to_string(status));
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

boost::shared_ptr<cairo_surface_t> image::data()
{
    return boost::shared_ptr<cairo_surface_t>(surface);
}

context::context(image& img) {
    ctx = boost::shared_ptr<cairo_t>(
        cairo_create(img.data().get()), cairo_destroy
    );
}

void context::set_color(const gil::rgb32f_pixel_t& color)
{
    cairo_set_source_rgb(ctx.get(), color[0], color[1], color[2]);
}

void context::rectangle(float x, float y, float width, float height)
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

} // namespace imgen
