#ifndef WALLGEN_X_UTIL_H_
#define WALLGEN_X_UTIL_H_

#include <xcb/xcb.h>
#include <memory>

namespace wallgen {
namespace x {

// Aliases for the xcb types
typedef std::shared_ptr<xcb_connection_t> Connection;
typedef std::shared_ptr<xcb_generic_event_t> Event;
typedef const xcb_screen_t* Screen;
typedef xcb_drawable_t Drawable;

// Wraps a xcb_connection_t in a shared pointer that will correctly call
// xcb_disconnect when all the connection is no longer in use.
// TODO: Add the parameters for xcb_connect
Connection connect();

// Wraps a xcb_generic_event_t from xcb_wait_for_event in a shared_ptr that will
// correctly free itself.
Event waitForEvent(const Connection& conn);

} //namespace x
} //namespace wallgen

#endif //WALLGEN_X_UTIL_H_

