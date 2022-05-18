#ifndef GAME_VARIABLES_GUARD
#define GAME_VARIABLES_GUARD
#include <SDL2/SDL.h>

/***********************************************************
 * This file holds all of the global variables that will 
 * be used in the SDL code.
 * 
 * Author: Liam Smith
************************************************************/

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650

// Define the structure for an application
typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} App;

// The application we will run
extern App app;

#endif