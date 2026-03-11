# Travail pratique 1

## Description

This program, written in C language, displays a mountain in ASCII format whose 
concaves are filled with water. You can specify the characters
representing land and water during the display.

The project was achieved in the course *Construction et maintenance de logiciels*.


## Author

Julie Chao-Jung WU


## Operation

#### execution
To generate an executable program, simply enter the command in terminal

    make

Then run the program using the command

    ./tp1 <earth> <water> <height>

where `<earth>` is a representative character of the land, `<water>` is a
character representing water and `<height>` is a sequence of natural numbers 
describing the heights of the mountains, column by column, separated by
commas.

#### example of execution
example input command:

    ./tp1 X E 1,2,4,2,5,1,2,3,1,5,3

output:

    ----XEEEEX-
    --XEXEEEEX-
    --XEXEEXEXX
    -XXXXEXXEXX
    XXXXXXXXXXX
    
#### constraints
* Only 3 arguments are allowed.
* `<earth>` and `<water>` each takes only one character.
* The value of `<height>` must be positive integer between 0 and 15, inclusively.
* The number of `<height>` must be positive integer between 1 and 20, inclusively.

#### make clean
To remove the files generated with the executable, simply enter the command

    make clean


## Project Content

* `tp1.c`: Principal source code file, containing `main` function
* `README.md`: Documentation of this project
* `Makefile`: Supports the calling of `make` and `make clean`
* `.gitignore`: Makes git ignore a.out and *.o files while updating git status
* `.gitlab-ci.yml`: Basic gitlab configuration
* `test.bats`: Tests automatically the exacutable with various scenarios


## References

1. Professor Alexandre Blondin Massé's lecture notes


## Status

This program has passed test.bats on git successfully.

This program runs without warning on malt server successfully.
    
