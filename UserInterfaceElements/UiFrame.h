//
// Created by Owner on 2/27/2024.
//

#ifndef UIFRAME_H
#define UIFRAME_H
#include <array>
#include <iostream>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "UiElement.h"
#include "../EngineRenderService.h"

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

    struct RenderOrder {
    public:
        SDL_Rect *rect_;
        SDL_Color color_;

        RenderOrder(SDL_Rect *rect, SDL_Color color) {
            this->color_ = color;
            this->rect_ = rect;
        }


    };

    class UiFrame : public UiElement {
    private:
        std::vector<UiElement> child_elements_;

        VerticalAnchorMode vertical_anchor_mode_;
        HorizontalAnchorMode horizontal_anchor_mode_;
        int width;
        int height;

        bool use_screen_size_scaling;
        double relative_screen_size_width;
        double relative_screen_size_height;

        SDL_Color background_color;
        SDL_Color text_color;

        std::array<UiElement, 5> ui_children;

        std::array<double, 2> getActualFrameSize(SDL_Window *window) const {
            int window_size_x;
            int window_size_y;

            SDL_GetWindowSize(window, &window_size_x, &window_size_y);

            if (use_screen_size_scaling) {
                std::array<double, 2> result_array;
                result_array[0] = window_size_x * relative_screen_size_width;
                result_array[1] = window_size_y * relative_screen_size_height;

                return result_array;
            }else {
                std::array<double, 2> result_array;
                result_array[0] = width + 0.0;
                result_array[1] = height + 0.0;

                return result_array;
            }
        }

        std::array<RenderOrder, 4>* makeBorder(SDL_Window *window, int x, int y) {
            const std::array<double, 2> dimensions = getActualFrameSize(window);

            SDL_Rect *leftRect = new SDL_Rect();
            leftRect->h = dimensions[1];
            leftRect->w = border_width;

            leftRect->x = x;
            leftRect->y = y;
            RenderOrder *left_render_order = new RenderOrder(leftRect, border_color);

            SDL_Rect *rightRect = new SDL_Rect();
            rightRect->h = dimensions[1];
            rightRect->w = border_width;

            rightRect->x = x + (dimensions[0] - border_width);
            rightRect->y = y ;
            RenderOrder *right_render_order = new RenderOrder(rightRect, border_color);

            SDL_Rect *topRect = new SDL_Rect();
            topRect->h = border_width;
            topRect->w = dimensions[0];

            topRect->x = x;
            topRect->y = y;
            RenderOrder *top_render_order = new RenderOrder(topRect, border_color);

            SDL_Rect *bottomRect = new SDL_Rect();
            bottomRect->h = border_width;
            bottomRect->w = dimensions[0];

            bottomRect->x = x;
            bottomRect->y = y + (dimensions[1]);
            RenderOrder *bottom_render_order = new RenderOrder(bottomRect, border_color);

            return new std::array<RenderOrder, 4> {*left_render_order, *right_render_order, *top_render_order, *bottom_render_order};
        }
    public:
        SDL_Color border_color;
        int border_width;
        SDL_Color frame_color;

        UiFrame(HorizontalAnchorMode horizontal_anchor_mode, VerticalAnchorMode vertical_anchor_mode) {
            this->vertical_anchor_mode_ = vertical_anchor_mode;
            this->horizontal_anchor_mode_ = horizontal_anchor_mode;
            this->width = 100;
            this->height = 100;
        }

        UiFrame(const HorizontalAnchorMode horizontal_anchor_mode, const VerticalAnchorMode vertical_anchor_mode, double relative_size_x, double relative_size_y) {
            this->vertical_anchor_mode_ = vertical_anchor_mode;
            this->horizontal_anchor_mode_ = horizontal_anchor_mode;

            // Lock relative sizes to between 0 and 1
            relative_size_x = std::max(std::min(relative_size_x, 1.0), 0.0);
            relative_size_y = std::max(std::min(relative_size_y, 1.0), 0.0);

            this->use_screen_size_scaling = true;
            this->relative_screen_size_width = relative_size_x;
            this->relative_screen_size_height = relative_size_y;
        }

        UiFrame(const HorizontalAnchorMode horizontal_anchor_mode, const VerticalAnchorMode vertical_anchor_mode, const int width, const int height) {
            this->vertical_anchor_mode_ = vertical_anchor_mode;
            this->horizontal_anchor_mode_ = horizontal_anchor_mode;
            this->width = width;
            this->height = height;
        }

        std::array<UserInterfaceElements::RenderOrder, 5> GetUiFrame(SDL_Renderer *renderer, SDL_Window *window) {

            auto *display_rect = new SDL_Rect(); // Auto is a keyword that automatically infers the type for lines with the 'new' keyword

            int window_size_x;
            int window_size_y;

            SDL_GetWindowSize(window, &window_size_x, &window_size_y);

            if (use_screen_size_scaling) {
                display_rect->w = window_size_x * relative_screen_size_width;
                display_rect->h = window_size_y * relative_screen_size_height;
            }else {
                display_rect->w = this->width;
                display_rect->h = this->height;
            }

            const std::array<double, 2> actual_size = getActualFrameSize(window);

            std::cout << window_size_x << ", " << window_size_y << std::endl;

            switch (this->vertical_anchor_mode_) {
                case  TOP:
                    display_rect->y = actual_size[1];
                break;
                case CENTER_VERTICAL:
                    display_rect->y = (window_size_y / 2) - (actual_size[1] / 2);
                break;
                case BOTTOM:
                    display_rect->y = window_size_y - actual_size[1];
                break;
            }

            switch (this->horizontal_anchor_mode_) {
                case LEFT:
                    display_rect->x = 0;
                break;
                case CENTER_HORIZONTAL:
                    display_rect->x = (window_size_x / 2) - (actual_size[0] / 2);
                break;
                case RIGHT:
                    display_rect->x = window_size_x - actual_size[0];
                break;
            }

            RenderOrder *display_render_order = new RenderOrder(display_rect, frame_color);
            std::array<RenderOrder, 4> *borders = makeBorder(window, display_rect->x, display_rect->y);

            std::array<RenderOrder, 5> display_orders{{*display_render_order, borders->at(0), borders->at(1), borders->at(2), borders->at(3)}};

            std::cout << "getting ui frame";

            return display_orders;
        };
    };
} // UserInterfaceElements

#endif //UIFRAME_H
