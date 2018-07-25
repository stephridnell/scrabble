/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include <string.h>
#include "board.h"
#include "word_list.h"
#include "helpers.h"
#include "shared.h"
#include "tile_list.h"

#ifndef RULES_H
#define RULES_H

struct player;
struct game;
/**
 * possible directions - horizontal or vertical
 **/
enum direction
{
        DIR_HORIZONTAL,
        DIR_VERTICAL
};

/**
 * holds the details on a move - the horizontal and vertical coordinates and
 * the direction.
 **/
struct move
{
        int x, y;
        enum direction dir;
};

/**
 * publicly available functions from this module
 **/
BOOLEAN is_valid_move(struct player *, char[], const char[], struct move *,
                      BOOLEAN);
int calculate_score(struct player *);
void apply_move(struct player *, const struct move *, const char[]);
#endif
