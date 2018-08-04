/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"
#include "io.h"
#include "rules.h"
#include "tile_list.h"
#include <string.h>
#ifndef PLAYER_H
#define PLAYER_H

/* the maximum number of players for the game */
#define MAX_PLAYERS 6
#define HAND_SIZE 7
#define NAME_LENGTH 20

struct game;

struct player {
  /* the name of the player */
  char name[NAME_LENGTH + 1];
  /* the player's score */
  int score;
  /* the color of each token played by this player */
  enum color color;
  /* the hand for the player */
  struct tileList hand;
  /* a pointer to the game data for this game */
  struct game* theGame;
};

/* public functions callable from this module */
enum inputResult init_player(struct player*, int, enum color, struct game*);
void shuffle_players(struct player*, int);
struct player* new_players(int, struct game*, enum inputResult*);
int player_cmp(const struct player*, const struct player*);
int player_shuffle_cmp(const struct player*, const struct player*);
void player_sort(struct player*, int, int (*)(const struct player*, const struct player*));
enum inputResult take_turn(struct player*, BOOLEAN);
#endif
