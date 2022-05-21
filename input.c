/***********************************************************
 * This file contains functions to handle user input
 * 
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

#include "input.h"
#include "game_logic.h"
#include "draw.h"

bool leftMouseDown = false;
bool rightMouseDown = false;

void readInput() {
    SDL_Event event; // An SDL event variable
    int mouseX;
    int mouseY;
    double cellSize = grid.gridWidth > grid.gridHeight ? 525 / grid.gridWidth : 525 / grid.gridHeight; // Size of each cell
    double startX = SCREEN_WIDTH/2 - (grid.gridWidth * cellSize)/2; // x coordinate top left of grid
    double startY = 537.5/2 - (grid.gridHeight * cellSize)/2 + 15; // y coordinate top left of grid
    double endX = startX + (grid.gridWidth * cellSize); // x coordinate bottom right of grid
    double endY = startY + (grid.gridHeight * cellSize); // y coordinate bottom right of grid

    while (SDL_PollEvent(&event)) { // Polls the event queue until it is emtpy, checks all queued events for a quit
        switch (event.type)
        {
        case SDL_QUIT: // Check for the event that the close "x" is pressed
            exit(0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                leftMouseDown = true;
                mouseX = event.button.x;
                mouseY = event.button.y;
                
                if ((mouseX > 137.5 && mouseX < 262.5) && (mouseY > 562.5 && mouseY < 612.5)) {
                    if (currentGeneration == maxGenerations) {
                        error = true;
                    } else {
                        error = false;
                        GameGrid newGrid = next_grid();

                        for (int i=0; i<grid.gridWidth; i++) {
                            for (int j=0; j<grid.gridWidth; j++) {
                                *(grid.data + (i*grid.gridWidth + j)) = *(newGrid.data + (i*grid.gridWidth + j));
                            }
                        }
                        currentGeneration++;
                    }
                    nextFilled = true;
                } else if ((mouseX > 337.5 && mouseX < 462.5) && (mouseY > 562.5 && mouseY < 612.5)) {
                    error = false;
                    load_position_config();
                    resetFilled = true;
                } else if ((mouseX > 537.5 && mouseX < 662.5) && (mouseY > 562.5 && mouseY < 612.5)) {
                    saveAndExit();
                    saveFilled = true;
                } else if (((mouseX > startX) && (mouseY > startY)) && ((mouseX < endX) && (mouseY < endY))) {
                    int row = (mouseY - startY) / cellSize;
                    int col = (mouseX - startX) / cellSize;
                    if (*(grid.data + (row*grid.gridWidth + col)) == 0) {
                        *(grid.data + (row * grid.gridWidth + col)) = 1;
                    }
                }
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                rightMouseDown = true;
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (((mouseX > startX) && (mouseY > startY)) && ((mouseX < endX) && (mouseY < endY))) {
                    int row = (mouseY - startY) / cellSize;
                    int col = (mouseX - startX) / cellSize;
                    if (*(grid.data + (row*grid.gridWidth + col)) == 1) {
                        *(grid.data + (row * grid.gridWidth + col)) = 0;
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (leftMouseDown) {
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (((mouseX > startX) && (mouseY > startY)) && ((mouseX < endX) && (mouseY < endY))) {
                    int row = (mouseY - startY) / cellSize;
                    int col = (mouseX - startX) / cellSize;

                    if (*(grid.data + (row * grid.gridWidth + col)) == 0) {
                        *(grid.data + (row * grid.gridWidth + col)) = 1;
                    }
                }
            } else if (rightMouseDown) {
                mouseX = event.button.x;
                mouseY = event.button.y;
                if (((mouseX > startX) && (mouseY > startY)) && ((mouseX < endX) && (mouseY < endY))) {
                    int row = (mouseY - startY) / cellSize;
                    int col = (mouseX - startX) / cellSize;

                    if (*(grid.data + (row * grid.gridWidth + col)) == 1) {
                        *(grid.data + (row * grid.gridWidth + col)) = 0;
                    }
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            leftMouseDown = false;
            rightMouseDown = false;
            nextFilled = false;
            resetFilled = false;
            saveFilled = false;
            break;
        default:
            break;
        }
    }
}