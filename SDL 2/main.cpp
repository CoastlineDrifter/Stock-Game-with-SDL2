#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int RECT_COUNT = 1000;

int i = 0;
float open[1000];
float close[1000];
float startingX, startingY;
int currentX = 60;
int camX = 0;
int camY = 0;
int offsetX = 0, offsetY = 0;
int lastMouseX, lastMouseY;
int mouseX, mouseY;
bool dragging = false;

float scaling = 1.0f;

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Stocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect rects[RECT_COUNT];
    SDL_Event e;
    bool quit = false;
    Uint32 lastUpdateTime = SDL_GetTicks();
    Uint32 lastUpdateTime2 = SDL_GetTicks();

    startingX = 100;
    startingY = 900;

    while (!quit) {
        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEMOTION) {
                if (dragging) {
                    offsetX += mouseX - lastMouseX;
                    offsetY += mouseY - lastMouseY;
                }
                lastMouseX = mouseX;
                lastMouseY = mouseY;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                dragging = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                dragging = false;
            }

            if (e.type == SDL_MOUSEWHEEL) {
                if (e.wheel.y > 0) {
                    scaling *= 1.1f;
                }
                else if (e.wheel.y < 0) {
                    scaling * .9f;
                }
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastUpdateTime >= 100) {
            lastUpdateTime = currentTime;
            open[i] = rand() % (100 - -100 + 1) + -100;
            rects[i].w = 45;
            rects[i].h = open[i];
            
            if (i > 0) {
                rects[i].y = rects[i - 1].y + rects[i - 1].h;
                rects[i].x = 60 + rects[i-1].x;
            } else {
                rects[i].y = startingY;
                rects[i].x = startingX;
            }
        }

        Uint32 currentTime2 = SDL_GetTicks();
        if (currentTime2 - lastUpdateTime2 >= 4000) {
            lastUpdateTime2 = currentTime2;
            close[i] = rects[i].y;
            i++;
            currentX += 60;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int j = 0; j < i + 1; ++j) {
            rects[j].x += offsetX;
            rects[j].y += offsetY;
            startingX += offsetX;
            startingY += offsetY;

            if (open[j] < 0 && j > 0) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            } else {
                if (j > 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                }
            }
            if (j == 0 && open[j] > 0) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else {
                if (j == 0) {
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                }
            }
            SDL_RenderFillRect(renderer, &rects[j]);
        }

        SDL_RenderPresent(renderer);
        offsetX = 0;
        offsetY = 0;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
