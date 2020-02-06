#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Star.hpp"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

bool playing = true;

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

std::vector<Star*> stars;

void update(SDL_Event& pEvent, SDL_Window& pWindow, SDL_Renderer *pRenderer);
void processEvents(SDL_Event& pEvent, SDL_Window& pWindow);
void controls(SDL_Renderer *pRenderer);

int main() {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

#ifdef SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
#endif

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Starfield in SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    for (int i = 0; i < 800; i++) {
        stars.push_back(new Star(&SCREEN_WIDTH, &SCREEN_HEIGHT));
    }

    SDL_Rect* r = new SDL_Rect();
    SDL_RenderGetViewport(renderer, r);
    std::cout << r->x << "|" <<  r->y << "|" << r->w << "|" << r->h << std::endl;
    r->x = r->w / 2;
    r->y = r->h / 2;
    //SDL_RenderSetViewport(renderer, r);
    SDL_RenderGetViewport(renderer, r);
    std::cout << r->x << "|" <<  r->y << "|" << r->w << "|" << r->h << std::endl;

    while (playing) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = ((double)(NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

        update(event, *window, renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

void update(SDL_Event& pEvent, SDL_Window& pWindow, SDL_Renderer *pRenderer) {
    processEvents(pEvent, pWindow);
    controls(pRenderer);

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    for (auto & star : stars) {
        star->update(deltaTime, 100);
        star->draw(pRenderer);
    }
}

void processEvents(SDL_Event& pEvent, SDL_Window& pWindow) {
    // Iterates through every event in the queue until there are none left to process
    while (SDL_PollEvent(&pEvent) != 0) {
        SDL_PumpEvents();

        // If the close button on the window is pressed we change the playing status to false
        if (pEvent.type == SDL_QUIT)
            playing = false;
    }
}

void controls(SDL_Renderer *pRenderer) {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE]) {
        playing = false;
    }
}
