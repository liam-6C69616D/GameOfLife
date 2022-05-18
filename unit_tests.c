#include "unity.h"
#include "game_logic.h"


void test_get_state_of() {
    grid.gridWidth = 4;
    int dataArray[16] = {0,1,0,0,
                         0,1,0,0,
                         0,1,0,0,
                         1,0,0,0};
                         
    grid.data = &dataArray[0];
    int state;
    // Test valid data
    state = get_state_of(1, 1);
    TEST_ASSERT(state == 1);
    state = get_state_of(0, 0);
    TEST_ASSERT(state == 0);

    // Test invalid data
    state = get_state_of(-1, 0);
    TEST_ASSERT(state == -1);
    state = get_state_of(4, -2);
    TEST_ASSERT(state == -1);
}

void test_calculate_next_state() {
    grid.gridWidth = 4;
    int dataArray[16] = {1,0,0,0,
                         0,1,1,0,
                         0,0,1,0,
                         1,0,1,0};

    grid.data = &dataArray[0];
    int newstate;

    // Test valid data
    newstate = calculate_next_state(0, 0);
    TEST_ASSERT(newstate == 0);
    newstate = calculate_next_state(1, 1);
    TEST_ASSERT(newstate == 1);
    newstate = calculate_next_state(3, 2);
    TEST_ASSERT(newstate == 0);
    newstate = calculate_next_state(3, 1);
    TEST_ASSERT(newstate == 1);
    newstate = calculate_next_state(0, 3);
    TEST_ASSERT(newstate == 0);

    // Test invalid data
    newstate = calculate_next_state(-10, 5);
    TEST_ASSERT(newstate == -1);
    newstate = calculate_next_state(7, -3);
    TEST_ASSERT(newstate == -1);
}

void test_load_position_config() {
    int result;
    rename("position_config.txt", "temp_position_config.txt"); // Rename the user created config file so the function will not be able to find it by it's name
    result = load_position_config();
    TEST_ASSERT(result == 1); // Should have code 1 if no file exists
    FILE* fp;

    fp = fopen("position_config.txt", "w"); // Make an invalid file config with missing coords and a letter instaed of a number
    fprintf(fp, "0,\n0,n\n1,1\n1,2\n2,1\n2,2\n3,0\n3,3\n");
    fclose(fp);
    result = load_position_config();
    TEST_ASSERT(result == 1); // Should have code 1 for invalid config

    fp = fopen("position_config.txt", "w"); // Make an invalid config with a coord out of index
    fprintf(fp, "0,0\n0,3\n1,1\n1,2\n2,1\n2,2\n3,0\n3,3\n40,-3");
    fclose(fp);
    result = load_position_config();
    TEST_ASSERT(result == 1); // Should have code 1 for invalid config

    fp = fopen("position_config.txt", "w"); // Make a new file to test function
    fprintf(fp, "0,0\n0,3\n1,1\n1,2\n2,1\n2,2\n3,0\n3,3\n");
    fclose(fp);
    grid.gridWidth = 4; // 4x4 grid
    int data[16] = {0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0};
    grid.data = &data[0]; // Set up blank data
    result = load_position_config();
    TEST_ASSERT(result == 0); // Check for the correct status code
    int testData[16] = {1,0,0,1,
                        0,1,1,0,
                        0,1,1,0,
                        1,0,0,1}; // Correct layout of grid data according to file that was created

    bool match = true; // Bool to track if the grid data matches what is should be
    if (grid.data == NULL) TEST_FAIL();
    for(int i=0; i<16; i++) {
        if (testData[i] != *(grid.data + i)) {
            match = false;
        }
    }

    TEST_ASSERT(match == true); // Check the data was correctly read and initialised from the text file
    TEST_ASSERT(currentGeneration == 0);
    remove("position_config.txt"); // Remove our test config file
    rename("temp_position_config.txt", "position_config.txt"); // Rename the users file for use in the program
}

void test_load_game_config() {
    int result;

    rename("game_config.txt", "temp_game_config.txt"); // Rename the user created config file so the function will not be able to find it by it's name
    result = load_game_config();
    TEST_ASSERT(result == 1); // Should have code 1 if no file exists

    grid.gridWidth = -1; // Set to invalid value so has to be set correctly later
    maxGenerations = -1;
    strcpy(outfileName, "");

    FILE* fp;

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Generations:40\nOut-File:output.txt\n"); // Miss Grid-Width
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Grid-Width:10\nOut-File:output.txt\n"); // Miss Generations
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Grid-Width:10\nGenerations:40\n"); // Miss Out-File
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Grid-Width:-1\nGenerations:40\nOut-File:output.txt\n"); // Invalid Width
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Grid-Width:10\nGenerations:-1\nOut-File:output.txt\n"); // Invalid Generations
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "grid-width:10\ngenerations:40\nout-file:output.txt\n"); // Wrong case on commands
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 1);

    fp = fopen("game_config.txt", "w");
    fprintf(fp, "Grid-Width:10\nGenerations:40\nOut-File:output.txt\n"); // Valid Data
    fclose(fp);
    result = load_game_config();
    TEST_ASSERT(result == 0); // Check for okay error status
    TEST_ASSERT(grid.gridWidth == 10); // Check grid width set correctly
    TEST_ASSERT(maxGenerations == 40); // Check max generations set correctly
    TEST_ASSERT_EQUAL_STRING("output.txt", outfileName); // Check output file set correctly

    remove("game_config.txt"); // Remove our test config file
    rename("temp_game_config.txt", "game_config.txt"); // Rename the users file for use in the program
}

void test_next_grid() {
    GameGrid resultGrid; // Create result grid holder
    grid.gridWidth = 5;
    int dataArray[25] = {0,0,0,0,1,
                         0,1,0,1,1,
                         0,0,1,0,1,
                         1,0,0,1,0,
                         1,1,0,0,0}; // Data for the current grid state

    int correctStep[25] = {0,0,0,1,1,
                           0,0,1,0,1,
                           0,1,1,0,1,
                           1,0,1,1,0,
                           1,1,0,0,0}; // Correct data for next generation
    
    grid.data = &dataArray[0]; // Set the grid data for this generations
    resultGrid = next_grid(); // Work out the grid for next generation

    if (resultGrid.data == NULL) { // Make sure there was no error
        TEST_FAIL();
    }
    
    bool match = true;
    for (int i=0; i<25; i++) { // Check the next generations grid is correct
        if (correctStep[i] != *(resultGrid.data + i)) {
            match = false;
        }
    }

    TEST_ASSERT(match == true);
    TEST_ASSERT(resultGrid.gridWidth == 5); // Check result grid is set up properly
}


void setUp() {

}

void tearDown() {

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_get_state_of);
    RUN_TEST(test_calculate_next_state);
    RUN_TEST(test_load_position_config);
    RUN_TEST(test_load_game_config);
    RUN_TEST(test_next_grid);
    return UNITY_END();
}