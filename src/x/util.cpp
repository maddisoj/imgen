#include "util.h"

namespace wallgen {
namespace x {

Connection connect() {
    return std::shared_ptr<xcb_connection_t>(
        xcb_connect(NULL, NULL),
        xcb_disconnect
    );
}

Event waitForEvent(const Connection& conn) {
    return std::shared_ptr<xcb_generic_event_t>(
        xcb_wait_for_event(conn.get()),
        free
    );
}

} //namespace x
} //namespace wallgen
