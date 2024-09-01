#include"engine/engine.hpp"
#include<iostream>

int main(int argc, char **argv) {
    core::init();
    
    Vec2 pos = {3.4,4};
    pos += Vec2(1,2.2);
    std::cout << pos.x << ' ' << pos.y << std::endl;
    pos.normalize_ip();
    std::cout << pos.length() << std::endl;

    /*
    Everything is linking correctly
    The rest is up to you
    TODO: go for it
    */

    return 0;
}