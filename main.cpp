#include <iostream>

struct cell {
    int row;
    int column;
};

enum player {attack, defense};

class Board {
private:
    char board[9][9];

public:
    Board ();
    void init_board ();
    void  print_board ();
    void  print_board_row (int );
    char get_cell(cell);
    void change_cell(cell, char);
};

class UI {
private:



public:
    void print_board (Board&);
    int get_row_coord (char);
    int get_column_coord (int);
    cell choose_piece (Board&, player);
    void move_piece (Board&, player);
};

class Taefl {
private:
    player curent_player;
public:
    Taefl ();
    void game ();
    bool is_end (Board&);
    player get_curent_player ();
    void change_player ();
};

Board::Board () {
    for (int row = 0; row < 9; ++row) {
        for (int column=0; column < 9; ++column) {
            board[row][column]=' ';
        }
    }
}

void Board::init_board () {
    board[0][3]=board[0][4]=board[0][5]='a';
    board[1][4]='a';
    board[2][4]='d';
    board[3][0]='a'; board[3][4]='d'; board[3][8]='a';
    board[4][0]=board[4][1]='a'; board[4][2]=board[4][3]='d';
    board[4][4]='k';
    board[4][5]=board[4][6]='d'; board[4][7]=board[4][8]='a';
    board[5][0]='a'; board[5][4]='d'; board[5][8]='a';
    board[6][4]='d';
    board[7][4]='a';
    board[8][3]=board[8][4]=board[8][5]='a';
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

char Board::get_cell(cell coord){
    return board[coord.row][coord.column];
}

void Board::change_cell(cell coord, char c){
    board[coord.row][coord.column]=c;
}

void UI::print_board (Board& board) {
    std::cout << "  1 2 3 4 5 6 7 8 9" << '\n';
    for (int row = 0; row < 9; ++row){
        std::cout << static_cast<char>(97+row) << ' ';
        board.print_board_row(row);
        std::cout << '\n';
    }
}

int UI::get_row_coord(char row){
    return static_cast<int>(row) - 97;
}

int UI::get_column_coord(int column){
    return column - 1;
}

cell UI::choose_piece (Board& board, player curent_player){
    bool correct_input = false;
    char user_row;
    int user_column;
    cell cell;
    while (!correct_input) {
        std::cout << "Enter a row and column of piece:" << '\n';
        std::cin >> user_row >> user_column;
        cell.row = get_row_coord(user_row);
        cell.column = get_column_coord(user_column);
        switch (board.get_cell(cell)) {
            case ' ':
                std::cout << "Please choose piece" << '\n';
                break;
            case 'a':
                if (curent_player == attack){
                    board.change_cell(cell, 'A');
                    correct_input = true;
                    break;
                } else {
                    std::cout << "Please choose piece of your color" << '\n';
                    break;
                }
            case 'd':
            if (curent_player == defense){
                board.change_cell(cell, 'D');
                correct_input = true;
                break;
            } else {
                std::cout << "Please choose piece of your color" << '\n';
                break;
            }
            case 'k':
            if (curent_player == attack){
                board.change_cell(cell, 'K');
                correct_input = true;
                break;
            } else {
                std::cout << "Please choose piece of your color" << '\n';
                break;
            }
        }
    }
    return cell;
}

void UI::move_piece (Board& board, player curent_player){
    cell start_coord = choose_piece(board, curent_player);
    print_board(board);
    char user_end_row;
    int user_end_column;
    cell end_coord;
    bool correct_input = false;
    char piece = board.get_cell(start_coord);
    while (!correct_input) {
        std::cout << "Enter row and column" << '\n';
        std::cin >> user_end_row >> user_end_column;
        end_coord.row = get_row_coord(user_end_row);
        end_coord.column = get_column_coord(user_end_column);
        if (board.get_cell(end_coord) == ' '){
            switch (piece) {
                case 'K':
                board.change_cell(end_coord, 'k');
                break;
                case 'A':
                board.change_cell(end_coord, 'a');
                break;
                case 'D':
                board.change_cell(end_coord, 'd');
                break;
            }
            board.change_cell(start_coord, ' ');
            correct_input = true;
        } else {
            std::cout << "Please choose free cell" << '\n';
        }
    }
    print_board(board);
}

Taefl::Taefl(){
    curent_player = attack;
}

void Taefl::game() {
    Board board;
    board.init_board();
    UI ui;
    while (!is_end(board)) {
        system("clear");
        ui.print_board(board);
        ui.move_piece(board, curent_player);
        change_player();
    }
}

bool Taefl::is_end (Board& board){
    return false;
}

player Taefl::get_curent_player () {
    return curent_player;
}

void Taefl::change_player () {
    if (curent_player == attack){
        curent_player = defense;
    } else {
        curent_player = attack;
    }
}

int main(int argc, char const *argv[]) {
    Taefl taefl;
    taefl.game();
    return 0;
}
