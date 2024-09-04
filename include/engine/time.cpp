#include "engine/time.hpp"
#include <thread>
#include "SDL2/SDL_timer.h"
namespace core::time
{
    float get_secs()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count()*1e9;
    }
    //time since epoch in mili
    float get_ticks()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count()*1e6;
    }
    //time since epoch in micro
    float get_micros()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count()*1e3;
    }
    //time since epoch in nano
    float get_nanos()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    //wait for given second, this sleep the program, allow other process to use cpu
    void wait(float sec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(sec*1000)));
    }
    //wait for given second, this use the cpu for timing so it more precise, but more strain on the cpu
    void delay(float sec)
    {
        auto start = std::chrono::high_resolution_clock::now();
        while(std::chrono::high_resolution_clock::now() < start + std::chrono::microseconds((int)(1e6*sec))){
        }
    }
    //Set an event to appear on the event queue every given number of seconds. The first event will not appear until the amount of time has passed. event attr can be an Even object or an interger denote what event type it is
    void set_timer(Event event, float delay_sec, bool loop)
    {
        
    }

    Clock::Clock(){
        
    }
}
