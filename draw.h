/***********************************************************
 * This file contains definitions for draw.c
 * 
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

#ifndef DRAW_GUARD
#define DRAW_GUARD

#include "common.h"
#include <SDL2/SDL_ttf.h>

extern TTF_Font* font;
extern TTF_Font* smallerFont;
extern SDL_Surface* next_text;
extern SDL_Surface* reset_text;
extern SDL_Surface* save_text;
extern SDL_Surface* error_text;
extern SDL_Texture* next_text_texture;
extern SDL_Texture* reset_text_texture;
extern SDL_Texture* save_text_texture;
extern SDL_Texture* error_text_texture;
extern bool nextFilled;
extern bool resetFilled;
extern bool saveFilled;
extern bool error;

// Prepare the scene to be drawn
void prepareScene();

// Draw the scene
void presentScene();

void initDraw();

void drawWindow();

#endif