/***********************************************************
 * This file contains definitions for init.c
 * 
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

#ifndef INIT_GUARD
#define INIT_GUARD
#include "common.h"

// This function initializes SDL
bool init();

// Handle the closing and cleanup of SDL
void cleanup();
#endif