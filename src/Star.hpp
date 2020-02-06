//
// Created by krasno on 2020-02-05.
//

#ifndef STARFIELD_SDL2_STAR_HPP
#define STARFIELD_SDL2_STAR_HPP


#include <SDL_render.h>

class Star {
public:
    float x;
    float y;
    float z;
    float pZ;

    int* sWidth;
    int* sHeight;

public:
    Star(int* width, int* height);
    void update(double deltaTime, float speed);
    void draw(SDL_Renderer *pRenderer);
};


#endif //STARFIELD_SDL2_STAR_HPP
