// Stores information about each piece for use in tetris.cpp

#ifndef _PIECES_
#define _PIECES_

#define NUM_PIECES 7
#define ROTATION_TYPE 4
#define P_ARRAY_WIDTH 5
#define P_ARRAY_HEIGHT 5
#define DIMENSIONS 2

class Pieces {
  public:

  Pieces();
  int x;
  int y;
  int piece_type;
  int rotation_state;
  
  void change_x(int delta_x);
  void change_y(int delta_y);
  void piece_rotate();

  int curr_pos (int piece_type, int piece_rotation, int y, int x);
  int get_x();
  int get_y();
  int get_type();
  int get_rotation();
  
  void new_piece(int type);
  
};

#endif
