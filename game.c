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
 * functions that initialise the data structures for the game from here.
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
enum inputResult init_game(struct game* theGame, struct wordList* dictionary, const char tileFile[]) {
  enum inputResult result = IR_FAILURE;
  char numberOfPlayersInput[LINE_LENGTH + EXTRA_CHARS],
       boardSizePrompt[LINE_LENGTH + EXTRA_CHARS],
       boardSizeInput[LINE_LENGTH + EXTRA_CHARS];
  int numberOfPlayers, boardSize;

  /* init the game strucpt */
  memset(theGame, 0, sizeof(struct game));
  theGame->allWords = dictionary;

  /* 
    * Start by loading the score file - the implementation of that function will be
    * in io.c but you'll need to call it from here.
  */
  if (!load_scores(tileFile, &theGame->tileMap, &theGame->tiledeck)) {
    error_print("Error loading tile file.\n");
    return IR_FAILURE;
  }

  /* You'll also need to ask for how many players are playing but the allocation
    * and initialisation of those players should be done in player.c - including
    * any user input that might involve.
  */
  while (result == IR_FAILURE) {
    result = get_input("How many players will play? ", numberOfPlayersInput, LINE_LENGTH);
    /* return if the user has entered a new line or crtlD */
    if (result == IR_RTM) {
      return IR_RTM;
    }
    /* check value  */
    if (result == IR_SUCCESS) {
      /* convert to int */
      if (!str_to_int(numberOfPlayersInput, &numberOfPlayers)) {
        error_print("Number of players needs to be a number.\n");
        result = IR_FAILURE;
        continue;
      }
      /* check that the number is in range */
      if (numberOfPlayers > 6 || numberOfPlayers < 1) {
        error_print("Please enter nunmber of players between 1-6.\n");
        result = IR_FAILURE;
        continue;
      }
    }
  }

  /* init players */
  result = IR_FAILURE;
  theGame->players = new_players(numberOfPlayers, theGame, &result);

  if (result != IR_SUCCESS) {
    return result;
  }

  /* shuffle players */
  shuffle_players(theGame->players, numberOfPlayers);

  /* 
    * Finally, you should prompt the user for the size of the board (that will be
    * used for both width and height as the board is a square). You'll then pass
    * that value into the board module to allocate a 2-dimensional board.
  */
 result = IR_FAILURE;
  while (result == IR_FAILURE) {
    sprintf(boardSizePrompt, "How wide and high should the board be? The minimum is %d and the maximum is %d: ", BOARD_MIN_SIZE, BOARD_MAX_SIZE);
    result = get_input(boardSizePrompt, boardSizeInput, LINE_LENGTH);
    /* return if the user has entered a new line or crtlD */
    if (result == IR_RTM) {
      return IR_RTM;
    }
    /* check value  */
    if (result == IR_SUCCESS) {
      /* convert to int */
      if (!str_to_int(boardSizeInput, &boardSize)) {
        error_print("Board size needs to be a number.\n");
        result = IR_FAILURE;
        continue;
      }
      /* check that the number is in range */
      if (boardSize > 15 || boardSize < 5) {
        error_print("Please enter number between 5-15.\n");
        result = IR_FAILURE;
        continue;
      }
    }
  }

  /* init board */
  theGame->theBoard.boardSize = boardSize;
  if (!init_board(&theGame->theBoard)) {
    error_print("Error initialising board.\n");
    return IR_FAILURE;
  }

  return IR_SUCCESS;
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
void play_game(struct wordList* dictionary, const char tileFile[]) {
  struct game theGame;
  BOOLEAN endGame = FALSE, isFirst = TRUE;
  enum inputResult result;
  int currentPlayerIndex = 0;

  /* initialise the game */
  result = init_game(&theGame, dictionary, tileFile);
  if (result == IR_FAILURE || result == IR_RTM) {
    normal_print("Exiting...\n");
    free_game(&theGame);
    return;
  }

  /* iterate over the players allowing each to have their turn until
   * someone quits */
  while (!endGame) {
    if (take_turn(&theGame.players[currentPlayerIndex], isFirst) == IR_RTM) {
      endGame = TRUE;
    }
    currentPlayerIndex++;
    if (currentPlayerIndex >= theGame.numberOfPlayers) {
      currentPlayerIndex = 0;
    }
  }

  /* finalise the scores and print them */
  print_finscores(&theGame);

  /* free memory for the game */
  free_game(&theGame);
}

/**
 * Once the game is finished we need to free all memory allocated for the game
 **/
void free_game(struct game* theGame) {
  int i;

  /* free the board */
  for (i = 0; i < theGame->theBoard.boardSize; i++) {
    free(theGame->theBoard.matrix[i]);
  }
  free(theGame->theBoard.matrix);

  /* need if statements to avoid seg fault */

  /* free the tiles (map and deck) */
  if (theGame->tileMap) {
    tl_free(theGame->tileMap);
    free(theGame->tileMap);
  }

  if (theGame->tiledeck) {
    tl_free(theGame->tiledeck);
    free(theGame->tiledeck);
  }

  /* free the players */
  if (theGame->players) {
    for (i = 0; i < theGame->numberOfPlayers; ++i) {
      tl_free(&theGame->players[i].hand);
    }
    free(theGame->players);
  }
  
}
