#include <iostream>
#include <iomanip>
#include <array> 
using namespace std;
class GameBoard {
  public:
    void printMenu();
    void printWin();
    void printLose();
    void newBoard();
    void printBoard();
    int boardValue(int, int);
    void setBoardValue(int, int, int);
    GameBoard() noexcept;
    void addNum();
    // checks if the player lost the game
    int didLose();
    int didWin();
    int countScore();
    void doMove(int direction);
    bool canDoMove(int row, int column, int nextRow, int nextColumn);

protected:
    // generates a random unoccupied position for a number to be placed in
    pair<int,int> generateUnocPos();

    
  private:
    int board[4][4];
    char playToDir[128];
    int dirRow[4];
    int dirColumn[4];
};
