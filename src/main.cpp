#include "engine/engine.hpp"
#include "engine/hardware_accelerate.hpp"
#include <iostream>

struct Player
{
    Rect hitbox;
    static Rect player_hitbox_key(const Player &p)
    {
        return p.hitbox;
    }
};
using Timer = core::time::Timer;
int main(int argc, char **argv)
{
    core::init();
    core::mixer_init();

    std::cout << sizeof(std::string);

    /*
    Everything is linking correctly
    The rest is up to you
    TODO: go for it
    */

    return 0;
}