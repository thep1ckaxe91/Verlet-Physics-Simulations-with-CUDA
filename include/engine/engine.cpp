#include "engine/engine.hpp"
#include <iostream>
namespace core
{
    void init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING))
        {
            throw CoreException(SDL_GetError());
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            throw CoreException(IMG_GetError());
        }
        if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
        {
            throw CoreException(IMG_GetError());
        }

        if (TTF_Init())
        {
            throw CoreException(TTF_GetError());
        }
    }

    void mixer_init(int freq, uint16_t format, int channels, int chunk_size)
    {
        if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3)
        {
            throw CoreException(Mix_GetError());
        }
        if ((Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG) != MIX_INIT_OGG)
        {
            throw CoreException(Mix_GetError());
        }
        if ((Mix_Init(MIX_INIT_WAVPACK) & MIX_INIT_WAVPACK) != MIX_INIT_WAVPACK)
        {
            std::cerr << Mix_GetError() << " (This might be a false error raise)\n";
        }

        if (Mix_OpenAudio(freq, format, channels, chunk_size))
        {
            throw CoreException(Mix_GetError());
        }
    }

    void quit()
    {
        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
    }
}