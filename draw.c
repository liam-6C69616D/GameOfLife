/***********************************************************
 * This file contains functions to do with drawing and 
 * rendering
 * 
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

#include "draw.h"
#include "game_logic.h"
#include <SDL2/SDL_ttf.h>

TTF_Font* font;
TTF_Font* smallerFont;
SDL_Surface* next_text;
SDL_Surface* reset_text;
SDL_Surface* save_text;
SDL_Surface* error_text;
SDL_Texture* next_text_texture;
SDL_Texture* reset_text_texture;
SDL_Texture* save_text_texture;
SDL_Texture* error_text_texture;
bool nextFilled;
bool resetFilled;
bool saveFilled;
bool error;

void prepareScene() {
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255); // Sets colour of the renderer
	SDL_RenderClear(app.renderer);
}

void presentScene() {
	SDL_RenderPresent(app.renderer); // Render the scene
}

void initDraw() {
	error = false;
	font = TTF_OpenFont("../Roboto-Light.ttf", 30);
	SDL_Color color = {0,0,0};
	
	if (!font) {
		printf("Failed to load font: %s\n", TTF_GetError());
	}

	next_text = TTF_RenderText_Solid(font, "Next >>", color);
	reset_text = TTF_RenderText_Solid(font, "Reset <<", color);
	save_text = TTF_RenderText_Solid(font, "Save", color);

	next_text_texture = SDL_CreateTextureFromSurface(app.renderer, next_text);
	reset_text_texture = SDL_CreateTextureFromSurface(app.renderer, reset_text);
	save_text_texture = SDL_CreateTextureFromSurface(app.renderer, save_text);

	nextFilled = false;
	resetFilled = false;
	saveFilled = false;
	smallerFont = TTF_OpenFont("../Roboto-Light.ttf", 21);
}

void drawWindow() {

	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);

	double cellSize = 525 / grid.gridWidth;
	double drawingX = 137.5;
	double drawingY = 25;

	for (int i=0; i<grid.gridWidth; i++) {
		for (int j=0; j<grid.gridWidth; j++) {
			SDL_Rect cell;
			cell.x = drawingX;
			cell.y = drawingY;
			cell.w = cellSize;
			cell.h = cellSize;
			if (*(grid.data + (i*grid.gridWidth + j)) == 1) {
				SDL_RenderFillRect(app.renderer, &cell);
			} else {
				SDL_RenderDrawRect(app.renderer, &cell);
			}
			drawingX += cellSize;
		}
		drawingX = 137.5;
		drawingY += cellSize;
	}

	SDL_Rect nextButton;
	nextButton.x = 137.5;
	nextButton.y = 562.5;
	nextButton.w = 125;
	nextButton.h = 50;
	if (nextFilled == false) {
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(app.renderer, &nextButton);
	} else {
		SDL_SetRenderDrawColor(app.renderer, 180, 180, 180, 255);
		SDL_RenderFillRect(app.renderer, &nextButton);
	}

	SDL_Rect resetButton;
	resetButton.x = 337.5;
	resetButton.y = 562.5;
	resetButton.w = 125;
	resetButton.h = 50;
	if (resetFilled == false) {
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(app.renderer, &resetButton);
	} else {
		SDL_SetRenderDrawColor(app.renderer, 180, 180, 180, 255);
		SDL_RenderFillRect(app.renderer, &resetButton);
	}

	SDL_Rect saveButton;
	saveButton.x = 537.5;
	saveButton.y = 562.5;
	saveButton.w = 125;
	saveButton.h = 50;
	if (saveFilled == false) {
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(app.renderer, &saveButton);
	} else {
		SDL_SetRenderDrawColor(app.renderer, 180, 180, 180, 255);
		SDL_RenderFillRect(app.renderer, &saveButton);
	}
	

	SDL_Rect dest = {150,570, next_text->w, next_text->h};
	SDL_RenderCopy(app.renderer, next_text_texture, NULL, &dest);

	SDL_Rect resetDest = {347.5, 570, reset_text->w, reset_text->h};
	SDL_RenderCopy(app.renderer, reset_text_texture, NULL, &resetDest);

	SDL_Rect saveDest = {565, 570, save_text->w, save_text->h};
	SDL_RenderCopy(app.renderer, save_text_texture, NULL, &saveDest);


	SDL_Color color = {0,0,0};
	char genText[16];
	sprintf(genText, "Generation: %d", currentGeneration);
	SDL_Surface* generation_text;
	generation_text = TTF_RenderText_Solid(smallerFont, genText, color);
	SDL_Texture* gen_text_texture;
	gen_text_texture = SDL_CreateTextureFromSurface(app.renderer, generation_text);
	SDL_Rect genDest = {337.5, 0, generation_text->w, generation_text->h};
	SDL_RenderCopy(app.renderer, gen_text_texture, NULL, &genDest);

	SDL_DestroyTexture(gen_text_texture);
	SDL_FreeSurface(generation_text);

	if (error) {
		SDL_Color color = {255,0,0};
		char errorText[60] = "Max Generations Reached! Reset the program or save and exit";
		SDL_Surface* error_text;
		error_text = TTF_RenderText_Solid(smallerFont, errorText, color);
		SDL_Texture* error_text_texture;
		error_text_texture = SDL_CreateTextureFromSurface(app.renderer, error_text);
		SDL_Rect errorDest = {120, 615, error_text->w, error_text->h};
		SDL_RenderCopy(app.renderer, error_text_texture, NULL, &errorDest);

	}
	SDL_DestroyTexture(error_text_texture);
	SDL_FreeSurface(error_text);
}