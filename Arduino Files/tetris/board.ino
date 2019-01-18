#include "Board.h"

// Constructor
Board::Board() {

  // Initialize borders of grid to 1 for collision checking
  for (int i = 0; i < BOARD_HEIGHT; i ++) {
    board[i][0] = 1;
    board[i][BOARD_WIDTH-1] = 1;
    if (i == BOARD_HEIGHT - 1) {
      for (int j = 1; j < BOARD_WIDTH; j ++) {
        board[i][j] = 1;
      }
    }
  }
  
  Serial.println("Constructor initialized"); // Debug
  curr_piece = new Pieces(); // Initialize piece
  next_piece(); // Create new piece

};

// Checks if any rows can be deleted, returns row to be deleted
int Board::can_delete() {

  for (int j = 0; j < BOARD_HEIGHT-1; j ++) {

    bool del = true;
    for (int i = 1; i < BOARD_WIDTH - 1; i++) {
      if (board[j][i] == 0) {
        del = false;
      }
    }
    if (del) {
      line_counter++;
      if (interval > 50) {
        interval -= 5;  
      }
      return j;
    }
  }
  return 100;
}

int Board::get_line() {
  return line_counter;  
}

int Board::get_interval() {
  return interval;  
}

// Getter
bool Board::game_over() {
  return lost;
}

// Checks if a change in the current piece's state is possible
bool Board::can_move(int rotation_change, int delta_y, int delta_x) {

  for (int i = 0; i < P_ARRAY_WIDTH; i ++) {
    for (int j = 0; j < P_ARRAY_WIDTH; j ++) {
      if (curr_piece->curr_pos(curr_piece->get_type(), (curr_piece->get_rotation() + rotation_change) % 4, i, j) > 0
        && board[curr_piece->get_y() + delta_y+ i][curr_piece->get_x() + delta_x + j] > 0) {
        return false;
      }
    }
  }
  return true;

}

void Board::print_board() { // Displays board to LED array
   /*Edit print_board for output to LEDs. I assume numbering is from top to bottom, i.e.:
  0   1   2   3   4   5   6   7   8   9
  19  18  17  16  15  14  13  12  11  10
  ...
  ...
  200 201 202 203 204 205 206 207 208 209
  */
  
  for (int i = 3; i < BOARD_HEIGHT - 1; i++) {
    for (int j = 1; j < BOARD_WIDTH - 1; j++) {

      int x = 0;
      
        if (i % 2 == 1) { // Snake pattern
          x = j;
        } else {
          x = BOARD_WIDTH - j - 1;
        } 

        switch(board[i][x]) {

          case 0: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = (0, 0 ,0);
              break;
          case 2: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(255, 255, 0); // Yellow
              break;
          case 3: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(0,128,128); // Teal
              break;
          case 4: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(0, 50, 255); // Blue
              break;
          case 5: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(255,  10, 10); // Orange
              break;
          case 6: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(80, 255, 50); // Green
              break;
          case 7: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(255, 95, 50); // Red
              break;
          case 8: leds[(BOARD_WIDTH-2) * (i-3) + j - 1] = CRGB(200, 20, 230); // Purple
              break;
        }
    }
  }
  
  FastLED.show(); // Update changes to LEDs
  
}

// Checks if game is over
void Board::game_over_check() {

  for (int i = 1; i < BOARD_WIDTH - 1; i ++) {
    if (board[2][i] > 0) { // Exists a piece above the playing board
      lost = true;
    }
  }

}

// Deletes rows
void Board::delete_lines() {

  while (can_delete() < 25) {
    
    int del = can_delete();
    for (int i = del; i > 0; i --) {
      for (int j = 1; j < BOARD_WIDTH - 1; j ++) {
        if (i <= del) {
          board[i][j] = board[i-1][j]; // Shits higher rows downwards
        }
      }
    }
    
  }

}

// Fills in the current pieces on the game board
void Board::piece_fill() {

  for (int i = 0; i < P_ARRAY_WIDTH; i ++) {
    for (int j = 0; j < P_ARRAY_WIDTH; j ++) {
      if (curr_piece->curr_pos(curr_piece->get_type(), curr_piece->get_rotation(), i, j) > 0) {
        board[curr_piece->get_y()+i][curr_piece->get_x()+j] = curr_piece->curr_pos(curr_piece->get_type(), curr_piece->get_rotation(), i, j);
      }
    }
  }

}

// Removes current piece from game board before checking for change to avoid self-collision
void Board::clear_old_piece() {

  for (int i = 0; i < P_ARRAY_WIDTH; i ++) {
    for (int j = 0; j < P_ARRAY_WIDTH; j ++) {
      if (curr_piece->curr_pos(curr_piece->get_type(), curr_piece->get_rotation(), i, j) > 0) {
        board[curr_piece->get_y() + i][curr_piece->get_x() + j] = 0;
      }
    }
  }

}

// One game 'tick', moves current piece downwards and does relevant checks
void Board::update_board() {
  
  // Clear old piece in board
  clear_old_piece();
  
  // Try downwards movement
  if (can_move(0, 1, 0)) {
    curr_piece->change_y(1);

  } else { // Piece cannot be moved downwards, add it permanently

    piece_fill();
    game_over_check();

    if (game_over()) { // Check if the game is over after this piece is placed
      Serial.println(F("Game Over!")); // Debug
    } else {
      delete_lines(); // Check for lines to be deleted
      next_piece(); // Create a new piece

    }

  }
  
  piece_fill(); // Draw the current piece's temporary state
  
}

// ===============================
// Movement Functions
// ===============================

void Board::move_right() { // Right

  clear_old_piece();
  if (can_move(0, 0, 1)) { // Checks if piece can be shifted to the right
    curr_piece->change_x(1); // Shifts right
  }
  piece_fill();

}

void Board::move_left() { // Left

  clear_old_piece();
  if (can_move(0, 0, -1)) { // Checks if piece can be shifted to the left
    curr_piece->change_x(-1); // Shifts left
  }
  piece_fill();

}

void Board::rotate() { // Rotation

  clear_old_piece();
  if (can_move(1, 0, 0)) { // Checks if piece can be rotated
    curr_piece->piece_rotate(); // Rotates
  }
  piece_fill();

}

void Board::hard_drop() { // Hard Drop

  clear_old_piece();
  while (can_move(0, 1, 0)) { // Checks if piece can still be mvoed downwards
    curr_piece->change_y(1); // Moves piece downwards
  }
  piece_fill();

}

// Generates a new random piece type and plaes it at the top of the board
void Board::next_piece() {

  for (int i = 0; i < random(10); i ++) { // Call random a few times to increase variation in pieces
    random(i);
  }
  int piece_type = random(7); // Sets piece type

  curr_piece->new_piece(piece_type); // Calls function in Piece object to reset the object

}
