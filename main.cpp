#include <iostream>
#include <SDL.h>

#include "EngineRenderService.h"

// Must be main method with args otherwise SDL won't work
int main(int argc, char* argv[]) {
    std::cout << "Starting" << std::endl;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("C++ Game Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        SDL_WINDOW_RESIZABLE
    );

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    // Don't move renderer declaration, it must be right after the window is created
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if(!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    // Update Loop
    bool run = true;
    double last_time_stamp = 0;
    double runtime_delta_time = 1.0; // Time in Milliseconds since last update
    auto *render_service = new EngineRenderService(window, renderer);

    while (run) {
        // Pre-Render Thread
        SDL_Event event;
        SDL_WaitEvent(&event); // Pass event memory reference for use

        if (event.type == SDL_QUIT) {
            run = false;
        }

        runtime_delta_time = (static_cast<double> (event.syswm.timestamp) - static_cast<double> (last_time_stamp)) / 1000; // Assign runtime delta time and convert to MS

        // Render Thread

        render_service->RenderFrame(runtime_delta_time);

        // Post Render Thread
        last_time_stamp = static_cast<double> (event.syswm.timestamp);
    }

    return 0;
}