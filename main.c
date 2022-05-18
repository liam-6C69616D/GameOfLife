#include "common.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "game_logic.h"


/***********************************************************
 * This code was developed using the SDL tutorial found at:
 * https://www.parallelrealities.co.uk/tutorials/#shooter
 * 
 * Author: Liam Smith
************************************************************/

App app;

int main(int argc, char* argv[]) {
    int loadGame = load_game_config();
    if (loadGame) exit(1);
    int loadPos = load_position_config();
    if (loadPos) exit(1);

    memset(&app, 0, sizeof(App)); // Clear the app variable
    init(); // Set up SDL
    initDraw();
    atexit(cleanup); // When exit() is called, call out cleanup function

    while(1) {
        prepareScene();
        readInput();
        drawWindow();
        presentScene();
        SDL_Delay(16); // About 60fps
    }

    return 0;
}