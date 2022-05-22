#include "game_logic.h"

GameGrid grid; // The game grid object
char outfileName[100]; // Name of the file to output the result to
int maxGenerations;
int currentGeneration;

int get_state_of(int row, int col) {
    if (row < 0 || col < 0 || row > grid.gridWidth-1 || col > grid.gridWidth-1) return -1;
    int index = (row * grid.gridWidth) + col;
    return *(grid.data + index);
}

int calculate_next_state(int row, int col) {
    int state = get_state_of(row, col);
    int sumAliveNeighbours = 0;
    if (state == -1) return -1;

    if (state == 0) {
        for (int r=-1; r<2; r++) {
            for (int c=-1; c<2; c++) {
                if (!(r == 0 && c == 0)) {
                    int nbrState = get_state_of(row+r, col+c);
                    if (nbrState == 1) sumAliveNeighbours++;
                }
            }
        }
        if (sumAliveNeighbours == 3) return 1;
        else return 0;

    } else if (state == 1) {
        for (int r=-1; r<2; r++) {
            for (int c=-1; c<2; c++) {
                if (!(r == 0 && c == 0)) {
                    int nbrState = get_state_of(row+r, col+c);
                    if (nbrState == 1) sumAliveNeighbours++;
                }
            }
        }
        if (sumAliveNeighbours < 2) return 0;
        else if (sumAliveNeighbours == 2 || sumAliveNeighbours == 3) return 1;
        else if (sumAliveNeighbours > 3) return 0;
    }
}

int load_position_config() {
    if (access("position_config.txt", F_OK) != 0) {
        printf("\nThe file position_config.txt does not exist, please create it and add comma separated coordinates (one pair per line) to run!\n\n");
        return 1;
    }
    FILE* fp;
    fp = fopen("position_config.txt", "r");
    char* line = (char *) malloc (20);
    grid.data = (int *) malloc (sizeof(int) * grid.gridWidth * grid.gridHeight);

    currentGeneration = 0;
    for (int i=0;i<grid.gridHeight; i++) {
        for (int j=0; j<grid.gridWidth; j++) {
            *(grid.data + (i*grid.gridWidth) + j) = 0;
        }
    }

    while(fgets(line, 20, fp)) {
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        char* token = strtok(line, ",");
        char* ptr;
        int iter = 0;
        int row = -1;
        int col = -1;
        while(token != NULL) {
            if (iter == 0) {
                row = strtol(token, &ptr, 10);
                if (strlen(ptr) > 0 && strcmp(ptr, "\n") != 0) {
                    printf("\nThere is an invalid coordinate pair in the position_config.txt file! Read the README file for help with formatting!\n\n");
                    return 1;
                }
            } else if (iter == 1) {
                col = strtol(token, &ptr, 10);
                if (strcmp(token, "\n") == 0 || (strlen(ptr) > 0 && strcmp(ptr, "\n") != 0)) {
                    printf("\nThere is an invalid coordinate pair in the position_config.txt file! Read the README file for help with formatting!\n\n");
                    return 1;
                }
            }
            iter++;
            token = strtok(NULL, ",");
        }
        if (grid.data == NULL) {
            return 1;
        }
        if (row < 0 || col < 0 || row >= grid.gridHeight || col >= grid.gridWidth) {
            printf("\nThere is an invalid coordinate pair in the position_config.txt file! Read the README file for help with formatting!\n\n");
            return 1;
        }
        *(grid.data + (row*grid.gridWidth + col)) = 1;
    }
    free(line);
    return 0;
}

int load_game_config() {
    if (access("game_config.txt", F_OK) != 0) {
        printf("\nThe file game_config.txt does not exist, please create it and add the required commands (see README file) to run!\n\n");
        return 1;
    }
    
    FILE* fp;
    fp = fopen("game_config.txt", "r");
    char* line = (char *) malloc (100);
    bool widthSet = false;
    bool genSet = false;
    bool outSet = false;
    bool heightSet = false;

    while(fgets(line, 100, fp)) {
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        bool hasColon = false;
        for (int i=0; i<strlen(line)-1; i++) {
            if (*(line+i) == ':') {
                hasColon = true;
            }
        }
        if (!hasColon) {
            printf("\nAn Invalid Command was found in the game_config.txt file! Read the README file for help!\n\n");
            return 1;
        }
        char* token = strtok(line, ":");
        char* command = (char *) malloc (50);
        int iter = 0;
        char* ptr;
        while(token != NULL) {
            if (iter == 0) {
                strcpy(command, token);
                iter++;
            } else if (iter == 1) {
                if (strcmp(command, "Grid-Width") == 0) {
                    int width = strtol(token, &ptr, 10);
                    if (width < 1 || strcmp(ptr, "\n") != 0) {
                        printf("\nValue given for 'Grid-Width' command was invalid! Read the README file for help!\n\n");
                        return 1;
                    } else {
                        grid.gridWidth = width;
                        widthSet = true;
                    }
                } else if (strcmp(command, "Grid-Height") == 0) {
                    int height = strtol(token, &ptr, 10);
                    if (height < 1 || strcmp(ptr, "\n") != 0) {
                        printf("\nValue given for 'Grid-Width' command was invalid! Read the README file for help!\n\n");
                        return 1;
                    } else {
                        grid.gridHeight = height;
                        heightSet = true;
                    }
                } else if (strcmp(command, "Generations") == 0) {
                    int genNum = strtol(token, &ptr, 10);
                    if (genNum < 1 || strcmp(ptr, "\n") != 0) {
                        printf("\nValue given for the 'Generation' command was invalid! Read the README file for help!\n\n");
                        return 1;
                    } else {
                        maxGenerations = genNum;
                        genSet = true;
                    }
                } else if (strcmp(command, "Out-File") == 0) {
                    if (*(token + strlen(token) - 1) == '\n') {
                        *(token + strlen(token) - 1) = '\0';
                    }
                    strcpy(outfileName, token);
                    outSet = true;
                } else {
                    printf("\nAn Invalid Command was found in the game_config.txt file! Read the README file for help!\n\n");
                    return 1;
                }
            }
            token = strtok(NULL, ":");
        }
        free(command);
    }
    free(line);

    if (!widthSet) {
        printf("\nThe grid width command was not supplied! Read the README file for help!\n\n");
    }
    if (!heightSet) {
        printf("\nThe grid height command was not supplied! Read the README file for help!\n\n");
    }
    if (!genSet) {
        printf("\nThe max number of generations was not set! Read the README file for help!\n\n");
    }
    if (!outSet) {
        printf("\nThe out-file was not set! Read the README file for help!\n\n");
    }
    if (widthSet && genSet && outSet && heightSet) {
        return 0;
    } else {
        return 1;
    }
    
}

GameGrid next_grid() {
    GameGrid testGrid;
    int width = grid.gridWidth;
    testGrid.gridWidth = width;
    int gridData[width*width];
    for (int i=0; i<width; i++) {
        for (int j=0; j<width; j++) {
            gridData[(i*width)+j] = calculate_next_state(i, j);
        }
    }
    testGrid.data = &gridData[0];
    return testGrid;
}

void saveAndExit() {
    FILE* fp;
    fp = fopen(outfileName, "w");
    for (int i=0; i<grid.gridWidth; i++) {
        for (int j=0; j<grid.gridWidth; j++) {
            if (*(grid.data + (i*grid.gridWidth + j)) == 1) {
                fprintf(fp, "%d,%d\n", i, j);
            }
        }
    }
    fclose(fp);
    printf("\nPositions of living cells in generation %d was saved to: %s\n\n", currentGeneration, outfileName);
    exit(0);
}