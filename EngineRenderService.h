//
// Created by Hayden on 2/22/2024.
// It setup the file structure like this for some reason, must be a C++ thing
//

#ifndef ENGINERENDERSERVICE_H
#define ENGINERENDERSERVICE_H
#include <SDL.h>
#include <vector>


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

        auto frame = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::BOTTOM, 1.0, 0.15);

        SDL_Color *frame_color = new SDL_Color();
        frame_color->r = 255;
        frame_color->b = 255;
        frame_color->g = 255;
        frame_color->a = 255;

        frame->frame_color = *frame_color;

        frame->border_width = 2;

        SDL_Color *border_color = new SDL_Color();
        border_color->r = 0;
        border_color->g = 255;
        border_color->b = 0;
        border_color->a = 255;
        frame->border_color = *border_color;

        auto frame2 = new UserInterfaceElements::UiFrame(UserInterfaceElements::CENTER_HORIZONTAL, UserInterfaceElements::BOTTOM, 1.0, 0.2);

        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);

        std::array<UserInterfaceElements::RenderOrder, 5> frame_orders = frame->GetUiFrame(renderer_, window_);

        for (UserInterfaceElements::RenderOrder render_order : frame_orders) {
            SDL_SetRenderDrawColor(renderer_, render_order.color_.r, render_order.color_.g, render_order.color_.b, render_order.color_.a);
            SDL_RenderFillRect(renderer_, render_order.rect_);
        }

        SDL_RenderDrawLine(renderer_, 12, 12, 74, 2);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

        SDL_RenderPresent(renderer_);

        return 1;
    }
};



#endif //ENGINERENDERSERVICE_H
