# SudokuSolver
Written September 2016

This project is a sudoku solver. It uses 3 basic logical algorithms to solve the puzzle by either eliminating 
from the array of possible values until it finds only one possible value to go in that cell, finding instances 
where there is only one cell a certain number can go in, or using slightly more complex logic to eliminate
values from cells. If these three algorithms fail to solve the puzzle, then the program will attempt to guess 
a cell by chosing one of its possible values as the "correct" one, then using the first three methods to either 
solve the puzzle or find a contradiction, at which point it will back out any changes it made and attempt to guess
again, with the guessed number eliminated from the possibilities. 
