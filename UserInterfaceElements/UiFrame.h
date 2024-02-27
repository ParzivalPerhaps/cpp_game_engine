//
// Created by Owner on 2/27/2024.
//

#ifndef UIFRAME_H
#define UIFRAME_H
#include <iostream>
#include <SDL_rect.h>
#include <SDL_render.h>

namespace UserInterfaceElements {
    enum VerticalAnchorMode {
        TOP,
        CENTER_VERTICAL,
        BOTTOM,
    };

    enum HorizontalAnchorMode {
        LEFT,
        RIGHT,
        CENTER_HORIZONTAL
    };

    class UiFrame {
        private:
            VerticalAnchorMode vertical_anchor_mode_;
            HorizontalAnchorMode horizontal_anchor_mode_;
            int width;
            int height;
        public:
            UiFrame(HorizontalAnchorMode horizontal_anchor_mode, VerticalAnchorMode vertical_anchor_mode) {
                this->vertical_anchor_mode_ = vertical_anchor_mode;
                this->horizontal_anchor_mode_ = horizontal_anchor_mode;
                this->width = 100;
                this->height = 100;
            }

            UiFrame(const HorizontalAnchorMode horizontal_anchor_mode, const VerticalAnchorMode vertical_anchor_mode, const int width, const int height) {
                this->vertical_anchor_mode_ = vertical_anchor_mode;
                this->horizontal_anchor_mode_ = horizontal_anchor_mode;
                this->width = width;
                this->height = height;
            }

            const SDL_Rect *GetUiFrame(SDL_Renderer *renderer, SDL_Window * window) {
                auto *display_rect = new SDL_Rect(); // Auto is a keyword that automatically infers the type for lines with the 'new' keyword

                display_rect->w = this->width;
                display_rect->h = this->height;

                int window_size_x;
                int window_size_y;

                SDL_GetWindowSize(window, &window_size_x, &window_size_y);

                switch (this->vertical_anchor_mode_) {
                    case  TOP:
                        display_rect->y = this->height;
                        break;
                    case CENTER_VERTICAL:
                        display_rect->y = window_size_y / 2;
                        break;
                    case BOTTOM:
                        display_rect->y = window_size_y - this->height;
                        break;
                }

                switch (this->horizontal_anchor_mode_) {
                    case LEFT:
                        display_rect->x = this->width;
                        break;
                    case CENTER_HORIZONTAL:
                        display_rect->x = (window_size_x / 2);
                        break;
                    case RIGHT:
                        display_rect->x = window_size_x - this->width;
                        break;
                }

                return display_rect;
            }
    };

} // UserInterfaceElements

#endif //UIFRAME_H
