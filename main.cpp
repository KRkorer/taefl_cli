#include <iostream>


class Taefl {
private:
    /* data */

public:
    Taefl ();

};

class Board {
private:
    char board[9][9];

public:
    Board ();
    void init_board ();
    void  print_board ();
    void  print_board_row (int );
};

class Piece {
private:
    /* data */

public:
    Piece ();
};

class Player {
private:
    /* data */

public:
    Player ();
};

class UI {
private:
    /* data */

public:

    void print_board (Board&);
};

Board::Board () {
    for (int row = 0; row < 9; ++row) {
        for (int column=0; column < 9; ++column) {
            board[row][column]=' ';
        }
    }
}

void Board::init_board () {
    board[0][3]=board[0][4]=board[0][5]='b';
    board[1][4]='b';
    board[2][4]='b';
    board[3][0]='b'; board[3][4]='w'; board[3][8]='b';
    board[4][0]=board[4][1]='b'; board[4][2]=board[4][3]='w';
    board[4][4]='k';
    board[4][5]=board[4][6]='w'; board[4][7]=board[4][8]='b';
    board[5][0]='b'; board[5][4]='w'; board[5][8]='b';
    board[6][4]='b';
    board[7][4]='b';
    board[8][3]=board[8][4]=board[8][5]='b';
}

void Board::print_board () {
    for (int row = 0; row < 9; ++row) {
        for (int column=0; column < 9; ++column) {
            std::cout << board[row][column];
        }
        std::cout << '\n';
    }
}

void Board::print_board_row (int row) {
    for (int column = 0; column < 9; ++column){
        std::cout << board[row][column] << ' ';
    }
}


void UI::print_board (Board& board) {
    std::cout << "  1 2 3 4 5 6 7 8 9" << '\n';
    for (int row = 0; row < 9; ++row){
        std::cout << static_cast<char>(97+row) << ' ';
        board.print_board_row(row);
        std::cout << '\n';
    }
}


int main(int argc, char const *argv[]) {
    Board myboard;
    myboard.init_board();
    UI myui;
    myui.print_board(myboard);
    return 0;
}
