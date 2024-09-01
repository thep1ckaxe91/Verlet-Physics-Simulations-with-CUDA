#include"engine/engine.hpp"
#include<iostream>

int main(int argc, char **argv) {
    core::init();
    
    Vec2 pos = {3.4,4};
    pos += Vec2(1,2.2);
    std::cout << pos.x << ' ' << pos.y << std::endl;
    pos.normalize_ip();
    std::cout << pos.length() << std::endl;
    Vec2 p(pos);
    std::cout << p << std::endl;

    Vec3 a(1,0,0);
    Vec3 b(0,1,0);
    std::cout << Vec3::unit_x.angle_to(Vec3::unit_y) << '\n';

    a.rotate_x_ip(30);
    std::cout << a << '\n';

    Rect 
    /*
    Everything is linking correctly
    The rest is up to you
    TODO: go for it
    */

    return 0;
}