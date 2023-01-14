This is a simple Tic-Tac-Toe game implemented in C++. The game is played on a 3x3 board and supports two players.

How to Run

To run the game, compile the code and run the executable. The game will start with player 1's turn and will continue until a win or draw is detected.

Class Overview

TicTacToe: This class represents the Tic-Tac-Toe game board and contains the logic for the game.
makeMove(int player, int x, int y): Function to make a move on the Tic-Tac-Toe board
gameOver(): Function to check if the game is over
printBoard(): Function to print the current state of the Tic-Tac-Toe board
Cell: Enum to represent the state of each cell on the Tic-Tac-Toe board. Each cell can be either Empty, Player1, or Player2.
Dependencies

This project uses the following libraries:

<array>: C++ standard container for fixed-size arrays
<chrono>: C++ standard library for time manipulation
<condition_variable>: C++ standard library for waiting for and notifying about events
<iostream>: C++ standard library for input/output operations
<mutex>: C++ standard library for mutual exclusion
<thread>: C++ standard library for multi-threading
Note

This is a simple Tic-Tac-Toe implementation and is not intended for production use. It has been written for educational purposes and as a starting point for further development.
