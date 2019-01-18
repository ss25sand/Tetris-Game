#ifndef _BOARD_
#define _BOARD_

#include "pieces.h"

using namespace std;

#define BOARD_HEIGHT 25 // Note the highest row is never used
#define BOARD_WIDTH 12

class Board {
  public:

    Board();

    Pieces *curr_piece;
    
    int board[BOARD_HEIGHT][BOARD_WIDTH] = {{0}};
    int line_counter = 0;
    int interval = 200;
    
    bool lost = false;
    
    int can_delete();
    int get_line();
    int get_interval();
    
    bool game_over();
    bool can_move(int rotation_change, int delta_y, int delta_x);
    
    void print_board();
    void game_over_check();
    void delete_lines();
    void piece_fill();
    void clear_old_piece();
    void update_board();
    void move_right();
    void move_left();
    void rotate();
    void hard_drop();
    void next_piece();

};

#endif
