/** @file laska.h
 * Defines all the functions used the in game's logic
 * 
*/
#ifndef ADD_H
#define ADD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "structures.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#endif

/**
 * Fills the moves array with all the possible moves a single tower in a specfific cell can make
 * @param b board where the tower is located
 * @param t identifies the current player
 * @param m current possible moves
 * @param c coordinates of the cell where the tower is located
 */
void getMoves(cell_t *b, bool t, moves_t *m, coord_t c);

/**
 * Returns the letter corresponding to the given number 
 * @param n number
 * @return corresponding letter
 */
char getAlpha(int n);

/**
 * Prints all the moves a player can make in that specific turn, if there are one or more moves where a capture is possible prints only those specific moves 
 * @param m all possible moves that turn
 * @param t identifies the current player
 */
void printMoves(moves_t m, bool t);

/**
 * Executes a move on a given board
 * @param b board where the match is played
 * @param m move to execute
 * @param t identifies the current player
*/
void executeMove(cell_t *b, move_t m, bool t);

/**
 * makes the player select the move he intends to make from all possible moves, if are present one or more moves where captures are possible, the selection is restricted to only this specific moves
 * @param m current possible moves
*/
move_t selectMove(moves_t m);

/**
 * Selects a random move from all the possible moves that turn, if one or more moves where capture is possible are present, the first one is selected, otherwise the selection will be random
 * @param m all current moves
*/
move_t cpuMove(moves_t m);

/**
 * Sets up and manages the turn, if losing conditions are met, changes the match lost flag to true
 * @param b board where the match is played
 * @param t identifies the current player
 * @param l match lost flag
 * @param cpu pvp or pve flag
*/
void play(cell_t *b, bool t, bool *l, bool cpu);
