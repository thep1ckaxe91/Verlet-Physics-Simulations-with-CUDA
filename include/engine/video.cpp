#include "engine/video.hpp"
namespace core::video
{
    Window::Window(const char *title, Vec2 size, Vec2 pos, bool fullscreen, bool fullscreen_desktop)
    {
        if (!SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "direct3d11", SDL_HINT_OVERRIDE))
        {
            printf("Set renderer driver hint failed\n");
        }
    }
}