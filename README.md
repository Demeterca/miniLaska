# MiniLaska

This project is an implementation of a board game called MiniLaska, a simplified version of the game Laska. <br>
Full details of the game are here: http://www.lasca.org/.

## Differences
MiniLaska has some differences from the original laska:
- The game is played on a 7x7 board;
- The height of the tower is limited to three soldiers, if a tower with 3 soldiers captures an enemy soldier the bottom soldier of thwe tower is deleted from the board and substituted with the captured soldier.

## Game Modes
This implementation of MiniLaska has two game modes:
- PvP, where player one and player two play against eachother;
- PvCpu, where player two is substituted by a bot.

The game ends when either player has no more moves available.
