/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"

/*****************************************************************************
 * board.c and board.h form the board module. You need to provide functions
 * that manage the game board: allocate the board, set and get the contents of
 * the cells for the board and free the board when exiting the game
 ****************************************************************************/

BOOLEAN init_board(struct board* board) {
  struct cell initialCell = {
    ' ',
    C_RESET
  };
  int y, x, boardSize = board->boardSize;

  /* alocate mem for pointers in the board */
  board->matrix = malloc(boardSize * boardSize * sizeof(struct cell*));

  /* return false if it failed */
  if (!board->matrix) {
      return FALSE;
    }

  for (x = 0; x < boardSize; x++) {
    /* malloc the row */
    board->matrix[x] = malloc(boardSize * sizeof(struct cell));

    /* return false if it failed */
    if (!board->matrix[x]) {
      return FALSE;
    }

    /* init each cell to be the initial cell */
    for (y = 0; y < boardSize; y++) {
      board->matrix[x][y] = initialCell;
    }
  }

  return TRUE;
}
