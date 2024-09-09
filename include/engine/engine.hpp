#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "engine/math.hpp"
#include "engine/Rect.hpp"
#include "engine/time.hpp"
#include "engine/event.hpp"
#include "engine/constant.hpp"
#include "engine/video.hpp"
#include "engine/color.hpp"
#include "engine/exception.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

namespace core
{
    void init();
    void quit();
    void mixer_init(int freq = 48000, uint16_t format = AUDIO_S16SYS, int channels = 2, int chunk_size = 2048);
}

#endif