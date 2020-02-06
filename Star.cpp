//
// Created by krasno on 2020-02-05.
//

#include <effolkronium/random.hpp>
#include "Star.hpp"
#include "utils.hpp"

using Random = effolkronium::random_static;

Star::Star(int* width, int* height) {
    x = Random::get(-*width / 2, *width / 2);
    y = Random::get(-*height / 2, *height / 2);
    z = Random::get(0, *width / 2);

    pZ = z;

    sWidth = width;
    sHeight = height;
}

void Star::update(double deltaTime, float speed) {
    z = z - speed * (float)deltaTime;

    if (z < 1) {
        x = Random::get(-*sWidth / 2, *sWidth / 2);
        y = Random::get(-*sHeight / 2, *sHeight / 2);
        z = (float)*sWidth / 2;
        pZ = z;
    }
}

void Star::draw(SDL_Renderer *pRenderer) {
    float sX = map((float) x / z, 0.0f, 1.0f, 0.0f, (float) *sWidth / 2);
    float sY = map((float) y / z, 0.0f, 1.0f, 0.0f, (float) *sHeight / 2);

    float r = map((float)z, 0.0f, (float)*sWidth / 2.0f, 8.0f, 0.0f);

    drawFilledCircle(pRenderer, (int)sX, (int)sY, (int)r);

    float px = map((float)x / pZ, 0.0f, 1.0f, 0.0f, (float)*sWidth/2);
    float py = map((float)y / pZ,0.0f, 1.0f, 0.0f, (float)*sHeight/2);

    pZ = z;

    SDL_RenderDrawLine(pRenderer, (int)px, (int)py, (int)sX, (int)sY);
    //SDL_RenderDrawLine(pRenderer, (int)px, (int)py, (int)(sX + r), (int)(sY + r));
    //SDL_RenderDrawLine(pRenderer, (int)px, (int)py, (int)(sX - r), (int)(sY - r));
}
