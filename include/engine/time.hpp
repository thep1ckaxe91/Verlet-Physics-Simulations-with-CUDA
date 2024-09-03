#ifndef TIME_HPP
#define TIME_HPP

#include "engine/event.hpp"

namespace core::time
{
    extern 

    //get time from epoch in second
    float get_times();
    //wait for given second, this sleep the program, allow other process to use cpu
    void wait(float sec);
    //wait for given second, this use the cpu for timing so it more precise, but more strain on the cpu
    void delay(float sec);
    //Set an event to appear on the event queue every given number of seconds. The first event will not appear until the amount of time has passed. event attr can be an Even object or an interger denote what event type it is
    void set_timer(Event event, float delay_sec, bool loop = false);


}

#endif