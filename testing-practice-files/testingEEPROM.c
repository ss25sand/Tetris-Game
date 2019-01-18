#include <stdio.h>
#define NUM_PIECES 7
#define ROTATION_TYPE 4
#define P_ARRAY_WIDTH 5
#define P_ARRAY_HEIGHT 5
#define DIMENSIONS 2

int pieces[NUM_PIECES][ROTATION_TYPE][P_ARRAY_WIDTH][P_ARRAY_HEIGHT] = {

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

int curr_pos (int piece_type, int piece_rotation, int y, int x) {
  return pieces[piece_type][piece_rotation][y][x];
}

void setup() {
  // put your setup code here, to run once:
  int array[1024] = {0};
  //printf("Test");
  //printf("%d",curr_pos(0,0,3,3));
  for (int i = 0; i < NUM_PIECES; i ++) {
    for (int j = 0; j < ROTATION_TYPE; j ++) {
      for (int k = 0; k < P_ARRAY_HEIGHT; k ++) {
        for (int l = 0; l < P_ARRAY_WIDTH; l ++) {
          array[i * (ROTATION_TYPE * P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + j * (P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + P_ARRAY_HEIGHT * k + l] = curr_pos(i,j,k,l);
          //printf("i-%d   ", i * (ROTATION_TYPE * P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + j * (P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + P_ARRAY_HEIGHT * k + l);
          //printf("(%d  %d  %d  %d)\n", i,j,k,l);
          //printf("d-%d  ", curr_pos(i,j,k,l));
        } 
        //printf("\n");
      }
      //printf("\n"); 
    }
    //printf("\n");
  }

  for (int i = 0; i < NUM_PIECES; i ++) {
    for (int j = 0; j < ROTATION_TYPE; j ++) {
      for (int k = 0; k < P_ARRAY_HEIGHT; k ++) {
        for (int l = 0; l < P_ARRAY_WIDTH; l ++) {
          printf("%d",array[i * (ROTATION_TYPE * P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + j * (P_ARRAY_HEIGHT * P_ARRAY_WIDTH) + P_ARRAY_HEIGHT * k + l]);
        } 
        printf("\n");
      }
      printf("\n"); 
    }
    printf("\n");
  }

  for (int i = 0; i < NUM_PIECES * ROTATION_TYPE * P_ARRAY_WIDTH * P_ARRAY_HEIGHT; i ++) {

      printf("%d",array[i]);
    
  }
  
}

int main (void) {
  // put your main code here, to run repeatedly:
  setup();
  return 0;
}