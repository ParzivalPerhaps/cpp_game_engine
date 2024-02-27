//
// Created by Hayden on 2/22/2024.
// It setup the file structure like this for some reason, must be a C++ thing
//

#ifndef ENGINERENDERSERVICE_H
#define ENGINERENDERSERVICE_H
#include <SDL.h>


#include "UserInterfaceElements/UiFrame.h"


class EngineRenderService {
    private:
        SDL_Window *window_;
        SDL_Renderer *renderer_;
    public:

    EngineRenderService(SDL_Window *window, SDL_Renderer *renderer) {
        this->window_ = window;
        this->renderer_ = renderer;
    }

    int RenderFrame(SDL_Renderer *renderer, SDL_Window *window) {
        return 1;
    }

    int RenderFrame(double runtime_delta_time) {
        int r = SDL_RenderClear(renderer_);


        if (r != 0) {
            return r;
        }

        auto frame = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::CENTER_VERTICAL, 100, 100);

        auto frame2 = new UserInterfaceElements::UiFrame(UserInterfaceElements::LEFT, UserInterfaceElements::CENTER_VERTICAL, 100, 100);
        auto frame3 = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::BOTTOM, 100, 100);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);

        SDL_RenderFillRect(renderer_, frame->GetUiFrame(renderer_, window_));
        SDL_RenderFillRect(renderer_, frame2->GetUiFrame(renderer_, window_));
        SDL_RenderFillRect(renderer_, frame3->GetUiFrame(renderer_, window_));

        SDL_RenderDrawLine(renderer_, 12, 12, 74, 2);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

        SDL_RenderPresent(renderer_);

        return 1;
    }
};



#endif //ENGINERENDERSERVICE_H
