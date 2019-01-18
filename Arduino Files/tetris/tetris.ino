#include <FastLED.h>
#include <EEPROM.h>
#include "Board.h"
#include "Pieces.h"

// Arduino pin constants
#define NUM_LEDS    210
#define LED_PIN     7
#define LEFT_PIN   4
#define RIGHT_PIN   3
#define ROTATE_PIN   2
#define HARD_PIN   6
#define SOFT_PIN   5

// Game piece constants
#define NUM_PIECES 7
#define ROTATION_TYPE 4
#define P_ARRAY_WIDTH 5
#define P_ARRAY_HEIGHT 5
#define DIMENSIONS 2

// Button states
byte left_button = 0;
byte right_button = 0;
byte rotate_button = 0;
byte hard_button = 0;
byte soft_button = 0;

// Button states
enum State {UNPUSHED, PUSHED};

State left_state = UNPUSHED;
State right_state = UNPUSHED;
State rotate_state = UNPUSHED;
State hard_drop_state = UNPUSHED;
State soft_drop_state = UNPUSHED;

// Game progression variables
int interval = 200; // Number of milliseconds between each game 'tick'
const int button_interval = 10; // Number of milliseconds between each button parse
unsigned long prev_millis = 0; // Time
unsigned long curr_millis = 0; // Gameplay timer
unsigned long button_prev_millis = 0; // Button timer

// LED array
CRGB *leds = (CRGB*)malloc(3*NUM_LEDS);

// Board object
Board board;
Board *game_board = &board;

// Setup loop
void setup() {
  randomSeed(analogRead(0)); // Seeds random number generator for generating piece types

  // Initial parameters for LED outpout library
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(2);

  // Pin initialization
  pinMode(LED_PIN,OUTPUT);
  pinMode(LEFT_PIN,INPUT_PULLUP);
  pinMode(RIGHT_PIN,INPUT_PULLUP);
  pinMode(ROTATE_PIN,INPUT_PULLUP);
  pinMode(HARD_PIN,INPUT_PULLUP);
  pinMode(SOFT_PIN,INPUT_PULLUP);
  
  Serial.begin(9600); // Port declaration

  // Declare a 4D 7x4x5x5 array that stores the rotation states of each piece, to be used when computing rotation
  byte pieces[NUM_PIECES][ROTATION_TYPE][P_ARRAY_WIDTH][P_ARRAY_HEIGHT] = {

  // O Piece
  {
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,2,2,0},
      {0,0,2,2,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,2,2,0},
      {0,0,2,2,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,2,2,0},
      {0,0,2,2,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,2,2,0},
      {0,0,2,2,0},
      {0,0,0,0,0}
    }
  },
  // I Piece
  {
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,3,3,3,3},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,3,0,0},
      {0,0,3,0,0},
      {0,0,3,0,0},
      {0,0,3,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {3,3,3,3,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,3,0,0},
      {0,0,3,0,0},
      {0,0,3,0,0},
      {0,0,3,0,0},
      {0,0,0,0,0}
    }
  },
  // J Piece
  {
    {
      {0,0,0,0,0},
      {0,4,0,0,0},
      {0,4,4,4,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,4,4,0},
      {0,0,4,0,0},
      {0,0,4,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,4,4,4,0},
      {0,0,0,4,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,4,0,0},
      {0,0,4,0,0},
      {0,4,4,0,0},
      {0,0,0,0,0}
    }
  },
  // L Piece
  {
    {
      {0,0,0,0,0},
      {0,0,0,5,0},
      {0,5,5,5,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,5,0,0},
      {0,0,5,0,0},
      {0,0,5,5,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,5,5,5,0},
      {0,5,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,5,5,0,0},
      {0,0,5,0,0},
      {0,0,5,0,0},
      {0,0,0,0,0}
    }
  },
  // S Piece
  {
    {
      {0,0,0,0,0},
      {0,0,6,6,0},
      {0,6,6,0,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,6,0,0},
      {0,0,6,6,0},
      {0,0,0,6,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,0,6,6,0},
      {0,6,6,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,6,0,0,0},
      {0,6,6,0,0},
      {0,0,6,0,0},
      {0,0,0,0,0}
    }
  },
  // Z Piece
  {
    {
      {0,0,0,0,0},
      {0,7,7,0,0},
      {0,0,7,7,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,7,0},
      {0,0,7,7,0},
      {0,0,7,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,7,7,0,0},
      {0,0,7,7,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,7,0,0},
      {0,7,7,0,0},
      {0,7,0,0,0},
      {0,0,0,0,0}
    }
  },
  // T Piece
  {
    {
      {0,0,0,0,0},
      {0,0,8,0,0},
      {0,8,8,8,0},
      {0,0,0,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,8,0,0},
      {0,0,8,8,0},
      {0,0,8,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,0,0,0},
      {0,8,8,8,0},
      {0,0,8,0,0},
      {0,0,0,0,0}
    },
    {
      {0,0,0,0,0},
      {0,0,8,0,0},
      {0,8,8,0,0},
      {0,0,8,0,0},
      {0,0,0,0,0}
    }
  }
};

  // Converts above array into EEPROM to conserve limited SRAM
  for (int i = 0; i < NUM_PIECES; i ++) {
    for (int j = 0; j < ROTATION_TYPE; j ++) {
      for (int k = 0; k < P_ARRAY_WIDTH; k ++) {
        for (int l = 0; l < P_ARRAY_HEIGHT; l ++) {
          EEPROM.update(i * (ROTATION_TYPE * P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + j * (P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + k * P_ARRAY_HEIGHT + l, pieces[i][j][k][l]); // Address of values is 0 to 700 in EEPROM
        }
      }  
    }
  }
  
}

// Main function
void loop() {
 
  // While loop to run through game
  while(!(game_board->game_over())) {
    
    curr_millis = millis(); // Gets current time

    // Reads button pushes
    left_button = digitalRead(LEFT_PIN);
    right_button = digitalRead(RIGHT_PIN);
    rotate_button = digitalRead(ROTATE_PIN);
    hard_button = digitalRead(HARD_PIN);
    soft_button = digitalRead(SOFT_PIN);
    Serial.println(soft_button);
    // Checks if enough time has elapsed to justify a game 'tick'
    if(curr_millis - prev_millis >= interval){
      
        game_board->print_board(); // Prints updarte of board to LED array
        game_board->update_board(); // Updates current piece by one 'tick'
        prev_millis = curr_millis; // Resets time
        //interval = game_board->get_interval();
        
    }

    // Checks if enough time ahs elapse to justify a check for button pushes
    if (curr_millis - button_prev_millis >= button_interval){

        // Switch statements for each button detailed taks to be completed ONLY at a change of state (Thus, holding right/left movement button will not repeat the command)

        // Left movement button
        switch (left_state) {

          case UNPUSHED: {
            if (!left_button) { // Checks if button transitioned from unpushed to pushed
              game_board->move_left();  
              left_state = PUSHED; // Change state
            }
            break;
          }
          case PUSHED: {
            if (left_button) { // Checks if button transitioned from pushed to unpushed
              left_state = UNPUSHED; // Change state
            }  
            break;
          }
          
        }

        // Right movement button
        switch (right_state) {

          case UNPUSHED: { 
            if (!right_button) { // Checks if button transitioned from unpushed to pushed
              game_board->move_right();  
              right_state = PUSHED; // Change state
            }
            break;
          }
          case PUSHED: {
            if (right_button) { // Checks if button transitioned from pushed to unpushed
              right_state = UNPUSHED; // Change state
            }  
            break;
          }
          
        }

        // Rotation button
        switch (rotate_state) {

          case UNPUSHED: {
            if (!rotate_button) { // Checks if button transitioned from unpushed to pushed
              game_board->rotate();  
              rotate_state = PUSHED; // Change state
            }
            break;
          }
          case PUSHED: {
            if (rotate_button) { // Checks if button transitioned from pushed to unpushed
              rotate_state = UNPUSHED; // Change state
            }  
            break;
          }
          
        }
        
        // Hard drop button
        switch (hard_drop_state) {

          case UNPUSHED: { // Checks if button transitioned from unpushed to pushed
            if (!hard_button) { 
              game_board->hard_drop();  
              hard_drop_state = PUSHED; // Change state
            }
            break;
          }
          case PUSHED: {
            if (hard_button) { // Checks if button transitioned from pushed to unpushed
              hard_drop_state = UNPUSHED; // Change state
            }  
            break;
          }
          
        }

        // Soft drop button
        switch (soft_drop_state) {

          case UNPUSHED: {
            if (!soft_button) { // Checks if button transitioned from unpushed to pushed
              interval = 15; // Lowers interval between game ticks
              soft_drop_state = PUSHED; // Change state
            }
            break;
          }
          case PUSHED: {
            if (soft_button) { // Checks if button transitioned from pushed to unpushed
              interval = 200; // Increases interval between game ticks to original value
              soft_drop_state = UNPUSHED; // Change state
            }  
            break;
          }
          
        }
        
        button_prev_millis = curr_millis; // Resets time
    }
  }

  // Game over animations
  for (int i = 0; i < 10; i ++) { // Flickers LEDs 5 times on and off
    
    if (i % 2 == 0) {
      FastLED.setBrightness(0); // Off
    } else {
      FastLED.setBrightness(5); // On
    }

    FastLED.show();
    delay(100); // Delay for flicker effect
    
  }

  for (byte i = 0; i < 21; i ++) { // 'Waterfall' effect
    for (byte j = 0; j < 10; j ++) {
      leds[10*i + j] = CRGB(0,0,0); // Successively turns off each row beginning at the top
    }  
    delay(60);
    FastLED.show();
  }
  
  free(leds);
  delay(100000); // Prevents undefined behaviours
}
