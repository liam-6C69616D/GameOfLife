# Game of Life Project
###### Liam Smith
This project is a graphical representation of Conway's Game of Life using C and SDL, with unity for unit testing.

#### Making the Project
After cloning the git repository, you should download the unity zip file from [Unity](https://github.com/ThrowTheSwitch/Unity/archive/master.zip).
Unzip this file and rename the folder `unity`, then copy this folder into the root of the repository.

The project repository has a `build` folder containing 2 config files `position_config.txt` and `game_config.txt` which are pre-populated with a demo configuration, ready to run.

The `position_config.txt` file takes coordinate pairs (one per line) separated by a comma and errors on invalid co-ords:
```
0,0
2,1
2,2
3,4
4,3
1,1
1,2
```

The `game_config.txt` file takes the following commands and format (commands are case sensitive and will throw CLI errors if any mistakes are found):
```
Grid-Width: 20 # Width and height of the game grid, must be an integer
Generations: 40 # The maximum nuber of generations the user can run, integer
Out-File: output.txt # The name of a text file to write the output to
```

> These files will be included with the repository when it is cloned with git and will be in the build folder, with demo values already set to play an oscillator[^1]. Feel free to try it out with these default values and then mess around with the content of the files and see what you can create. Also, feel free to delete these config files and remake them yourself (however, if they don't exist at runtime, the program will throw an error).

To make the project run the following on the command line from the root of the repository:
``` bash
cd build
cmake ..
make
```

This will make two executable files provided that the required SDL libraries are in place and Unity has been installed as detailed above [[#Making the Project | Making the Project]]. Any Library errors might be fixed [[#Troubleshooting | here]].

#### Running the Executables
From the build folder, both of the executable files are available to run after executing the [[#^074022 | bash commands]]. 

To run the unit tests for the project:
``` bash
./unit_tests
```

And to run the game of life:
``` bash
./gameoflife
```

Any errors will be shown on the command line.

#### Playing the Game of Life
There are 3 buttons in the UI for the operation of the game: 
- The `Next >>` button will increment the generation and show the next stage.
- The `Reset <<` button resets the game back to the state defined in the `position_config.txt` file.
- The `Save` button saves the active coordinates of the current generation to the user specified output file from `game_config.txt`.

#### Troubleshooting
###### Library errors
__For errors with unity__: try removing the folder from the main directory, redownloading the zip file from [here](https://github.com/ThrowTheSwitch/Unity/archive/master.zip) or [here](https://www.throwtheswitch.org/unity), unzip it again and add it back into the main directory, making sure it has the name `unity`.

__For errors with SDL__: There should be no errors with SDL on `feng-linux` as it is preinstalled and worked fine during all of the tests. If there is an error however, try running the following commands to install the development version of SDL:

``` bash
sudo apt install libsdl2-dev
sudo apt install libsdl2-ttf-dev
```

__For all other errors__: Any errors that the program catches will output to the console with where the error was caught. The errors aren't overly specific, they may only show there was an error in the config files for instance. In this case, check the file naming and formatting/instructions to make sure they match case and style.

There shouldn't be any unhandled exceptions in the program but just incase there are, just try rerunning the program. For any recurring errors, please try a fresh install and following these steps over again.


[^1]: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#/media/File:Game_of_life_pulsar.gif
