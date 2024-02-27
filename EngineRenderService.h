//
// Created by Hayden on 2/22/2024.
// It setup the file structure like this for some reason, must be a C++ thing
//

#ifndef ENGINERENDERSERVICE_H
#define ENGINERENDERSERVICE_H
#include <SDL.h>


#include "UserInterfaceElements/UiFrame.h"


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

        auto frame = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::CENTER_VERTICAL, 100, 100);

        auto frame2 = new UserInterfaceElements::UiFrame(UserInterfaceElements::LEFT, UserInterfaceElements::CENTER_VERTICAL, 100, 100);
        auto frame3 = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::BOTTOM, 100, 100);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_RenderFillRect(renderer, frame->GetUiFrame(renderer, window));
        SDL_RenderFillRect(renderer, frame2->GetUiFrame(renderer, window));
        SDL_RenderFillRect(renderer, frame3->GetUiFrame(renderer, window));

        SDL_RenderDrawLine(renderer, 12, 12, 74, 2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);

        return 1;
    }
};



#endif //ENGINERENDERSERVICE_H
