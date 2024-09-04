#include "event.hpp"

namespace core::event
{
    bool poll_event(Event *e)
    {
        return SDL_PollEvent(e);
    }

    bool post_event(Event *e)
    {
        return SDL_PushEvent(e) == 1 ? 1 : 0;
    }

    bool wait_event(Event *e, float timeout_sec)
    {
        if (timeout_sec != 0.f)
            return SDL_WaitEventTimeout(e, timeout_sec * 1000);
        return SDL_WaitEvent(e);
    }
}