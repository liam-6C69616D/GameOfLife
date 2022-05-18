/***********************************************************
 * This file contains functions to initialize SDL
 * 
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

#include "init.h"
#include "game_logic.h"
#include <SDL2/SDL_ttf.h>

bool init() {
    int rendererFlags, windowFlags; // Flags to pass to the functions to create the window and the renderer
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // Initialize SDL and error if it doesn't init properly
        printf("SDL Couldn't Initialize! Error: %s\n", SDL_GetError());
        return false;
    }
    else {
        // Create window
        // (title, x position of win, y position of win, width, height, creation flags (e.g. show when made: SDL_WINDOW_SHOWN))
        app.window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_UNDEFINED, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(!app.window) { // NULL on error
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        } else {
            app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags); // Create the renderer for the window
        }
    }

    if (TTF_Init() < 0) {
        printf("TTF Couldn't Initialize! Error: %s\n", TTF_GetError());
    }
}

void cleanup() {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    free(grid.data);
}