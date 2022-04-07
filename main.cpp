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
    char get_piece (cell);
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

bool operator!= (const cell& lhs, const cell& rhs) {
 if ((lhs.row == rhs.row) and (lhs.column == rhs.column)){
     return false;
 }
 return true;
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

char Board::get_piece (cell coord){
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
    switch (board.get_piece(cell)) {
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
    switch (board.get_piece(begin)) {
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
        char up = board.get_piece(cell {king.row - 1, king.column});
        char left = board.get_piece(cell {king.row, king.column - 1});
        char right = board.get_piece(cell {king.row, king.column + 1});
        char down = board.get_piece(cell {king.row + 1, king.column});
        if ((up == 'a') and (left == 'a') and
        (right == 'a') and (down == 'a')) {
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
        if (board.get_piece(cell) == 'a'){
            return true;
        }
        break;
        case defense:
        if ((board.get_piece(cell) == 'd') or (board.get_piece(cell) == 'k')) {
            return true;
        }
        break;
    }
    return false;
}

bool Taefl::is_move_correct (Board& board, cell begin, cell end) {
    switch (board.get_piece(begin)) {
        case 'A':
        if ((board.get_piece(end) == ' ' and begin != cell {4, 4})){
            if (begin.row == end.row) {
                for (int i = 1; i < abs(end.column-begin.column); ++i) {
                    if (end.column > begin.column) {
                        if (board.get_piece(cell {begin.row, begin.column + i}) != ' ') {
                            return false;
                        }
                    } else {
                        if (board.get_piece(cell {begin.row, begin.column - i}) != ' ') {
                            return false;
                        }
                    }
                }
                return true;
            }
            if (begin.column == end.column) {
                for (int i = 1; i < abs(end.row-begin.row); ++i) {
                    if (end.row > begin.row) {
                        if (board.get_piece(cell {begin.row - i, begin.column}) != ' ') {
                            return false;
                        }
                    } else {
                        if (board.get_piece(cell {begin.row - i, begin.column}) != ' ') {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
        break;
        default :
        if (board.get_piece(end) == ' '){
            if (begin.row == end.row) {
                for (int i = 1; i < abs(end.column-begin.column); ++i) {
                    if (end.column > begin.column) {
                        if (board.get_piece(cell {begin.row, begin.column + i}) != ' ') {
                            return false;
                        }
                    } else {
                        if (board.get_piece(cell {begin.row, begin.column - i}) != ' ') {
                            return false;
                        }
                    }
                }
                return true;
            }
            if (begin.column == end.column) {
                for (int i = 1; i < abs(end.row-begin.row); ++i) {
                    if (end.row > begin.row) {
                        if (board.get_piece(cell {begin.row - i, begin.column}) != ' ') {
                            return false;
                        }
                    } else {
                        if (board.get_piece(cell {begin.row - i, begin.column}) != ' ') {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
        break;
    }
    return false;
}

void Taefl::eat_pieces(Board& board) {
    char curent_piece;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            curent_piece = board.get_piece (cell {i, j});
            if ((i > 0) and (i < 8) and (j > 0) and (j < 8)) {
                switch (curent_piece) {
                    case 'd':
                    if ((board.get_piece(cell {i - 1, j}) == 'a') and
                    (board.get_piece(cell {i, j - 1}) == 'a') and
                    (board.get_piece(cell {i, j + 1}) == 'a') and
                    (board.get_piece(cell {i + 1, j}) == 'a')) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if (i == 0) {
                switch (curent_piece) {
                    case 'd':
                    if ((board.get_piece(cell {i, j - 1}) == 'a') and
                    (board.get_piece(cell {i, j + 1}) == 'a') and
                    (board.get_piece(cell {i + 1, j}) == 'a')) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if (i == 8){
                switch (curent_piece) {
                    case 'd':
                    if ((board.get_piece(cell {i - 1, j}) == 'a') and
                    (board.get_piece(cell {i, j - 1}) == 'a') and
                    (board.get_piece(cell {i, j + 1}) == 'a')) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if (j == 0) {
                switch (curent_piece) {
                    case 'd':
                    if ((board.get_piece(cell {i - 1, j}) == 'a') and
                    (board.get_piece(cell {i, j + 1}) == 'a') and
                    (board.get_piece(cell {i + 1, j}) == 'a')) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if (j == 8) {
                switch (curent_piece) {
                    case 'd':
                    if ((board.get_piece(cell {i - 1, j}) == 'a') and
                    (board.get_piece(cell {i, j - 1}) == 'a') and
                    (board.get_piece(cell {i + 1, j}) == 'a')) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if ((i == 3) and (j == 4)) {
                switch (curent_piece) {
                    case 'd':
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if ((i == 4) and (j == 3)) {
                switch (curent_piece) {
                    case 'd':
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if ((i == 5) and (j == 4)) {
                switch (curent_piece) {
                    case 'd':
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i, j - 1}) == 'd') or
                    (board.get_piece(cell {i, j - 1}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
            if ((i == 4) and (j == 5)) {
                switch (curent_piece) {
                    case 'd':
                    break;
                    case 'a':
                    if (((board.get_piece(cell {i - 1, j}) == 'd') or
                    (board.get_piece(cell {i - 1, j}) == 'k')) and
                    ((board.get_piece(cell {i, j + 1}) == 'd') or
                    (board.get_piece(cell {i, j + 1}) == 'k')) and
                    ((board.get_piece(cell {i + 1, j}) == 'd') or
                    (board.get_piece(cell {i + 1, j}) == 'k'))) {
                        board.del_piece(cell{i, j});
                    }
                    break;
                }
            }
        }
    }
}

int main (int argc, char const *argv[]) {
    Taefl taefl;
    taefl.game();
    return 0;
}
