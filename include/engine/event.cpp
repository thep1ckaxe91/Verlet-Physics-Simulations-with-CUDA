#include "event.hpp"

namespace core::event
{
    bool poll_event(Event *e)
    {
        return SDL_PollEvent(e);
    }

    bool post_event(Event e)
    {
        return SDL_PushEvent(&e) == 1 ? 1 : 0;
    }
}