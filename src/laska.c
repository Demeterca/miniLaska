#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "structures.h"

void getMoves(cell_t *b, bool t, moves_t *m, coord_t c)
{
    int h, d;

    if (t == 0) /* sets the direction on which a tower should move based on current turn*/
    {
        d = -1; /*-1 if it's player's 1 turn*/
    }
    else
        d = 1; /*1 if it's player's 2 turn*/

    h = getCell(b, c.x, c.y).height;
    if (getTower(b, c.x, c.y)[h].official == true) /*Checks if a tower is controlled by an official*/
    {
        d = -1;
        while (d <= 1) /*The code to find all the moves is repeated 2 times with d == -1 and d == 1 because an official can move in all directions*/
        {
            /*Checks if a tower can perform a move to y+d,x+d direction*/
            if (c.y + d < EDGE && c.x + d < EDGE && (c.y + d >= 0) && (c.x + d >= 0) && (c.y + d != -1) && (c.y + d != EDGE) && (c.x + d > -1) && (c.x + d < EDGE)) /*Checks if the tower goes out of bounds while performing a normal move*/
            {
                if (getCell(b, c.x + d, c.y + d).height == -1)
                {
                    /*Creates a move and adds it to the moves array*/
                    m->n_moves++;
                    m->moves[m->n_moves] = toMove(c, toCoord(c.x + d, c.y + d), toCoord(-1, -1), false);
                }
                /*Checks if a tower can perform a move to y+(d*2),x+(d*2) direction*/
                else if (getTower(b, c.x + d, c.y + d)[getCell(b, c.x + d, c.y + d).height].color == !t && ((c.y + (2 * d) < EDGE)) && (c.x + (2 * d) > -1) && (c.x + (2 * d) < EDGE)) /*Checks if the tower goes out of bounds while performing a move with capture*/
                {

                    if (getCell(b, c.x + (2 * d), c.y + (2 * d)).height == -1)
                    {
                        /*Creates a move and adds it to the moves array*/
                        m->n_moves++;
                        m->moves[m->n_moves] = toMove(c, toCoord(c.x + 2 * d, c.y + 2 * d), toCoord(c.x + d, c.y + d), true);
                    }
                }
            }
            /*Checks if a tower can perform a move to y+d,x-d direction*/
            if (c.y + d < EDGE && c.x - d < EDGE && c.y + d >= 0 && c.x - d >= 0 && (c.y + d != -1) && (c.y + d != EDGE) && (c.x - d > -1) && (c.x - d < EDGE)) /*Checks if the tower goes out of bounds while performing a normal move*/
            {
                if (getCell(b, c.x - d, c.y + d).height == -1)
                {
                    /*Creates a move and adds it to the moves array*/
                    m->n_moves++;
                    m->moves[m->n_moves] = toMove(c, toCoord(c.x - d, c.y + d), toCoord(-1, -1), false);
                }
                /*Checks if a tower can perform a move to y+(d*2),x-(d*2) direction*/
                else if (getTower(b, c.x - d, c.y + d)[getCell(b, c.x - d, c.y + d).height].color == !t && ((c.y + (2 * d) < EDGE)) && (c.x - (2 * d) > -1) && (c.x - (2 * d) < EDGE)) /*Checks if the tower goes out of bounds while performing a move with capture*/
                {
                    if (getCell(b, c.x - (2 * d), c.y + (2 * d)).height == -1)
                    {
                        /*Creates a move and adds it to the moves array*/
                        m->n_moves++;
                        m->moves[m->n_moves] = toMove(c, toCoord(c.x - 2 * d, c.y + 2 * d), toCoord(c.x - d, c.y + d), true);
                    }
                }
            }
            d = d + 2;
        }
    }
    /*Finds all the possible moves a soldier can make in the d direction that specific turn*/
    else
    {
        if (c.y + d < EDGE && c.x + d < EDGE && c.y + d >= 0 && c.x + d >= 0 && (c.x != (EDGE - 1) * t + (EDGE - 1) - 6) && (c.y + d != -1) && (c.y + d != EDGE) && (c.x + d > -1) && (c.x + d < EDGE)) /*Checks if the tower goes out of bounds while performing a normal move*/
        {
            if (getCell(b, c.x + d, c.y + d).height == -1)
            {
                /*Creates a move and adds it to the moves array*/
                m->n_moves++;
                m->moves[m->n_moves] = toMove(c, toCoord(c.x + d, c.y + d), toCoord(-1, -1), false);
            }
            else if (getTower(b, c.x + d, c.y + d)[getCell(b, c.x + d, c.y + d).height].color == !t && ((c.y + (2 * d) < EDGE)) && (c.x + (2 * d) > -1) && (c.x + (2 * d) < EDGE)) /*Checks if the tower goes out of bounds while performing a move with capture*/
            {

                if (getCell(b, c.x + (2 * d), c.y + (2 * d)).height == -1)
                {
                    /*Creates a move and adds it to the moves array*/
                    m->n_moves++;
                    m->moves[m->n_moves] = toMove(c, toCoord(c.x + 2 * d, c.y + 2 * d), toCoord(c.x + d, c.y + d), true);
                }
            }
        }
        if (c.y + d < EDGE && c.x - d < EDGE && c.y + d >= 0 && c.x - d >= 0 && (c.x != (EDGE - 1) * (-t) + (EDGE - 1)) && (c.y + d != -1) && (c.y + d != EDGE) && (c.x - d > -1) && (c.x - d < EDGE)) /*Checks if the tower goes out of bounds while performing a normal move*/
        {
            if (getCell(b, c.x - d, c.y + d).height == -1)
            {
                /*Creates a move and adds it to the moves array*/
                m->n_moves++;
                m->moves[m->n_moves] = toMove(c, toCoord(c.x - d, c.y + d), toCoord(-1, -1), false);
            }
            else if (getTower(b, c.x - d, c.y + d)[getCell(b, c.x - d, c.y + d).height].color == !t && (c.y + (2 * d) > -1) && ((c.y + (2 * d) < EDGE)) && (c.x - (2 * d) > -1) && (c.x - (2 * d) < EDGE)) /*Checks if the tower goes out of bounds while performing a move with capture*/
            {
                if (getCell(b, c.x - (2 * d), c.y + (2 * d)).height == -1)
                {
                    /*Creates a move and adds it to the moves array*/
                    m->n_moves++;
                    m->moves[m->n_moves] = toMove(c, toCoord(c.x - 2 * d, c.y + 2 * d), toCoord(c.x - d, c.y + d), true);
                }
            }
        }
    }
}

char getAlpha(int n)
{
    switch (n)
    {
    case 0:
        return 'a';
    case 1:
        return 'b';
    case 2:
        return 'c';
    case 3:
        return 'd';
    case 4:
        return 'e';
    case 5:
        return 'f';
    case 6:
        return 'g';
    default:
        return 'n';
    }
}

void printMoves(moves_t m, bool t)
{
    int i, j, count = 0;
    bool flag = false;

    for (j = 0; j < m.n_moves + 1; j++) /*Checks if one or more moves with capture are present in the moves array, changes the flag accordingly*/
    {
        if (m.moves[j].eat == true)
        {
            flag = true;
            count++;
        }
    }

    if (flag == false)
    {
        /*If there are no moves with capture, prints all the mosses */
        printf("\nAvailable moves for player %d: %d\n", t + 1, m.n_moves + 1);
        for (i = 0; i < m.n_moves + 1; i++)
        {
            printf("%d - from: %c%d; to %c%d\n", i + 1, getAlpha(m.moves[i].s.x), m.moves[i].s.y, getAlpha(m.moves[i].f.x),
                   m.moves[i].f.y);
        }
    }
    else
    {
        /*If there are moves with capture, prints only those*/
        j = 0;
        printf("\nAvailable moves for player %d: %d\n", t + 1, count);
        for (i = 0; i < m.n_moves + 1; i++)
        {
            if (m.moves[i].eat == true)
            {
                printf("%d - from: %c%d; to %c%d\n", j + 1, getAlpha(m.moves[i].s.x), m.moves[i].s.y, getAlpha(m.moves[i].f.x),
                       m.moves[i].f.y);
                j++;
            }
        }
    }
}

void executeMove(cell_t *b, move_t m, bool t)
{
    int h;
    moveContents(&b[EDGE * m.s.y + m.s.x], &b[EDGE * m.f.y + m.f.x]);
    if (m.eat == true) /*Checks if the move results in a capture*/
    {
        if (getCell(b, m.f.x, m.f.y).height < LIM - 1) /*Checks the height of the tower at the destination */
        {
            addSoldier(&b[EDGE * m.f.y + m.f.x], getCell(b, m.e.x, m.e.y)); /*if the height of the tower is less than LIM-1 adds a soldier*/
        }
        else
        {
            h = getCell(b, m.e.x, m.e.y).height;
            if (getTower(b, m.f.x, m.f.y)[0].color != getTower(b, m.e.x, m.e.y)[h].color) /*if the height of the tower is LIM - 1 (max height) checks if the color of the bottom soldier is different from the one the captured soldier*/
                getTower(b, m.f.x, m.f.y)[0].color = getTower(b, m.e.x, m.e.y)[h].color;  /*if the color is different changes the color of the bottom soldier to the one of the captured soldier */
        }
        removeTop(&b[EDGE * m.e.y + m.e.x]); /*Removes the captured soldier from its tower*/
    }
    if (t == 0) /*Based on the current player, promotes the soldier if it is arrived at the end of the board*/
    {
        if (m.f.y == 0)
            Promote(&b[EDGE * m.f.y + m.f.x]);
    }
    else if (m.f.y == EDGE - 1)
        Promote(&b[EDGE * m.f.y + m.f.x]);
}

move_t selectMove(moves_t m)
{
    int arr[6] = {0, 0, 0, 0, 0, 0}; /*Creates a support array with capacity = 6, an arbitrary number so the array can contain as much moves as needed*/
    int j, 
        count, /*Counter used to save the number of the possible moves with capture*/
        nm;
    bool ok;
    ok = false; /*Flag used to know if input is valid*/
    count = 0;

    for (j = 0; j < m.n_moves + 1; j++) /*Scrolls the moves array*/
    {
        if (m.moves[j].eat == true) /*finds a move where a capture is possible*/
        {
            arr[count] = j; /*Adds the current value of j (the index of a capture inside m.moves array) to the support array*/
            count++;
        }
    }

    printf("Please select the move you want to make (choose wisely): ");
    while (ok != true) /*Repeats until ivalid input is recieved*/
    {
        nm = 0;
        scanf("%d", &nm); /*Recieves input from the player*/

        if (count > 0) /*Check if captures are possible*/
        {
            if (nm - 1 <= count - 1 && nm - 1 >= 0) /*If captures are possible, checks if the value recieved on input corresponds to a move*/
            {
                ok = true; /*If input corresponds to a move sets the flag to true*/
            }
            else
            {
                printf("Write a NUMBER from %d to %d, please: ", count + 1 - count, count); /*If input is invalid checks asks the user to input a valid number*/
                while ((nm = getchar()) != '\n' && nm != EOF); /*prevents a program malfunction if something other than a character is recieved on input*/
            }
        }
        else
        {
            if (nm - 1 <= m.n_moves && nm - 1 >= 0) /*Checks if the value recieved on input corresponds to a move*/
            {

                ok = true; /*If input corresponds to a move sets the flag to true*/
            }
            else
            {
                printf("Write a NUMBER from %d to %d, please: ", m.n_moves + 1 - m.n_moves, m.n_moves + 1); /*If input is invalid checks asks the user to input a valid number*/
                while ((nm = getchar()) != '\n' && nm != EOF); /*prevents a program malfunction if something other than a character is recieved on input*/
            }
        }
    }
    if (count == 0)
        return m.moves[nm - 1]; /*if captures are not possible returns the move at nm-1 position of the m.moves array*/
    else
        return m.moves[arr[nm - 1]]; /*if captures are possible returns the move at arr[nm-1] position of the m.moves array*/
}

move_t cpuMove(moves_t m)
{
    int j;

    printf("\nCpu is making it's move...");
    fflush(stdout);
    for (j = 0; j < m.n_moves + 1; j++) /*Scrolls the moves array, if a move where a capture is possible, the move is selected*/
    {
        if (m.moves[j].eat == true)
        {
            sleep(1.7);
            return m.moves[j];
        }
    }
    sleep(1.7);
    srand((unsigned)time(NULL)); /*rand() function initialization*/
    if (m.n_moves == 0)
        return m.moves[0]; /*If there is only one move possible, that move is selected*/
    else
        return m.moves[rand() % m.n_moves + 1]; /*If two or more moves are possible, selects a random one*/
}

void play(cell_t *b, bool t, bool *l, bool cpu)
{
    int i, j, h;
    move_t move;
    moves_t moves;
    moves.n_moves = -1;                                  /*sets n_moves to -1 this means there are non moves insidew the moves array*/
    moves.moves = (move_t *)malloc(30 * sizeof(move_t)); /*Allocates the memory for a moves with capacity = 30, an arbitrary number so the array can contain as much moves as needed*/
    /*Scrolls all the board*/
    for (i = 0; i < EDGE; i++)
    {
        for (j = 0; j < EDGE; j++)
        {
            /*If there are one or more soldiers in a tower checks if the top one is controlled by the player*/
            h = getCell(b, j, i).height;
            if (h >= 0)
            {
                if (getTower(b, j, i)[h].color == t)
                {
                    /*If the soldier is controlled by the player, calls the getMoves() function for the cell where the tower is located*/
                    coord_t s;
                    s.y = i;
                    s.x = j;
                    getMoves(b, t, &moves, s);
                }
            }
        }
    }

    if (moves.n_moves >= 0) /*Checks if the player has some moves left, if it has makes the player select a move*/
    {
        if ((cpu == false) || ((cpu == true) && t == 0)) /*if the game mode is PvP calls the selectMove() function*/
        {
            printMoves(moves, t);
            move = selectMove(moves);
            executeMove(b, move, t);
        }
        else if (cpu == true && t == 1) /*if the game mode is PvCpu calls the cpuMove() function*/
        {
            /*printMoves(moves, t);*/
            move = cpuMove(moves);
            executeMove(b, move, t);
        }
    }
    else /*If the player can't do any moves sets the game lost flag to true to end the game*/
    {
        *l = true;
        printf("\nPlayer %d lost", t + 1);
    }
    free(moves.moves);
    printf("\n");
}
