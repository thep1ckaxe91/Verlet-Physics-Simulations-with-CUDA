#ifndef TIME_HPP
#define TIME_HPP

#include "engine/event.hpp"
#include <chrono>
#include <string>
namespace core::time
{
    // get time from epoch in second
    float get_secs();
    // time since epoch in mili
    float get_ticks();
    // time since epoch in micro
    float get_micros();
    // time since epoch in nano
    float get_nanos();
    // wait for given second, this sleep the program, allow other process to use cpu
    void wait(float sec);
    // wait for given second, this use the cpu for timing so it more precise, but more strain on the cpu
    void delay(float sec);
    // Set an event to appear on the event queue every given number of seconds. The first event will not appear until the amount of time has passed. event attr can be an Even object or an interger denote what event type it is, this function will create a seperate thread to run
    void set_timer(Event event, float delay_sec, bool loop = false);

    static void event_timer(Event event, float delay_sec, bool loop);

    class Clock
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> last_tick;
        std::chrono::duration<int64_t, std::nano> dt;

    public:
        Clock();
        // update the clock, This method should be called once per frame. It will compute how many second have passed since prev call. this will guarantee return 1/framerate 
        float tick(float framerate = 0);
        // return time duration of 2 previous call to tick
        float get_dt();
        // basicly return 1/get_dt
        float get_fps();
    };
    /**
     * @brief Automatically print the time in ms that passed in the scope
     *
     */
    class Timer
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::string msg;

    public:
        Timer(std::string &&msg = "Time passed: ");
        ~Timer();
    };
}

#endif