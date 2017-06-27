# SudokuSolver
September 2016
Side project

This project is a sudoku solver. It uses 3 basic logical algorithms to solve the puzzle by either eliminating 
from the array of possible values until it finds only one possible value to go in that cell, finding instances 
where there is only one cell a certain number can go in, or using slightly more complex logic to eliminate
values from cells. If these three algorithms fail to solve the puzzle, then the program will attempt to guess 
a cell by chosing one of its possible values as the "correct" one, then using the first three methods to either 
solve the puzzle or find a contradiction, at which point it will back out any changes it made and attempt to guess
again, with the guessed number eliminated from the possibilities. 

The puzzle.txt file is the file that the program reads to find its puzzle to solve. It expects 9 lines of 9 characters
each. The characters should be numbers in the range 0-9. This corresponds to a sudoku puzzle, reading the numbers left 
to right, top to bottom, substituting 0 for any blank (unsolved) cell. It will crash if this file does not follow this 
format.

In puzzles.txt, you will find more puzzles that it can solve, already in the correct formating, with labels for the 
difficulty level. 
