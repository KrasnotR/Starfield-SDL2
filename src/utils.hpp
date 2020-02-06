//
// Created by krasno on 2020-02-05.
//

#ifndef STARFIELD_SDL2_UTILS_HPP
#define STARFIELD_SDL2_UTILS_HPP


#include <SDL_render.h>

template <class T>
T map(T s, T a1, T a2, T b1, T b2) {
    return (T)(b1 + (s-a1)*(b2-b1)/(a2-a1));
}

void drawFilledCircle(SDL_Renderer *pRenderer, int centreX, int centreY, int radius) {
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    for (int x = -radius; x < radius; x++)
    {
        int height = (int)sqrt(radius * radius - x * x);

        for (int y = -height; y < height; y++)
            SDL_RenderDrawPoint(pRenderer, x + centreX, y + centreY);
    }
}


#endif //STARFIELD_SDL2_UTILS_HPP
