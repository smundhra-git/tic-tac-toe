#include <array>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int BOARD_SIZE = 3;

// Enum to represent the state of each cell on the Tic-Tac-Toe board
enum class Cell { Empty, Player1, Player2 };

// Class to represent the Tic-Tac-Toe game board
class TicTacToe {
private:
  std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE> board;
  std::mutex mtx;
  std::condition_variable cv;
  int playerTurn;

public:
  TicTacToe() {
    // Initialize the board with empty cells
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        board[i][j] = Cell::Empty;
      }
    }

    playerTurn = 1;
  }

  // Function to make a move on the Tic-Tac-Toe board
  bool makeMove(int player, int x, int y) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this, player] { return playerTurn == player; });
    // Check if the move is valid
    if (board[x][y] == Cell::Empty) {
      // Update the board with the move
      board[x][y] = (player == 1) ? Cell::Player1 : Cell::Player2;
      playerTurn = (playerTurn == 1) ? 2 : 1;
      cv.notify_all();
      return true;
    }
    return false;
  }

  // Function to check if the game is over
  bool gameOver() {
    // Check for a win
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board[i][0] != Cell::Empty && board[i][0] == board[i][1] &&
          board[i][1] == board[i][2]) {
        return true;
      }
      if (board[0][i] != Cell::Empty && board[0][i] == board[1][i] &&
          board[1][i] == board[2][i]) {
        return true;
      }
    }
    if (board[0][0] != Cell::Empty && board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
      return true;
    }
    if (board[2][0] != Cell::Empty && board[2][0] == board[1][1] &&
        board[1][1] == board[0][2]) {
      return true;
    }

    // Check for a draw
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] == Cell::Empty) {
          return false;
        }
      }
    }
    return true;
  }

  // Function to print the current state of the Tic-Tac-Toe board
  void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        switch (board[i][j]) {
        case Cell::Empty:
          std::cout << "   ";
          break;
        case Cell::Player1:
          std::cout << " X ";
          break;
        case Cell::Player2:
          std::cout << " O ";
          break;
        }
        if (j < BOARD_SIZE - 1) {
          std::cout << "|";
        }
      }
      std::cout << std::endl;
      if (i < BOARD_SIZE - 1) {
        std::cout << "---|---|---" << std::endl;
      }
    }
    std::cout << std::endl;
  }

  void printBoardInstruct() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        switch (board[i][j]) {
        case Cell::Empty:
          std::cout << i << " " << j;
          break;
        }
        if (j < BOARD_SIZE - 1) {
          std::cout << "|";
        }
      }
      std::cout << std::endl;
      if (i < BOARD_SIZE - 1) {
        std::cout << "---|---|---" << std::endl;
      }
    }
    std::cout << std::endl;
  }
  int getPlayerTurn() { return playerTurn; }

  void reset() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        board[i][j] = Cell::Empty;
      }
    }
    playerTurn = 1;
  }
  int getWinner() {
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board[i][0] != Cell::Empty && board[i][0] == board[i][1] &&
          board[i][1] == board[i][2]) {
        return (board[i][0] == Cell::Player1) ? 1 : 2;
      }
      if (board[0][i] != Cell::Empty && board[0][i] == board[1][i] &&
          board[1][i] == board[2][i]) {
        return (board[0][i] == Cell::Player1) ? 1 : 2;
      }
    }
    if (board[0][0] != Cell::Empty && board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
      return (board[0][0] == Cell::Player1) ? 1 : 2;
    }
    if (board[2][0] != Cell::Empty && board[2][0] == board[1][1] &&
        board[1][1] == board[0][2]) {
      return (board[2][0] == Cell::Player1) ? 1 : 2;
    }
    return 0;
  }
};

// Function for player 1 to make moves
void player1(TicTacToe &game) {
  while (!game.gameOver()) {
    int x, y;
    std::cout << "Player 1: Enter your move (x y): ";
    std::cin >> x >> y;
    if (game.makeMove(1, x, y)) {
      game.printBoard();
    } else {
      std::cout << "Invalid move! Try again." << std::endl;
    }
  }
}

// Function for player 2 to make moves
void player2(TicTacToe &game) {
  while (!game.gameOver()) {
    int x, y;
    std::cout << "Player 2: Enter your move (x y): ";
    std::cin >> x >> y;
    if (game.makeMove(2, x, y)) {
      game.printBoard();
    } else {
      std::cout << "Invalid move! Try again." << std::endl;
    }
  }
}
