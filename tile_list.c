/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "tile_list.h"

/******************************************************************************
 * the tile list module manages the tile list which might behave like a tile map
 * (mapping between a letter and a score) or it might be a list which that can
 * be added to or deleted from (such as a tile deck or tile hand). You are
 *required to create the functions for this list.
 *****************************************************************************/

struct tileList* init_tile_list(int totalTiles) {
  struct tileList* newTileList;
  /* create var here cause shorter to write 
  *  - need to use a arg for number of tiles because there is a diff number of tiles in tile map and fill tile list and the players hand
  */
  unsigned sizeOfTiles = totalTiles * sizeof(struct tile);

  /* malloc - return NULL if fails */
  if (!(newTileList = malloc(sizeof(struct tileList)))) {
    return NULL;
  }

  /* malloc tiles - return NULL if fails */
  if (!(newTileList->tiles = malloc(sizeOfTiles))) {
    return NULL;
  }

  /* put initial values in tile list */
  memset(newTileList->tiles, 0, sizeOfTiles);

  /* total number of tiles for the list */
  newTileList->totalTiles = totalTiles;

  /* number of tiles is 0 until we add tiles */
  newTileList->numberOfTiles = 0;

  return newTileList;
}

int new_tile(struct tile *newTile, const char tileString[]) {
  char *currentToken, *tileStringCopy, *letter, *score, *count;
  int tokenCount = 1, tileCount = 0, tileScore = 0;

  /* strtok is mutative so we have make a copy of the tileString */
  if (!(tileStringCopy = strdup(tileString))) {
    error_print("Error copying tileString\n");
    /* return new tile error (-1) */
    return NEW_TILE_ERROR;
  }

  /* get the tokens */
  currentToken = strtok(tileStringCopy, DELIM);
  while (currentToken) {
    if (tokenCount == 1) {
      /* store the letter */
      letter = strdup(currentToken);
      if (!letter) {
        error_print("Error getting letter\n");
        return NEW_TILE_ERROR;
      }
    } else if (tokenCount == 2) {
      /* store the score */
      score = strdup(currentToken);
      if (!score) {
        error_print("Error getting score\n");
        return NEW_TILE_ERROR;
      }
    } else if (tokenCount == 3) {
      /* store the count */
      count = strdup(currentToken);
      if (!count) {
        error_print("Error getting count\n");
        return NEW_TILE_ERROR;
      }
    } else {
      /* if it gets here it means there are too many tokens so we error */
      error_print("Error. Invalid tile format encountered. Too many tokens: %s\n", tileString);
      return NEW_TILE_ERROR;
    }

    /* increment token count */
    tokenCount++;

    /* proceed to next token */
    currentToken = strtok(NULL, DELIM);
  }

  if (tokenCount != 4) {
    error_print("Error. Invalid tile format encountered. Too few tokens: %s\n", tileString);
    return NEW_TILE_ERROR;
  }

  /* free mem allocated to the string copy we made - theres probably a bunch of other stuff im supposed to free but honestly im terrible at this whole memory thing */
  free(tileStringCopy);

  /* validate LETTER */
  /* length must be 1 */
  if (strlen(letter) != 1) {
    error_print("Error. Invalid tile format encountered. Letter is too long: %s\n", tileString);
  }
  /* must be uppcase letter or a space */
  if ((!isalpha(*letter) || !isupper(*letter)) && *letter != ' ') {
    error_print("Error. Invalid tile format encountered. Letter is wrong: %s\n", tileString);
  }

  /* make SCORE int */
  if (!str_to_int(score, &tileScore)) {
    error_print("Error. Invalid tile format encountered. Score needs to be a number: %s\n", tileString);
    return NEW_TILE_ERROR;
  }

  /* make COUNT int */
  if (!str_to_int(count, &tileCount)) {
    error_print("Error. Invalid tile format encountered. Count needs to be a number: %s\n", tileString);
    return NEW_TILE_ERROR;
  }

  /* create new tile with the values we have in letter and tileScore */
  newTile->letter = *letter;
  newTile->score = tileScore;

  /* return the tile count so we kmnow how many times to add it to the deck */
  return tileCount;
}

BOOLEAN add_to_tile_list(struct tile tileToAdd, struct tileList *list) {
  /* add tile to the end of the lsit */
  list->tiles[list->numberOfTiles++] = tileToAdd;

  /* check if we added too many tiles to the list */
  if (list->numberOfTiles > list->totalTiles) {
    error_print("Too many tiles yo.\n");
    return FALSE;
  }

  return TRUE;
}
