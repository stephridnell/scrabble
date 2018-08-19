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
  int tokenCount = 1, y = 0, x = 0, i, letter;
  BOOLEAN overlap = FALSE, usedOwnLetter = FALSE;
  /* find out if there are any blanks in hand */
  int blanks = 0, tileLocation = 0;
  for (i = 0; i < currentPlayer->hand.numberOfTiles; i++) {
    if (currentPlayer->hand.tiles[i].letter == SPACE) {
      blanks++;
    }
  }
  
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

  /* Finally, test that the word specified can be made 
  on the board given the starting location and the player's hand */
  for (i = 0; i < strlen(word); i++) {
    /* get currenct cell on board */
    if (theMove->dir == DIR_HORIZONTAL) {
      letter = board_get(&currentPlayer->theGame->theBoard, theMove->x + i, theMove->y).letter;
    } else {
      letter = board_get(&currentPlayer->theGame->theBoard, theMove->x, theMove->y + i).letter;
    }

    /* abs because letter in cell can be negative */
    letter = abs(letter);

    /* if the char is the letter then is valid move because word overlaps another word */
    if (letter == word[i]) {
      overlap = TRUE;
    } else if (letter == SPACE) {
      /* if the char is a space, make sure the player has the letter or a blank */
      tileLocation = tl_find(&currentPlayer->hand, word[i]);
      if (tileLocation < 0) {
        /* if letter isn't found - check for blanks */
        if (blanks > 0) {
          /* decement nunmber of blanks */
          blanks = blanks - 1;
          usedOwnLetter = TRUE;
        } else {
          error_print("Error. Player does not have letter %c.\n", word[i]);
          return FALSE;
        }
      } else {
        usedOwnLetter = TRUE;
      }
    } else {
      return FALSE;
    }
  }

  if (!usedOwnLetter) {
    /* invalid move if the player didn't use any letters from their hand */
    error_print("Error. Player must use at least one letter from their own hand.\n");
    return FALSE;
  } else if (!overlap && !isFirst) {
    /* invalid move if it's not the first turn and there's no overlap with another word */
    error_print("Error. Word must overlap another word already in play.\n");
    return FALSE;
  } else {
    /* else move is valid */
    return TRUE;
  }
}

/**
 * applies the word specified at the coordinates and direction specified by the
 * move struct to the game board using the player's color. Don't forget to
 * account for the blank tiles.
 **/
void apply_move(struct player* player, const struct move* currentMove, const char word[]) {
  int i;

  /* find out if there are any blanks in hand */
  int blanks = 0;
  for (i = 0; i < player->hand.numberOfTiles; i++) {
    if (player->hand.tiles[i].letter == SPACE) {
      blanks++;
    }
  }

  /* loop thru word */
  for (i = 0; i < strlen(word); i++) {
    int tileLocation = 0;
    /* create new cell */
    struct cell newCell;
    struct cell boardCell;
    BOOLEAN setSuccess = FALSE;
    newCell.letter = word[i];
    newCell.color = player->color;

    /* get current board cell */
    if (currentMove->dir == DIR_VERTICAL) {
      boardCell = board_get(&player->theGame->theBoard, currentMove->x, currentMove->y + i);
    } else {
      boardCell = board_get(&player->theGame->theBoard, currentMove->x + i, currentMove->y);
    }

    /* check if cell empty (letter is a space) */
    if (boardCell.letter == SPACE) {
      /* if it is a space - remove tile from players hand */
      /* check if letter is in hand */
      tileLocation = tl_find(&player->hand, newCell.letter);
      if (tileLocation < 0) {
        /* if letter isn't found - check for blanks */
        if (blanks > 0) {
          /* convert the letter in te cell to negative so we still know what letter it is but that it is also a blnk */
          newCell.letter = -newCell.letter;
          blanks = blanks - 1;
          /* find the blank in the hand */
          tileLocation = tl_find(&player->hand, SPACE);
        } else {
          error_print("Error: you do not have the letter %c in your hand.\n", newCell.letter);
          return;
        }
      }

      /* start up code has this method return void so 
      im not sure if i should be handling these failing */
      if (!tl_remove(&player->hand, NULL, tileLocation)) {
        error_print("Error removing tile from hand.\n");
        return;
      }

      if (currentMove->dir == DIR_VERTICAL) {
        setSuccess = board_set(&player->theGame->theBoard, currentMove->x, currentMove->y + i, newCell);
      } else {
        setSuccess = board_set(&player->theGame->theBoard, currentMove->x + i, currentMove->y, newCell);
      }

      if (!setSuccess) {
        error_print("Error adding cell to board.\n");
        return;
      }

    }
  }
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
