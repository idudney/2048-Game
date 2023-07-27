#include "GameBoard.h"

// function definitions
GameBoard::GameBoard() noexcept {
    for (int i = 0;i < 4;i++) {
        for (int j = 0;j < 4;j++) {
            board[i][j] = 0;
        }
    }
}

// prints the menu for player
void GameBoard::printMenu(){
    cout << "enter n for a new game"<< endl;
    cout << "enter q to quit" << endl;
    cout << "w: up \ns: down \na: left \nd: right"<< endl;
}
void GameBoard::printWin(){
    cout << "You won! Congratulations!" << endl;
}
void GameBoard::printLose(){
    cout << "You lost! Better luck next time." << endl;
}

// adds a number to the board, will be used every time the player makes a move
void GameBoard::addNum(){
    pair<int,int> pos = generateUnocPos();
    board [pos.first][pos.second] = 2;
}

// makes a blank board, and then adds one number randomly placed, will be called whenever the player wants to play a new game
void GameBoard::newBoard(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            board [i][j] = 0;
        }
    }
    addNum();
}


// prints the board
void GameBoard::printBoard(){
    cout << endl << "|-----------------------|"<< endl;
    for (int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            if (board[i][j] == 0){
                if (j == 0){
                    cout << "|" << setw(5) << left << " " <<  "|";
                }
                else {
                    cout << setw(5) << left << " " << "|";
                }
                if (j == 3){
                    cout << endl << "|-----------------------|"<< endl;
                }
            }
            else{
                if (j == 0){
                    cout << "|" << setw(5) << left << board[i][j] <<  "|";
                }
                else {
                    cout << setw(5) << left << board[i][j] << "|";
                }
                if (j == 3){
                    cout << endl << "|-----------------------|"<< endl;
                }
            }
        }
    }
}

int GameBoard::boardValue(int row, int column) {
    return board[row][column];
}

void GameBoard::setBoardValue(int row, int column, int newValue) {
    board[row][column] = newValue;
}

pair<int,int> GameBoard::generateUnocPos() {
    int occupied = 1, row, column;
    while (occupied){
        // chooses a random unoccupied position from the board
        row = rand() % 4;
        column = rand() % 4;
        if (boardValue(row, column) == 0){
            //if (board[row][column] == 0){
            occupied = 0;
        }
    }
    return make_pair(row, column);
}

// checks if the player lost the game
int GameBoard::didLose() {
    for (int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if (boardValue(i, j) == 0) { // if there is a zero found in the loop, then the player did not lose
                return 0;
            }
        }
    }
    // if the player fills up the board, then they lose
    return 1;
}

// checks if the player won
int GameBoard::didWin() {
    for (int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            if (boardValue(i, j) == 2048) { // if the player hits 2048, they win
                return 1;
            }
        }
    }
    // if none of the values in the array are 2048, the loop in main continues to loop
    return 0;
}

// counts the players score, doesnt count 2's
int GameBoard::countScore() {
    int score = 0;
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            if (boardValue(i, j) > 2){
                score = score + boardValue(i, j);
            }
        }
    }
    cout << score << endl;
    return score;
}

// performs the move that the player makes
void GameBoard::doMove(int direction) {
    int startRow = 0;
    int startColumn = 0;
    int numStepsRow = 1;
    int numStepsColumn = 1;
    int dirRow[] = {1, 0, -1, 0};
    int dirColumn[] = {0, 1, 0, -1};

    
    if (direction == 0) {
        startRow = 3;
        numStepsRow = -1;
    }
    if (direction == 1) {
        startColumn = 3;
        numStepsColumn = -1;
    }
    // sets the move possible to 0, or false
    int movePossible, canAddNum = 0;
    // will move all the pieces over until they hit the edge or hit another number theyre not able to combine with
    do {
        movePossible = 0;
        for (int i = startRow; i >= 0 && i < 4; i += numStepsRow){
            for (int j = startColumn; j >= 0 && j <4; j += numStepsColumn){
                int nextI = i + dirRow[direction];
                int nextJ = j + dirColumn[direction];
                if(boardValue(i, j) && canDoMove(i, j, nextI, nextJ)) {
                    setBoardValue(nextI, nextJ, boardValue(nextI, nextJ) + boardValue(i, j));
                    setBoardValue(i, j, 0);
                    //if the move is able to happen, then movepossible will be changed to true
                    movePossible = canAddNum = 1;
                }
            }
        }
    } while(movePossible);
    if (canAddNum == 1){
        addNum();
    }
}

// checks if a move is possible
bool GameBoard::canDoMove(int row, int column, int nextRow, int nextColumn) {
    if(nextRow < 0 || nextColumn < 0 || nextRow >= 4 || nextColumn >= 4) {
        return false;
    }
    else if (boardValue(row, column) != boardValue(nextRow, nextColumn) && boardValue(nextRow, nextColumn) != 0) {
        return false;
    }
    else
        return true;
}

