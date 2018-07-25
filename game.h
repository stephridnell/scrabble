/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"
#include "helpers.h"
#include "io.h"
#include "player.h"
#include "tile_list.h"
#include "word_list.h"
#ifndef GAME_H
#define GAME_H
/**
 * the main data structure for the game. Just like in the first assignment,
 **/
struct game
{
        /* the players array - it's a pointer so we can dynamically allocate how
         * many we need */
        struct player* players;
        /* the board - notice it's not a pointer? That means we get the
         * allocation of the board struct itself for free. Any pointers inside
         * we still need to point somewhere before we use them. That's the job
         * of malloc */
        struct board theboard;
        /* the dictionary of words that are loaded at startup */
        struct word_list* allwords;
        /* this list provides the mapping from tiles (letters) to scores (the
         * the numeric contribution of the tile to the board */
        struct tile_list* tilemap;
        /* the full deck of tiles - dealing of tiles is just deleting from the
         * top of this list and adding it to the hand list in the player struct
         */
        struct tile_list* tiledeck;
        /* the number of players in the game */
        int num_players;
};

/* public functions callable from outside this module */
enum input_result init_game(struct game*, struct word_list*, const char[]);

void play_game(struct word_list*, const char[]);

void free_game(struct game*);
#endif
