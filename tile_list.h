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
#define ONECHAR 1

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
extern const struct scoreCount errorScore;

struct tileList {
  struct tile* tiles;
  int numberOfTiles;
  int totalTiles;
};


BOOLEAN add_to_tile_list(struct tile, struct tileList*);
int tl_find(struct tileList* tileList, int needle);
void tl_free(struct tileList* tilelist);
BOOLEAN tl_remove(struct tileList* tileList, struct tile* returnVal, int index);

struct tileList* tl_make(int numberOfTiles);
struct scoreCount new_score_count(const char tilestring[]);
BOOLEAN tl_add(struct tileList* tilelist, const struct tile atile);
BOOLEAN tl_set(struct tileList* map, const struct tile score);
struct tileList* tl_init(struct tileList* newMap, int numberOfTiles);
void tl_shuffle(struct tileList* tilelist);

#endif
