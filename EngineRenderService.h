//
// Created by Hayden on 2/22/2024.
// It setup the file structure like this for some reason, must be a C++ thing
//

#ifndef ENGINERENDERSERVICE_H
#define ENGINERENDERSERVICE_H
#include <SDL.h>


class EngineRenderService {
    public:

    static int RenderFrame(SDL_Renderer *renderer, SDL_Window *window) {
        return 1;
    }

    static int RenderFrame(SDL_Renderer *renderer, SDL_Window *window, double runtime_delta_time) {
        int r = SDL_RenderClear(renderer);


        if (r != 0) {
            return r;
        }



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        auto *f_rect = new SDL_Rect(); // f_rect must be a pointer because new SDL_Rect() returns a pointer

        f_rect->x = 0;
        f_rect->y = 0;
        f_rect->w = 50;
        f_rect->h = 100;

        SDL_RenderFillRect(renderer, f_rect);
        SDL_RenderDrawLine(renderer, 12, 12, 74, 2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

        return 1;
    }
};



#endif //ENGINERENDERSERVICE_H
