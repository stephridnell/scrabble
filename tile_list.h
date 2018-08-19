/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "helpers.h"
#include "io.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef WORDMAP_H
#define WORDMAP_H
#define AL_NUM_LETTERS 27
#define NUM_TILE_DELIMS 2
#define NUM_TILE_TOKENS 3
#define NUM_LETTERS 100
#define DELIM ","
#define NEW_TILE_ERROR -1

/**
 * a tile is a letter and tile pair.
 **/
struct tile {
  /* int is used for letter rather than char in order to consistently
   * use negative numbers
   */
  int letter;
  int score;
};

/**
 * scoreCount stores both the tile and how many times that tile should occur.
 **/
struct scoreCount {
  struct tile tile;
  int count;
};

/**
 * global const variable that indicates that an error has occured.
 **/
extern const struct scoreCount error_score;

struct tileList {
  struct tile* tiles;
  int numberOfTiles;
  int totalTiles;
};

struct tileList* init_tile_list(int);
int new_tile(struct tile*, const char[]);
BOOLEAN add_to_tile_list(struct tile, struct tileList*);
void shuffle_tiles(struct tileList*);
int tl_find(struct tileList* tileList, int needle);
void tl_free(struct tileList* tilelist);

#endif
