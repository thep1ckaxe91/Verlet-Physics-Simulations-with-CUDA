#include"engine/engine.hpp"
#include<iostream>

struct Player
{
    Rect hitbox;
    static Rect player_hitbox_key(const Player &p)
    {
        return p.hitbox;
    }
};

int main(int argc, char **argv) {
    core::init();
    
    /*
    Everything is linking correctly
    The rest is up to you
    TODO: go for it
    */

    return 0;
}