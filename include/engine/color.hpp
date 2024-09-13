#ifndef COLOR_HPP
#define COLOR_HPP
#include "SDL2/SDL.h"
struct Color : public SDL_Color
{
    Color();
    /**
     * @brief Construct a new Color object, alpha is range [0,255]
     * 
     * @param r 
     * @param g 
     * @param b 
     * @param a 
     */
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);


};

#endif