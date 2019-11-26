//
// Created by jdemoss on 11/20/19.
//

#include "GameGraphics.h"

#include <functional>
#include <algorithm>
#include <utility>

struct PriorityDrawable {
    int Layer;
    float Sublayer;
    std::function<void(SDL_Renderer*)> DrawFunction;

    PriorityDrawable(std::function<void(SDL_Renderer*)> drawFunction, int layer, float sublayer) {
        Layer = layer;
        Sublayer = sublayer;
        DrawFunction = std::move(drawFunction);
    }
};

GameGraphics::GameGraphics() {
    DrawList = std::vector<PriorityDrawable*>();
}

void GameGraphics::Draw(SDL_Renderer* renderer) {
    std::sort(DrawList.begin(), DrawList.end(), [&renderer](PriorityDrawable* a, PriorityDrawable* b) {
        if (a->Layer == b->Layer) {
            return a->Sublayer - b->Sublayer;
        }
        return (float) (a->Layer - b->Layer);
    });
    for (PriorityDrawable* priorityDrawable : DrawList) {
        priorityDrawable->DrawFunction(renderer);
        delete(priorityDrawable);
    }
    DrawList.clear();
}

void GameGraphics::DrawRectangle(const Rectangle &rectangle, Color color, int layer, float sublayer, bool useCamera) {
    DrawList.emplace_back(new PriorityDrawable([=](SDL_Renderer* renderer) {
        SetRendererColor(renderer, color);
        SDL_Rect* sdlRect = ToSDLRect(rectangle, useCamera);
        SDL_RenderFillRect(renderer, sdlRect);
        delete (sdlRect);
    }, layer, sublayer));
}

void GameGraphics::SetRendererColor(SDL_Renderer* renderer, Color color) {
    SDL_SetRenderDrawColor(renderer, color.GetRed(), color.GetGreen(), color.GetGreen(), color.GetAlpha());
}

SDL_Rect* GameGraphics::ToSDLRect(Rectangle rectangle, bool useCamera) {
    SDL_Rect* rect = new SDL_Rect;
    rect->x = rectangle.GetPosition().GetXInt();
    rect->y = rectangle.GetPosition().GetYInt();
    rect->h = rectangle.GetSize().GetXInt();
    rect->w = rectangle.GetSize().GetYInt();
    if (useCamera) {
        rect->x += Camera.GetXInt();
        rect->y += Camera.GetYInt();
    }
    return rect;
}
