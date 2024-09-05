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
using Timer = core::time::Timer;
int main(int argc, char **argv) {
    core::init();
    
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    core::time::Clock clock;
    
    while(true)
    {
        clock.tick();
        Event e;
        while(core::event::poll_event(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
        SDL_RenderClear(renderer);
        
    }

    /*
    Everything is linking correctly
    The rest is up to you
    TODO: go for it
    */

    return 0;
}