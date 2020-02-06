#include <iostream>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

bool playing = true;

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

    while (playing) {
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
