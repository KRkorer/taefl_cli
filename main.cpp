#include <iostream>
#include <cmath>

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
    char get_cell (cell);
    void change_cell (cell, char);
    cell get_king_cell ();
    void del_piece (cell);
};

class UI {
private:

public:
    void print_board (Board&);
    int get_row_coord (char);
    int get_column_coord (int);
    cell input ();
    void choose_piece (Board&, cell);
    void move_piece (Board&, cell, cell);
};

class Taefl {
private:
    player curent_player;
public:
    Taefl ();
    void game ();
    bool is_defense_win (Board&);
    bool is_attack_win (Board&);
    player get_curent_player ();
    void change_player ();
    bool is_choose_correct (Board&, cell, player);
    bool is_move_correct (Board&, cell, cell);
    void eat_pieces (Board&);
};

bool operator== (const cell& lhs, const cell& rhs) {
 if ((lhs.row == rhs.row) and (lhs.column == rhs.column)){
     return true;
 }
 return false;
}

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

char Board::get_cell (cell coord){
    return board[coord.row][coord.column];
}

void Board::change_cell (cell coord, char c){
    board[coord.row][coord.column]=c;
}

cell Board::get_king_cell (){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 'k'){
                return cell{i, j};
            }
        }
    }
    return cell {-1, -1};
}

void Board::del_piece(cell cell) {
    change_cell(cell, ' ');
}

void UI::print_board (Board& board) {
    std::cout << "  1 2 3 4 5 6 7 8 9" << '\n';
    for (int row = 0; row < 9; ++row){
        std::cout << static_cast<char>(97+row) << ' ';
        board.print_board_row(row);
        std::cout << '\n';
    }
}

int UI::get_row_coord (char row){
    return static_cast<int>(row) - 97;
}

int UI::get_column_coord (int column){
    return column - 1;
}

 cell UI::input () {
    std::cout << "Enter a row and column" << '\n';
    char row;
    int column;
    std::cin >> row >> column;
    return cell {get_row_coord(row), get_column_coord(column)};
}

void UI::choose_piece (Board& board, cell cell){
    switch (board.get_cell(cell)) {
        case 'a':
        board.change_cell(cell, 'A');
        break;
        case 'd':
        board.change_cell(cell, 'D');
        break;
        case 'k':
        board.change_cell(cell, 'K');
        break;
    }
}

void UI::move_piece (Board& board, cell begin, cell end){
    switch (board.get_cell(begin)) {
        case 'A':
        board.change_cell(end, 'a');
        break;
        case 'D':
        board.change_cell(end, 'd');
        break;
        case 'K':
        board.change_cell(end, 'k');
        break;
    }
    board.del_piece(begin);
}

Taefl::Taefl (){
    curent_player = attack;
}

void Taefl::game () {
    Board board;
    board.init_board();
    UI ui;
    cell begin, end;
    while (!((is_defense_win(board)) or (is_attack_win(board)))) {
        system("clear");
        ui.print_board(board);

        do {
            std::cout << "Choose piece" << '\n';
            begin = ui.input();
        } while (!is_choose_correct(board, begin, curent_player));
        ui.choose_piece(board, begin);
        system("clear");
        ui.print_board(board);

        do {
            std::cout << "Choose destination point" << '\n';
            end = ui.input();
        } while (!is_move_correct(board, begin, end));

        ui.move_piece(board, begin, end);

        eat_pieces(board);

        change_player();

        system("clear");
    }
    switch (curent_player) {
        case attack:
        std::cout << "Defense win" << '\n';
        break;
        case defense:
        std::cout << "Attack win" << '\n';
    }
}

bool Taefl::is_defense_win (Board& board){
    cell king = board.get_king_cell();
    if ((king.row == 0) and (king.row == 8) and
        (king.column == 0) and (king.column == 8)) {
        return true;
    }
    return false;
}

bool Taefl::is_attack_win (Board& board){
    cell king = board.get_king_cell();
    if ((king.row > 0) and (king.row < 8) and
        (king.column > 0) and (king.column < 8)) {
        char up = board.get_cell(cell {king.row - 1, king.column});
        char left = board.get_cell(cell {king.row, king.column - 1});
        char right = board.get_cell(cell {king.row, king.column + 1});
        char down = board.get_cell(cell {king.row + 1, king.column});
        if ((up == 'a') and (left == 'a')
            and (right == 'a') and (down == 'a')) {
            return true;
        }
    }
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

bool Taefl::is_choose_correct (Board& board, cell cell, player curent_player){
    switch (curent_player) {
        case attack:
        if (board.get_cell(cell) == 'a'){
            return true;
        }
        break;
        case defense:
        if ((board.get_cell(cell) == 'd') or (board.get_cell(cell) == 'k')) {
            return true;
        }
        break;
    }
    return false;
}

bool Taefl::is_move_correct (Board& board, cell begin, cell end) {
    if (board.get_cell(end) == ' '){
        if (begin.row == end.row) {
            for (int i = 1; i < abs(end.column-begin.column); ++i) {
                if (board.get_cell(cell {begin.row, begin.column + i}) != ' ') {
                    return false;
                }
            }
            return true;
        }
        if (begin.column == end.column) {
            for (int i = 1; i < abs(end.row-begin.row); ++i) {
                if (board.get_cell(cell {begin.row+i, begin.column}) != ' ') {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void Taefl::eat_pieces(Board& board) {
    //To Do
}

int main (int argc, char const *argv[]) {
    Taefl taefl;
    taefl.game();
    return 0;
}
