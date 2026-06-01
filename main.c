#include <SDL3/SDL.h>
#include "logic.h"
#include <stdlib.h>
#include "ui.h"
#include <time.h>
#include "simulation.h"
#include <stdbool.h>
#define SYSTEM_SIZE 20

void free_system(System* sys) {
    if (sys == NULL) return;
    for (int i = 0; i < sys->count; i++) {
        free(sys->bodies[i]);
    }
    free(sys->bodies);
    free(sys);
}
int main(int argc, char* argv[]) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("ZXc", WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    struct pixel* pixels = malloc(HEIGHT * WIDTH * sizeof(struct pixel));
    bool running = true;
    SDL_Event event;

    // System* sys = create_random_system(SYSTEM_SIZE);
    System* sys = create_solar_system();
    // System* sys = create_random_system(100);
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        uint64_t frame_start = SDL_GetTicks();

        update_system(sys);
        draw_system(pixels, sys);
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * (sizeof(struct pixel)));

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        memset(pixels, 0, WIDTH * HEIGHT * sizeof(struct pixel));
        uint64_t frame_time = SDL_GetTicks() - frame_start;

        if (frame_time < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    free(pixels);
    free_system(sys);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}