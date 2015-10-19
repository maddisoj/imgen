#include "imgen/path.hpp"

namespace imgen {

void path::draw(context& ctx, bool close) const
{
    auto c = ctx.data().get();

    cairo_new_path(c);
    cairo_set_line_width(c, line_width);

    for(auto op : operations) {
        auto type = op.first;
        auto points = op.second;

        switch(type) {
            case MOVE_TO:
                cairo_move_to(c, points[0].x, points[0].y);
                break;

            case LINE_TO:
                cairo_line_to(c, points[0].x, points[0].y);
                break;

            case CURVE_TO:
                cairo_curve_to(c, points[0].x, points[0].y,
                                  points[1].x, points[1].y,
                                  points[2].x, points[2].y);
                break;

            default:
                throw std::logic_error(fmt::format(
                    "Unimplemented path operation: {}", type
                ));
        }
    }

    if(close) {
        cairo_close_path(c);
    }
}

void path::add_operation(operation_type op, std::vector<point_t> points)
{
    operations.push_back(operation_t(op, std::move(points)));
}

} // namespace imgen
