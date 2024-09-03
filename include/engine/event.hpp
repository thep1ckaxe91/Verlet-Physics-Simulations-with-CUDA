#ifndef EVENT_HPP
#define EVENT_HPP

#include<array>
#include"SDL2/SDL_events.h"
typedef SDL_Event Event;
namespace core::event
{
    //Poll for current event
    bool poll_event(Event *e);

    
}
#endif