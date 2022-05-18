#ifndef GAME_LOGIC_GUARD
#define GAME_LOGIC_GUARD
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************
 * This file contains the function prototypes for the logic
 * behind the game of life
 * 
 * Author: Liam Smith
************************************************************/

typedef struct grid {
    int gridWidth; // Width of the grid
    int* data; // Pointer to data for the grid's cells
} GameGrid;

extern GameGrid grid; // The game grid object
extern char outfileName[100]; // Name of the file to output the result to
extern int maxGenerations;
extern int currentGeneration;

// Get the state of a cell at a given row and column
int get_state_of(int row, int col);

// Calculate the state of a cell for the next turn
int calculate_next_state(int row, int col);

// Load the position config file to create the starting layout
int load_position_config();

// Load the environment config file to get user values
// such as grid size and number of turns to play
int load_game_config();

// Return a game grid which contains the next stage of
// evolution
GameGrid next_grid();

void saveAndExit();


#endif