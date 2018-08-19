/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "rules.h"
#include "game.h"
#include "player.h"

/******************************************************************************
 * the rules module implements the rules for the game. This is likely to be
 * the largest module. I have provided two functions here that you need to
 * implement, being is_valid_move() , apply_move() and calculate_score(). You
 *are likely to require many helper functions however.
 *****************************************************************************/

/**
 * This is the key validation function for each move. Firstly, you'll need to
 * check that the word exists in the dictionary. Next tokenize the move string
 * and validate it - check that the column and row are valid and that placing
 * the word at this location won't overflow the board array. Finally, you'll
 * need to test that the word specified can be made on the board given the
 * starting location and the player's hand. Don't forget that there are
 * different rules when it comes to the first move of the game!
 **/
BOOLEAN is_valid_move(struct player* currentPlayer, char word[], const char location[], struct move* theMove, BOOLEAN isFirst) {
  char *coordCopy, *currentToken, *xCoord, *yCoord, *direction;
  int tokenCount = 1, y = 0, x = 0;
  
  /* Firstly, you'll need to check that the word exists in the dictionary */
  if (!lookup_word(currentPlayer->theGame->allWords, word)) {
    error_print("Word not found in dictionary.\n");
    return FALSE;
  }
  
  /* Next tokenize the move string and validate it */
  if (!(coordCopy = strdup(location))) {
    error_print("Error copying coord string\n");
    /* return new tile error (-1) */
    return FALSE;
  }

  /* get the tokens */
  currentToken = strtok(coordCopy, ":");
  while (currentToken) {
    if (tokenCount == 1) {
      /* store the x coord */
      xCoord = strdup(currentToken);
      if (!xCoord) {
        error_print("Error getting x coord\n");
        return FALSE;
      }
    } else if (tokenCount == 2) {
      /* store the y coord */
      yCoord = strdup(currentToken);
      if (!yCoord) {
        error_print("Error getting y coord\n");
        return FALSE;
      }
    } else if (tokenCount == 3) {
      /* store the direction */
      direction = strdup(currentToken);
      if (!direction) {
        error_print("Error getting direction\n");
        return FALSE;
      }
    } else {
      /* if it gets here it means there are too many tokens so we error */
      error_print("Error. Invalid location format encountered. Too many tokens: %s\n", location);
      return FALSE;
    }

    /* increment token count */
    tokenCount++;

    /* proceed to next token */
    currentToken = strtok(NULL, ":");
  }

  if (tokenCount != 4) {
    error_print("Error. Invalid location format encountered. Too few tokens: %s\n", location);
    return FALSE;
  }

  /* free mem allocated to the string copy we made */
  free(coordCopy);

  /* make COORDS int */
  if (!str_to_int(xCoord, &x)) {
    error_print("Error. Invalid tile format encountered. X coord needs to be a number: %s\n", location);
    return FALSE;
  }

  if (!str_to_int(yCoord, &y)) {
    error_print("Error. Invalid tile format encountered. Y coord needs to be a number: %s\n", location);
    return NEW_TILE_ERROR;
  }

  /* decerement coords cos arrays start at 0 */
  x--;
  y--;

  /* make sure within board boundries */
  if (x > currentPlayer->theGame->theBoard.boardSize || x < 0) {
    error_print("Error. X coord not witin board bounds.\n");
    return FALSE;
  }

  if (y > currentPlayer->theGame->theBoard.boardSize || y < 0) {
    error_print("Error. Y coord not witin board bounds.\n");
    return FALSE;
  }

  /* save coord values in the move */
  theMove->x = x;
  theMove->y = y;

  /* validate direction and make sure word fits */
  if (strcmp(direction, "h") == 0 || strcmp(direction, "H") == 0) {
    theMove->dir = DIR_HORIZONTAL;
    if (theMove->x + strlen(word) > currentPlayer->theGame->theBoard.boardSize) {
      error_print("Error. Word will not fit on board.\n");
      return FALSE;
    }
  } else if (strcmp(direction, "v") == 0 || strcmp(direction, "V") == 0) {
    theMove->dir = DIR_VERTICAL;
    if (theMove->y + strlen(word) > currentPlayer->theGame->theBoard.boardSize) {
      error_print("Error. Word will not fit on board.\n");
      return FALSE;
    }
  } else {
    error_print("Error. Invalid direction.\n");
    return FALSE;
  }

  /* TODO Finally, test that the word specified can be made 
  on the board given the starting location and the player's hand */

  return TRUE;
}

/**
 * applies the word specified at the coordinates and direction specified by the
 * move struct to the game board using the player's color. Don't forget to
 * account for the blank tiles.
 **/
void apply_move(struct player* player, const struct move* currentMove, const char word[]) {
}

/**
 * iterates over the board and each letter that has the same color as the
 * player's letter is added to their score. If the letter value is negative,
 * that means that it was placed by a blank and has a score of 0.
 **/
int calculate_score(struct player* currentPlayer) {
  struct board* board = &currentPlayer->theGame->theBoard;
  int score = 0, x, y, tileIndex;
  struct tileList* tileMap = currentPlayer->theGame->tileMap;

  /* loop through the board */
  for (y = 0; y < board->boardSize; y++) {
    for (x = 0; x < board->boardSize; x++) {
      /* get the current cell using board_get from ass2 partb solution */
      const struct cell cell = board_get(board, x, y);
      
      /* check that the cell letter isn't blank (not negative) 
      and that the colour matches the players colour */
      if (cell.letter >= 0 && cell.color == currentPlayer->color) {
        if ((tileIndex = tl_find(tileMap, cell.letter) == EOF)) {
          return EOF;
        }
        score += tileMap->tiles[tileIndex].score;
      }
    }
  }
  return score;
}
