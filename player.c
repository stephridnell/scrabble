/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "player.h"
#include "game.h"

/******************************************************************************
 * the player module manages the player struct. There are required functions
 * provided such as new_players(), init_player(), take_turn(),
 * shuffle_players(), player_sort() and some comparison functions for players.
 * You should add additional functions for managing of players if you need to.
 *****************************************************************************/

/**
 * allocates a players array of the size specified. It allocates a random color
 * for each player and then calls init_player() on each player, passing in the
 * required arguments
 **/
struct player* new_players(int numberOfPlayers, struct game* theGame, enum inputResult* status) {
  /* init each player, assign random colours */
  int currentPlayerIndex;
  
  /* allocate size / initialise for players array */
  int size = sizeof(struct player) * numberOfPlayers;
  theGame->players = (struct player*)malloc(size);

  /* return null if there was an error */
  if (!theGame->players) {
    error_print("malloc error\n");
    return NULL;
  }

  /* set games' numberOfPlayers */
  theGame->numberOfPlayers = numberOfPlayers;

  /* init individual players */
  for (currentPlayerIndex = 0; currentPlayerIndex < numberOfPlayers; currentPlayerIndex++) {
    enum color currentPlayersColour = C_MAGENTA;

    /* TODO assign randcom colours - every player can have pink for now :) */

    *status = init_player(
      &theGame->players[currentPlayerIndex],
      currentPlayerIndex + 1,
      currentPlayersColour,
      theGame
    );
  }

  return theGame->players;
}

/**
 * Initialise the data for a player. this includes prompting for the name
 * of a player, and filling the starting hand for the using from the tile
 * deck, as well as setting the color and the game pointer and set the score to
 * 0.
 **/
enum inputResult init_player(struct player* currentPlayer, int playerNumber, enum color color, struct game* theGame) {
  enum inputResult inputResult = IR_FAILURE;
  char prompt[LINE_LENGTH + EXTRA_CHARS];
  char playerNameInput[NAME_LENGTH + EXTRA_CHARS];

  /* get the name of th player from user */
  while (inputResult == IR_FAILURE) {
    inputResult = get_input("Please enter the name of the player: ", playerNameInput);
  }

  /* handle rtm */
  if (inputResult == IR_RTM) {
    return IR_RTM;
  }

  /* TODO filling the starting hand for the using from the tile deck */

  /* add stuff to the struct */
  currentPlayer->color = color;
  currentPlayer->theGame = theGame;
  currentPlayer->score = 0;
  strcpy(currentPlayer->name, playerNameInput);

  return IR_SUCCESS;
}

/**
 * This is the function that implements each player turn. Firstly, the word to
 * player is prompted for - the word cannot be any longer than the width of
 * the board, of course. Display the board, prompt for the coordinates of
 * the move in the form of x:y:d where x and y are the starting coordinates of
 * the word and d is the dimension of the word - either h or v (case
 * insensitive). It must be apparent from the prompt the name and color of the
 * player who is taking the current turn.
 *
 * Next, use the functions implemented in the rules module to validate
 * and apply the changes to the board.
 **/
enum inputResult take_turn(struct player* currentPlayer, BOOLEAN isFirst) {
  /* you'll need to allocate and free this on every turne */
  char* word;
  return IR_FAILURE;
}

/**
 * shuffle the player so they are ordered in a different order to the order
 * they were entered as part of initialisation
 **/
void shuffle_players(struct player *players, int numberOfPlayers) {
  int currentPlayerIndex, indexToSwapWith;
  struct player temp;

  /* loop through the players and swap with a random other player */
  for(currentPlayerIndex = 0; currentPlayerIndex < numberOfPlayers; currentPlayerIndex++) {
    indexToSwapWith = player_shuffle_cmp(numberOfPlayers);

    /* using same swap method as in assignment 1 */
    temp = players[indexToSwapWith];
    players[indexToSwapWith] = players[currentPlayerIndex];
    players[currentPlayerIndex] = temp;
  }
}

/**
 * sorts the players in the player list in some order
 **/
void player_sort(struct player* players, int numberOfPlayers, int (*cmp)(const struct player*, const struct player*)) {
}

/**
 * when finalising the scores, players are sorted by score from top to bottom
 * to print out at the end of a game
 **/
int player_cmp(const struct player* first, const struct player* second) {
  return EOF;
}

/**
 * in the random shuffle, we randomly "sort" elements according to the result
 * returned from rand()
 * 
 * I changed the params for this method cos it made more sense this way
 **/
int player_shuffle_cmp(int numberOfPlayers) {
  return rand() % numberOfPlayers;
}
