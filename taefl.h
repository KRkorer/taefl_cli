#ifndef taefl_h
#define taefl_h

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


#endif /* end of include guard: taefl */
