#include "engine/engine.hpp"

void core::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw "Cannot init SDL";
    }
}
