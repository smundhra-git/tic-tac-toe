#include <iostream>
#include "functions.h"

using namespace std;

int main() {
  TicTacToe game;
  cout << "Position name for reference: " << endl;
  game.printBoardInstruct();
  while (true) {
    int x, y;
    while (!game.gameOver()) {
      cout << "Player " << game.getPlayerTurn() << " turn. Enter x y: ";
      cin >> x >> y;
      if (cin.fail() || x < 0 || x > 2 || y < 0 || y > 2) {
        cout << "Invalid input. Try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } 
      else if (!game.makeMove(game.getPlayerTurn(), x, y)) {
        cout << "Invalid move. Try again." << endl;
      } 
      else {
        game.printBoard();
      }
    }
    cout << "Game over. " << endl;
    int winner = game.getWinner();
    if (winner == 0) {
      cout << "It's a draw." << endl;
    } 
    else {
      cout << "Player " << winner << " wins!" << endl;
    }
    char playAgain;
    cout << "Do you want to play again? (y/n) ";
    cin >> playAgain;
    if (playAgain == 'n') {
      break;
    }
    game.reset();
  }

  return 0;
}
