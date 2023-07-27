// Isabel Dudney, CSC 160-040, Final Project Final Compiled Source Code, May 8th 2022

#include <iostream>

#include <algorithm>
// these two are used so we can generate a random number, I know we did not learn this in class but I needed it so I did my own research on how to do this
#include <ctime>
#include <cstdlib>

// our class files
#include "GameBoard.h"

using namespace std;

// main function
int main() {
    GameBoard board;
    srand(time(0));
    
    // creates an array to store the value of the players move
    char playToDir[128];
    // sets the players move to a int instead of a char
    playToDir['s'] = 0;
    playToDir['d'] = 1;
    playToDir['w'] = 2;
    playToDir['a'] = 3;
    // prints the menu
    board.printMenu();
    // an infinite loop for our game to run
    while (true){
        char move;
        cin >> move;
        if (move == 'n'){
            // generates a new blank board, if the player wishes to start a new game
            board.newBoard();
        }
        if (move == 'q'){
            // ends the program if the player wants to quit
            break;
        }
        else {
            // sets the current direction to the players move, so we can use it in our do move member function
            int currentDirection = playToDir[move];
            board.doMove(currentDirection);
            board.printBoard();
            // checks if the player has won after every move
            if (board.didWin() == 1){
                board.printWin();
                break;
            }
            // checks if the player has lost after every move
            if (board.didLose() == 1){
                board.printLose();
                break;
            }
        }
        cout << "Player score: "<< endl;
        board.countScore();
    }
}
