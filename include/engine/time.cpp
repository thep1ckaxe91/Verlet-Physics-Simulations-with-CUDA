#include "engine/time.hpp"
#include <thread>
#include "SDL2/SDL_timer.h"
#include <iostream>
#include <iomanip>
namespace core::time
{
    float get_secs()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count() * 1e9;
    }
    // time since epoch in mili
    float get_ticks()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count() * 1e6;
    }
    // time since epoch in micro
    float get_micros()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count() * 1e3;
    }
    // time since epoch in nano
    float get_nanos()
    {
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    // wait for given second, this sleep the program, allow other process to use cpu
    void wait(float sec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(sec * 1000)));
    }
    // wait for given second, this use the cpu for timing so it more precise, but more strain on the cpu
    void delay(float sec)
    {
        auto start = std::chrono::high_resolution_clock::now();
        long long micro = (long long)(1e6 * sec);
        while (std::chrono::high_resolution_clock::now() < start + std::chrono::microseconds(micro))
        {
        }
    }
    // Set an event to appear on the event queue every given number of seconds. The first event will not appear until the amount of time has passed. event attr can be an Even object or an interger denote what event type it is
    void set_timer(Event event, float delay_sec, bool loop)
    {
        std::thread t(event_timer, event, delay_sec, loop);
        t.detach();
    }

    static void event_timer(Event event, float delay_sec, bool loop)
    {
        int mili = delay_sec * 1000;
        do
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(mili));
            core::event::post_event(&event);
        } while (loop);
    }

    Clock::Clock()
    {
        last_tick = std::chrono::high_resolution_clock::now();
    }

    float Clock::tick(float framerate)
    {
        if (framerate)
        {
            float time_per_frame = 1 / framerate;
            auto now = std::chrono::high_resolution_clock::now();
            dt = now - last_tick;
            wait(time_per_frame - dt.count() / 1e9);
            last_tick = now;
            return time_per_frame;
        }
        else
        {
            auto now = std::chrono::high_resolution_clock::now();
            dt = now - last_tick;
            float dur = dt.count() / 1e9;
            return dur;
        }
    }

    float Clock::get_dt()
    {
        return dt.count() / 1e9;
    }

    float Clock::get_fps()
    {
        return 1e9 / dt.count();
    }

    Timer::Timer(std::string &&msg) : msg((std::string &&)msg)
    {
        start = std::chrono::high_resolution_clock::now();
    }
    Timer::~Timer()
    {
        auto dur = std::chrono::high_resolution_clock::now() - start;
        printf_s("%s%.3lf%s\n", msg.c_str(), dur.count() / (dur.count() > 1e6 ? 1e9 : 1e6), (dur.count() > 1e6 ? "s" : "ms"));
    }

}
