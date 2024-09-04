#ifndef EVENT_HPP
#define EVENT_HPP

#include<array>
#include"SDL2/SDL_events.h"
typedef SDL_Event Event;
namespace core::event
{
    //Poll for current event, only in the thread that init display
    bool poll_event(Event *e);
    // post an event to the event queue
    bool post_event(Event *e);
    // wait until an event occur in the queue, if timeout is 0, it will wait indefinitely, return 1 if success
    bool wait_event(Event *e, float timeout_sec = 0);
}
#endif