#ifndef VIDEO_HPP
#define VIDEO_HPP
#include "engine/math.hpp"
#include "engine/color.hpp"
#include "engine/rect.hpp"
#include "SDL2/SDL.h"

#include <string>

typedef SDL_BlendMode BlendMode;
typedef SDL_TextureAccess TextureAccess;
namespace core::video
{
    class Renderer
    {
    private:
        SDL_Renderer *renderer;
        BlendMode draw_blend_mode;
        Color draw_color;
        Vec2 logical_size;
        Vec2 scale;
        //leave nullptr to renderer to acsociated
        SDL_Texture* target;


    public:
        Renderer();
        Renderer(const Window& window, int index = -1, int accelerated=-1, bool vsync=false, bool target_texture=false);
        Renderer(const Renderer& other);
        Renderer(Renderer&& other);

        Renderer &operator=(const Renderer& other);
        Renderer &operator=(Renderer&& other);


    };

    class Image
    {
    private:
        Texture texture;
        float angle;
        Vec2 origin;
        bool flip_x;
        bool flip_y;
        Color color;
        float alpha;
        BlendMode blend_mode;

    public:
        Image();
        Image(Texture &&texture, Rect srcrect = {});
        Image(const Texture &texture, Rect srcrect = {});
        Image(Image &&img);
        Image(const Image &other);

        Image &operator=(const Image &other);
        Image &operator=(Image &&other);

        Rect get_rect() const;

        void draw(Rect srcrect = {}, Rect dstrect = {});
        float get_angle() const;
        void set_angle();
        Vec2 get_origin() const;
        void set_origin(Vec2 orig);
        void set_flip_x(bool enable = false);
        void set_flip_y(bool enable = false);
        Color get_color() const;
        void set_color(Color color);
        /**
         * @brief Get the alpha of the image, range from [0,1]
         *
         * @return float
         */
        float get_alpha() const;
        /**
         * @brief Get the alpha of the image, range from [0,1]
         *
         */
        void set_alpha(float value);
        BlendMode get_blend_mode() const;
        void set_blend_mode(BlendMode bm);
        /**
         * @brief Get the texture reference that the image object holding
         * 
         * @return Texture& 
         */
        Texture &get_texture() const;
        void set_texture(const Texture& other);
        void set_texture(Texture&& other);

        Rect get_srcrect() const;
        void set_srcrect(Rect srcrect);
    };

    class Texture
    {
    private:
        // additional color multiplied into the render copy op
        Color color;
        SDL_Texture *texture;
        Renderer &renderer;
        uint32_t width, height;
        uint32_t alpha;
        BlendMode blend_mode;

    public:
        Texture();
        Texture(const Renderer &renderer, Vec2 size, bool static_type = false, bool streaming_type = false, bool target_type = false);
        Texture(Texture &&texture);
        Texture(const Texture &texture);

        Texture &operator=(const Texture &other);
        Texture &operator=(Texture &&other);

        void draw(Rect srcrect = {}, Rect dstrect = {}, float angle_deg = 0, Vec2 origin = {0, 0}, bool flip_x = false, bool flip_y = false) const;
        int get_width() const;
        int get_height() const;
        BlendMode get_blend_mode() const;
        void set_blend_mode(BlendMode blend_mode);
        Color get_color() const;
        void set_color(Color color);

        // get the rect area of the texture
        Rect get_rect() const;
        Vec2 get_size() const;
    };
    // Wrapper for window in SDL2
    class Window
    {
    private:
        SDL_Window *window;
        Vec2 position;
        Vec2 size;
        std::string title;
        float opacity;
        bool grab;
        bool resizable;

    public:
        /**
         * @brief Construct a new Window object
         *
         * @param title
         * @param size
         * @param pos if leave as -1,-1 it will consider as WINDOWPOS_CENTERED
         * @param fullscreen
         * @param fullscreen_desktop
         */
        Window();
        Window(const char *title = "thep1ckaxe's engine window", Vec2 size = {800, 600}, Vec2 pos = {-1, -1}, bool fullscreen = false, bool fullscreen_desktop = false);
        Window(Window &&window);

        Window &operator=(const Window &other);
        Window &operator=(Window &&other);

        void set_grab(bool enable);
        bool get_grab() const;
        /**
         * @brief make the window not fullscreen (exit fullscreen)
         *
         */
        void set_windowed();
        /**
         * @brief Set the window to be full screen
         *
         * @param desktop true if need the fake fullscreen
         */
        void set_fullscreen(bool desktop = false);
        void set_title(std::string &&title);
        void set_title(const char *title);
        std::string &get_title();
        /**
         * @brief Deinit the window
         *
         */
        void destroy();
        void hide();
        void show();
        void restore();
        void maximize();
        void minimize();
        void set_resizable(bool enable);
        bool get_resizable() const;
        void set_borderless(bool enable);
        bool get_borderless() const;
        void set_icon(Texture &&t);
        void set_icon(const Texture &t);
        Vec2 get_size() const;
        /**
         * @brief Get the position of the window currently on the screen
         * @return Vec2 represent the position of the window
         */
        Vec2 get_position() const;
        void set_position(Vec2 pos);
        float get_opacity() const;
        /**
         * @brief set opacity of the window, value range from [0-1]
         *
         */
        void set_opacity(float value);
    };
}

#endif