/** @file main.c 
 * Includes the entry point of the program and an utility function
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structures.h"
#include "laska.h"

/**
 * Makes the user choose if he wants to play against another player or against the cpu
 * 
 * @return the choice the user has made
 * @retval true the user wants to play against another player
 * @retval false the user wants to play against the cpu
*/
bool choice()
{
    int a;
    printf("Choose the game mode:\n1: 1v1\n2: 1vCpu\n> ");
    scanf("%d", &a);
    if (a == 1)
        return true;
    return false;
}

/**
 * Main entry point of the program
 * @return debug code
*/
int main()
{
    bool player,   /*Identifies the player that is currently playing the turn, false player 1, true player 2*/
        lost,      /*Encodes the current state of the game, false nobody of the players lost, so the game goes on, true someone lost and the game finishes*/
        cpu;       /*Encodes the type of the game, false PvP, true PvCpu */
    cell_t *board; /*Array of cell_t, encodes the board where the game is played*/

    player = 0;
    lost = false;
    cpu = false;
    board = initializeBoard();
    cpu = choice() ? false : true;

    system("clear");
    if (cpu)
    {
        printf("You chose PvCpu\n");
    }
    else
        printf("You chose PvP\n");
    do
    {

        show(board);
        play(board, player, &lost, cpu);
        if (!lost)
            system("clear");
        player = !player;
    } while (!lost);
    freeBoard(board);
    return 0;
}