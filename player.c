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
    enum color currentPlayersColour = C_RESET;
    BOOLEAN colourAllocated = FALSE, colourTaken = FALSE;
    int i, color;

    /* assign randcom colours */
    while (!colourAllocated) {
      color = (rand() % 6) + 1;
      colourTaken = FALSE;
      
      for (i = 0; i < numberOfPlayers; i++) {
        /* check to see if a player already has the colour */
        if (theGame->players[i].color == color) {
          colourTaken = TRUE;
        }
      }
      /* if colour not taken - assign it */
      if (!colourTaken) {
        currentPlayersColour = color;
        colourAllocated = TRUE;
      }
    }

    *status = init_player(
      &theGame->players[currentPlayerIndex],
      currentPlayerIndex + 1,
      currentPlayersColour,
      theGame
    );

    if (*status == IR_RTM) {
      return NULL;
    }
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
    sprintf(prompt, "Please enter the name of the player %d: ", playerNumber);
    inputResult = get_input(prompt, playerNameInput, LINE_LENGTH);
  }

  /* handle rtm */
  if (inputResult == IR_RTM) {
    return IR_RTM;
  }

  /* INIT HAND */
  if (!init_hand(&currentPlayer->hand, theGame->tiledeck)) {
    error_print("Error initialising player hand.\n");
    return IR_FAILURE;
  }

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
  char* word;
  enum inputResult result = IR_FAILURE;
  char prompt[BUFSIZ + EXTRA_CHARS];
  struct board* board = &currentPlayer->theGame->theBoard;
  char coords[COORDS_LENGTH + EXTRA_CHARS];

  /* you'll need to allocate and free this on every turne */
  word = malloc(currentPlayer->theGame->theBoard.boardSize + EXTRA_CHARS);

  /* display the board */
  display_board(board);

  /* display player name, score and hand */
  normal_print("It is %s%s's%s turn, their current score is %d, and their current hand is: ", 
    colorStrings[currentPlayer->color],
    currentPlayer->name,
    COLOR_RESET,
    currentPlayer->score = calculate_score(currentPlayer)
  );

  /* display hand */
  print_hand(&currentPlayer->hand);

  /* prompt user for word */
  sprintf(prompt, "Please enter a word to play, at most %d characters: ", board->boardSize);

  while (result == IR_FAILURE) {
    result = get_input(prompt, word, board->boardSize);
  }

  if (result == IR_RTM) {
    normal_print("Exiting...\n");
    free(word);
    return IR_RTM;
  }

  /* prompt for coordinates */
  result = IR_FAILURE;

  while (result == IR_FAILURE) {
    result = get_input("Please enter the starting location for the word in the format x:y:d where x and y are the row and column the word starts and d is the direction - either h for horizontal or v for vertical: ", coords, COORDS_LENGTH);
  }

  if (result == IR_RTM) {
    normal_print("Exiting...\n");
    free(word);
    return IR_RTM;
  }

  /* validate the turn */

  /* apply changes to board */

  /* draw new tiles for the player */

  free(word);
  return IR_SUCCESS;
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

BOOLEAN init_hand(struct tileList *hand , struct tileList *deck) {
  int tilesAdded;

  if (!(hand->tiles = malloc(HAND_SIZE))) {
    return FALSE;
  }

  memset(hand->tiles, 0, HAND_SIZE);
  hand->totalTiles = HAND_SIZE;
  hand->numberOfTiles = 0;

  /* add 7 random tiles to hand from deck */
  for (tilesAdded = 0; tilesAdded < hand->totalTiles; tilesAdded++) {
    /* draw tile and add to hand */
    if (!draw_tile(deck, hand)) {
      error_print("Error drawing tile.\n");
      return FALSE;
    }
  }

  return TRUE;
}

BOOLEAN draw_tile(struct tileList* deck, struct tileList* hand) {
  int i, index = 0;
  struct tile drawnTile;

  /* remove top tile from the deck */
  drawnTile = deck->tiles[index];

  /* move all hte tiles forward to fill the now empty spot */
  for (i = 0; i < deck->numberOfTiles - 1; i++) {
    deck->tiles[i] = deck->tiles[i + 1];
  }

  /* reduce the count of tiles remaining in the deck by 1 */
  deck->numberOfTiles = deck->numberOfTiles - 1;

  /* add drawn tile to hand */
  if (!add_to_tile_list(drawnTile, hand)) {
    return FALSE;
  }

  return TRUE;
}
