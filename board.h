/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "shared.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BOARD_H
#define BOARD_H

#define BOARD_MIN_SIZE 5
#define BOARD_MAX_SIZE 15
/* the contents of each board cell - the letter and the color of the player who
 * played the letter */
struct cell {
  int letter;
  enum color color;
};

/*
 * The definition of a board as a 2d matrix and a specicifation of its size.
 * This allows for dynamic memory allocation.
 */
struct board {
  struct cell** matrix;
  int boardSize;
};

BOOLEAN init_board(struct board*);
struct cell board_get(struct board* theboard, int x, int y);

#endif
