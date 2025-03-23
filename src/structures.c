#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structures.h"

cell_t getCell(cell_t *b, int x, int y)
{
    return b[EDGE * y + x];
}

soldier_t *getTower(cell_t *b, int x, int y)
{
    return b[EDGE * y + x].tower;
}

coord_t toCoord(int x, int y)
{
    coord_t c;
    c.x = x;
    c.y = y;
    return c;
}

move_t toMove(coord_t s, coord_t f, coord_t c, bool cap)
{
    move_t m;
    m.s = s;
    m.f = f;
    if (cap == 1)
    {
        m.e = c;
        m.eat = true;
    }
    else
    {
        m.eat = false;
        m.e = c;
    }
    return m;
}

void moveContents(cell_t *o, cell_t *t)
{
    int i, c;
    t->height = o->height;
    for (i = 0; i < o->height + 1; i++)
    {
        c = o->tower[i].color;
        t->tower[i].color = c;
        t->tower[i].official = o->tower[i].official;
        o->tower[i].official = false;
        o->tower[i].color = -1;
    }
    o->height = -1;
}

void removeTop(cell_t *o)
{
    int h;
    h = o->height;
    o->tower[h].color = -1;
    o->tower[h].official = false;
    o->height--;
}

void addSoldier(cell_t *t, cell_t o)
{
    int h, i;
    h = t->height;
    for (i = h + 1; i >= 0; i--)
    {
        t->tower[i].color = t->tower[i - 1].color;
        t->tower[i].official = t->tower[i - 1].official;
    }
    t->height++;
    t->tower[0].color = o.tower[o.height].color;
    t->tower[0].official = false;
}

void Promote(cell_t *o)
{
    printf("promote");
    o->tower[o->height].official = true;
}

cell_t *initializeBoard()
{
    cell_t *board;
    int i, j;
    board = (cell_t *)malloc((EDGE * EDGE) * sizeof(cell_t)); /*Initializing the main vector*/
    for (i = 0; i < EDGE; i++)
    {
        for (j = 0; j < EDGE; j++)
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) /*Initalize only the cells where the game is actually played*/
            {
                board[EDGE * i + j].tower = (soldier_t *)malloc(LIM * sizeof(soldier_t)); /*Initializing the cell_t vector (tower)*/
                if (i < 3)
                {
                    board[EDGE * i + j].height = 0;
                    board[EDGE * i + j].tower[0].official = 0;
                    board[EDGE * i + j].tower[0].color = 1;
                    board[EDGE * i + j].tower[1].color = -1;
                    board[EDGE * i + j].tower[2].color = -1;
                }
                else if (i > 3)
                {
                    board[EDGE * i + j].height = 0;
                    board[EDGE * i + j].tower[0].official = 0;
                    board[EDGE * i + j].tower[0].color = 0;
                    board[EDGE * i + j].tower[1].color = -1;
                    board[EDGE * i + j].tower[2].color = -1;
                }
                else
                {
                    board[EDGE * i + j].height = -1;
                    board[EDGE * i + j].tower[0].official = 0;
                    board[EDGE * i + j].tower[0].color = -1;
                    board[EDGE * i + j].tower[1].color = -1;
                    board[EDGE * i + j].tower[2].color = -1;
                }
            }
            else
            {
                /*Cells that will never be used have an height of -1*/
                board[EDGE * i + j].height = -1;
            }
        }
    }
    return board;
}

void show(cell_t *b)
{
    int i, j, k;
    printf("\n   | a | b | c | d | e | f | g |\n---+---+---+---+---+---+---+---+---"); /*prints the column numbers and a separator*/
    for (i = 0; i < EDGE; i++)
    {
        printf("\n %d |", i); /*Prints the row number*/
        for (j = 0; j < EDGE; j++)
        {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) /*Checks if the cell is a "playable cell"*/
            {
                for (k = 0; k < LIM; k++) /*If the cell is playable check the color of or every soldier inside the tower in the cell*/
                {
                    /*If the color is 0, prints a "space" character with a yellow background*/
                    if (getCell(b, j, i).tower[k].color == 0)
                    {
                        if (getCell(b, j, i).tower[k].official == 0)
                            printf("\x1b[43m \x1b[0m");
                        else
                            printf("\x1b[30;43m°\x1b[0m");
                    }
                    /*If the color is 1, prints a "space" character with a red background*/
                    else if (getTower(b, j, i)[k].color == 1)
                    {
                        if (getTower(b, j, i)[k].official == 0)
                            printf("\x1b[41m \x1b[0m");
                        else
                            printf("\x1b[30;41m°\x1b[0m");
                    }
                    /*If the color is -1, prints a "space" character*/
                    else
                        printf(" ");
                }
            }
            /*If the cell is not a playable cell, prints the "space" character three times*/
            else
                printf("   ");
            printf("|");
        }
        printf(" %d", i);
        printf("\n---+---+---+---+---+---+---+---+---");
    }
    printf("\n   | a | b | c | d | e | f | g |   \n");
}

void freeBoard(cell_t *b)
{
    {
        int i, j;
        for (i = 0; i < EDGE; i++)
        {
            for (j = 0; j < EDGE; j++)
            {
                if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
                {
                    /*frees the memory allocated in the soldier_t* tower*/
                    free(b[EDGE * i + j].tower);
                }
            }
        }
        free(b);
    }
}