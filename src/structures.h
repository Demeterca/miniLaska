/** @file structures.h
 * Defines all the structures and constants used in the program and their base functions
 * 
 */
#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#endif

#define EDGE 7 /**<Sets the max width and height of the board*/
#define LIM 3  /**<Sets the max height of a tower*/

/**
 * Encodes the structure of the piece (soldier) used within the game.
*/
typedef struct
{
    bool official; /**<Indicates whether the soldier is an official or not, true if an officer, false otherwise*/
    int color;     /**<Indicates the "color" of the soldier, 0 (player 1) is yellow, 1 (player 2) is red, -1 is an empty position*/
} soldier_t;

/**
 * Encodes the structure of the tower inside the cell.
*/
typedef struct
{
    int height;       /**<Indicates the number of soldiers inside the tower, used as an index for tower so height == -1 means the tower is empty, height == 0 means there is one soldier and so on, different from LIM, that is the max height of the tower*/
    soldier_t *tower; /**<Array of soldier_t with LIM capacity*/
} cell_t;

/**
 * Structure used to manage coordinates. the x,y pair identifies a specific cell in the board.
*/
typedef struct
{
    int x; /**<Value of the x axis*/
    int y; /**<Value of the y axis*/
} coord_t;

/**
 * Structure used to store al information concerning a particular move.
*/
typedef struct
{
    coord_t s; /**<Coordinates of the cell where the tower to move is located */
    coord_t f; /**<Coordinates of the cell where the tower has to be moved*/
    coord_t e; /**<Coordinates of the cell where a capture has to be performed, for a standard move, e.x,e.y is set to -1*/
    bool eat;  /**<Indicates if a capture has to be performed*/
} move_t;

/**
 * Structure used to store all the moves that can be made in a specific turn.
*/
typedef struct
{
    move_t *moves; /**<Array of move_t*/
    int n_moves;   /**<Number of moves currently stored, it's used as an index for the array so n_moves == -1 means 0 moves are stored, n_moves == 0 means 1 move is stored and so on*/
} moves_t;

/**
 * Returns the cell at specific coordinates. 
 * Formula: EDGE * y + x
 * @param b the board where the game is played
 * @param x value of the x axis
 * @param y value of the y axis
 * @return cell at given coordinates
 */
cell_t getCell(cell_t *b, int x, int y);

/**
 * Returns the tower inside a cell at specific coordinates. 
 * Formula: EDGE * y + x
 * @param b the board where the game is played
 * @param x value of the x axis
 * @param y value of the y axis
 * @return tower at given coordinates
 */
soldier_t *getTower(cell_t *b, int x, int y);

/**
 * Creates coordinates (coord_t) based on Input
 * 
 * @param x value of the x axis
 * @param y value of the y axis
*/
coord_t toCoord(int x, int y);

/**
 * Creates a move (move_t) based on inputs
 * 
 * @param s coordinates of the starting position
 * @param f coordinates of the position after the move
 * @param c coordinates of the position where the soldier to capture is located, for a standard move, c.x,c.y is set to -1
 * @param cap flag used to define if a move expects a capture
*/
move_t toMove(coord_t s, coord_t f,coord_t c, bool cap);

/**
 * Copies the contents of the source cell on the target cell, deletes the contents from the source cell
 * @param o source cell
 * @param t target cell
 */
void moveContents(cell_t *o, cell_t *t);

/**
 * Removes the soldier at the top the tower inside a given cell
 * @param o cell where the tower is located
*/
void removeTop(cell_t *o);

/**
 * Adds the soldier at the top of the tower inside the source cell to the bottom of the tower inside the target cell
 * @param t target cell 
 * @param o source cell
*/
void addSoldier(cell_t *t, cell_t o);

/**
 * Promotes to official the soldier at the top of the tower inside the source cell
 * @param o source cell
*/
void Promote(cell_t *o);

/**
 * Initializes the Board
 * @return pointer to the created board
 */
cell_t *initializeBoard();

/**
 * Prints the board and all its contents following the style and colors of a laska board
 * @param b board to print
*/
void show(cell_t *b);

/**
 * Frees the memory previously allocated by the initialize() function
 * 
 * @param b cell_t* of wich the contents have to be freed
*/
void freeBoard(cell_t *b);