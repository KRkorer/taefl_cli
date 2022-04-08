#include <iostream>
#include <cmath>
#include "taefl.h"


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
    board[coord.row][coord.column] = c;
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

void UI::unchoose_piece(Board& board, cell cell){
    switch (board.get_piece(cell)) {
        case 'A':
        board.change_cell(cell, 'a');
        break;
        case 'D':
        board.change_cell(cell, 'd');
        break;
        case 'K':
        board.change_cell(cell, 'k');
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

void UI::show_move (Board& board, cell begin, cell end){
    if (begin.row == end.row) {
        for (int i = 1; i < abs(end.column-begin.column); ++i) {
            if (end.column > begin.column) {
                board.change_cell(cell{begin.row, begin.column + i}, 'x');
            } else {
                board.change_cell(cell{begin.row, begin.column - i}, 'x');
            }
        }
    }
    if (begin.column == end.column) {
        for (int i = 1; i < abs(end.row-begin.row); ++i) {
            if (end.row > begin.row) {
            board.change_cell(cell{begin.row + i, begin.column}, 'x');
            } else {
            board.change_cell(cell{begin.row - i, begin.column}, 'x');
            }
        }
    }
    board.change_cell(end, 'X');
}

void UI::unshow_move (Board& board){
    for (int row = 0; row < 8; ++row){
        for (int column = 0; column < 8; ++column){
            if ((board.get_piece(cell{row, column}) == 'x') or
            (board.get_piece(cell{row, column}) == 'X')){
                board.del_piece(cell{row, column});
            }
        }
    }
}


Taefl::Taefl (){
    curent_player = attack;
}

void Taefl::game () {
    Board board;
    board.init_board();
    UI ui;
    cell begin, end;
    char confirm = 'n';
    while (!((is_defense_win(board)) or (is_attack_win(board)))) {

        do {
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

            ui.show_move (board, begin, end);
            system("clear");
            ui.print_board(board);
            ui.unshow_move(board);

            std::cout << "Confirm move (y/n)" << '\n';
            std::cin >> confirm;
            if (confirm == 'n') {
                ui.unchoose_piece(board, begin);
                system("clear");
                ui.print_board(board);
            } else {
                ui.move_piece(board, begin, end);
                system("clear");
                ui.print_board(board);
            }

        } while (confirm == 'n');


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
    } else {
        if (board.get_king_cell() == cell {-1 ,-1}) {
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

bool Taefl::is_choose_correct (Board& board, cell c_cell, player curent_player){

    if ((board.get_piece(cell {c_cell.row - 1, c_cell.column}) != ' ') and
    (board.get_piece(cell {c_cell.row, c_cell.column + 1}) != ' ') and
    (board.get_piece(cell {c_cell.row + 1, c_cell.column}) != ' ') and
    (board.get_piece(cell {c_cell.row, c_cell.column + 1}) != ' ')) {
        return false;
    }


    switch (curent_player) {
        case attack:
        if (board.get_piece(c_cell) == 'a'){
            return true;
        }
        break;
        case defense:
        if ((board.get_piece(c_cell) == 'd') or (board.get_piece(c_cell) == 'k')) {
            return true;
        }
        break;
    }
    return false;
}

bool Taefl::is_move_correct (Board& board, cell begin, cell end) {
    switch (board.get_piece(begin)) {
        case 'A':
        if ((board.get_piece(end) == ' ') and (end != cell {4, 4})){
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
                        if (board.get_piece(cell {begin.row + i, begin.column}) != ' ') {
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
                        if (board.get_piece(cell {begin.row + i, begin.column}) != ' ') {
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
