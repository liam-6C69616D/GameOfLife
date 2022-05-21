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

void readInput() {
    SDL_Event event; // An SDL event variable

    while (SDL_PollEvent(&event)) { // Polls the event queue until it is emtpy, checks all queued events for a quit
        switch (event.type)
        {
        case SDL_QUIT: // Check for the event that the close "x" is pressed
            exit(0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;
                double cellSize = grid.gridWidth > grid.gridHeight ? 525 / grid.gridWidth : 525 / grid.gridHeight;
                double startX = SCREEN_WIDTH/2 - (grid.gridWidth * cellSize)/2;
                double startY = 537.5/2 - (grid.gridHeight * cellSize)/2 + 15;
                double endX = startX + (grid.gridWidth * cellSize);
                double endY = startY + (grid.gridHeight * cellSize);
                
                if ((x>137.5 && x<262.5) && (y>562.5 && y<612.5)) {
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
                } else if ((x>337.5 && x<462.5) && (y>562.5 && y<612.5)) {
                    error = false;
                    load_position_config();
                    resetFilled = true;
                } else if ((x>537.5 && x<662.5) && (y>562.5 && y<612.5)) {
                    saveAndExit();
                    saveFilled = true;
                } else if (((x>startX) && (y>startY)) && ((x<endX) && (x<endY))) {
                    int row = (y - startY) / cellSize;
                    int col = (x - startX) / cellSize;
                    if (*(grid.data + (row*grid.gridWidth + col)) == 0) {
                        *(grid.data + (row*grid.gridWidth + col)) = 1;
                    } else if (*(grid.data + (row*grid.gridWidth + col)) == 1) {
                        *(grid.data + (row*grid.gridWidth + col)) = 0;
                    }
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            nextFilled = false;
            resetFilled = false;
            saveFilled = false;
            break;
        default:
            break;
        }
    }
}