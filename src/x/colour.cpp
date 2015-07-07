#include "colour.h"

namespace wallgen {
namespace x {

Pixel getColour(const Connection& conn, ColourMap map,
                uint16_t red, uint16_t green, uint16_t blue) {
    auto reply = std::shared_ptr<xcb_alloc_color_reply_t>(
        xcb_alloc_color_reply(
            conn.get(),
            xcb_alloc_color(conn.get(), map, red, green, blue),
            NULL
        )
    );

    if(reply) {
        return reply->pixel;
    } else {
        throw std::runtime_error(fmt::format(
            "Could not allocate colour: ({}, {}, {})", red, green, blue
        ));
    }
}

} // namespace x
} // namespace wallgen
