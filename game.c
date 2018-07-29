/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "game.h"
/******************************************************************************
 * the game module manages the overall game. This includes initialisation of
 * the game (initialise and load data for the game, manage the game while in
 * process (selecting the current player, allow that player to have their turn)
 * and finally, displaying scores at the end of the game (when it is quit). Some
 * of these things are managed by calling functions in other modules.
 *****************************************************************************/

/**
 * initialise the game - just like in assignment 1, you should call all the
 *functions that initialise the data structures for the game from here.
 *
 * Start by loading the score file - the implementation of that function will be
 * in io.c but you'll need to call it from here.
 *
 * You'll also need to ask for how many players are playing but the allocation
 * and initialisation of those players should be done in player.c - including
 * any user input that might involve.
 *
 * Finally, you should prompt the user for the size of the board (that will be
 * used for both width and height as the board is a square). You'll then pass
 * that value into the board module to allocate a 2-dimensional board.
 **/
enum input_result init_game(struct game* thegame, struct word_list* dictionary, const char tile_file[]) {
  return IR_FAILURE;
}

/**
 * The main game loop for the game. Start by initialising the game by a call to
 * init_game() then simply iterate over the players, getting each to have their
 * turn. As there has been no end of game condition specified, the game simply
 * ends when a player quits. At this time, just output the list of players
 * sorted by ther currect score. Please note that as the rules for the placing
 * of the first turn are different you will also need to keep track of whether
 * it is the first turn or not.
 **/
void play_game(struct word_list* dictionary, const char tilefile[]) {
  struct game thegame;
  /* initialise the game */
  /* iterate over the players allowing each to have their turn until
   * someone quits */
  /* finalise the scores and print them */
  /* free memory for the game */
}

/**
 * Once the game is finished we need to free all memory allocated for the game
 **/
void free_game(struct game* thegame) {
}
