/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"

/* from paul miller ass2 partb solution */
const struct cell default_cell = { ' ', C_RESET };

/*****************************************************************************
 * board.c and board.h form the board module. You need to provide functions
 * that manage the game board: allocate the board, set and get the contents of
 * the cells for the board and free the board when exiting the game
 ****************************************************************************/

/* from paul miller ass2 partb solution */
BOOLEAN init_board(struct board* board) {
  int xcount, ycount;
  
  /* allocate the row pointers */
  board->matrix = (struct cell**)malloc(board->boardSize * sizeof(struct cell*));
  
  /* allocate each row and then initialise each cell to the default cell */
  for (ycount = 0; ycount < board->boardSize; ++ycount) {
    board->matrix[ycount] = (struct cell*)malloc(board->boardSize * sizeof(struct cell));
    for (xcount = 0; xcount < board->boardSize; ++xcount) {
      board->matrix[ycount][xcount] = default_cell;
    }
  }
  
  return TRUE;
}

/**
 * function for retrieving a value from a cell - from paul miller ass2 partb solution
 **/
struct cell board_get(struct board* theboard, int x, int y) {
  return theboard->matrix[y][x];
}
