#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <emscripten.h>
#include <stdio.h>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Main loop function called by emscripten
void main_loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            emscripten_cancel_main_loop();
            return;
        }
    }

    // Clear with a dark background
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    // Draw a colored rectangle
    SDL_FRect rect = {100.0f, 100.0f, 200.0f, 150.0f};
    SDL_SetRenderDrawColor(renderer, 65, 105, 225, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Draw a border
    SDL_FRect border = {95.0f, 95.0f, 210.0f, 160.0f};
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderRect(renderer, &border);

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    printf("Hello from Emscripten with SDL3!\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Emscripten SDL3 Demo", 640, 480, 0);
    if (!window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return 1;
    }

    printf("SDL3 initialized successfully!\n");
    printf("Window: 640x480\n");

    emscripten_set_main_loop(main_loop, 0, 1);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
