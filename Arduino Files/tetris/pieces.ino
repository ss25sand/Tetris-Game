#include "pieces.h"

int piece_spawn[NUM_PIECES][2] = { // Stores initial position of spawned piece
  // O Piece
    {0, 3}, 
  // I Piece
    {1, 3},
  // J Piece
    {1, 3},
  // L Piece
    {1, 3},
  // S Piece
    {0, 3},
  // Z Piece
    {0, 3},
  // T Piece
    {0, 3}
};

// Constructor
Pieces::Pieces() {
  
  piece_type = 0; // Dummy, value will be initialized elsewhere
  y = piece_spawn[piece_type][0]; // Gets intial y-offset
  x = piece_spawn[piece_type][1]; // Gets initial x-offset
  rotation_state = 0; // Sets to default rotation state (flat)
}

// ===============================
// Modifying functions
// ===============================

void Pieces::change_x(int delta_x) {
  x += delta_x;
}

void Pieces::change_y(int delta_y) {
  y += delta_y;
}

void Pieces::piece_rotate() {
  rotation_state = (rotation_state + 1) % 4;
}

// ===============================
// Getters
// ===============================

int Pieces::curr_pos (int piece_type, int piece_rotation, int y, int x) {
  return EEPROM.read(piece_type * (ROTATION_TYPE * P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + piece_rotation * (P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + y * P_ARRAY_HEIGHT + x); // Reads EEPROM to get current piece's position
}

int Pieces::get_x() {
  return x;
}

int Pieces::get_y() {
  return y;
}

int Pieces::get_type() {
  return piece_type;
}

int Pieces::get_rotation() {
  return rotation_state;
}

// End Getters

// Creates new piece
void Pieces::new_piece(int type) {
  piece_type = type; // Initializes type
  y = piece_spawn[piece_type][0]; // Gets intial y-offset
  x = piece_spawn[piece_type][1]; // Gets initial x-offset
  rotation_state = 0; // Sets to default rotation state (flat)
}
