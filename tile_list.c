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

/**
 * global error score
 * FROM ASS2PARTB SOL
 **/
const struct scoreCount errorScore = { { EOF, EOF }, EOF };

/**
 * performs a linear search to file the letter specified. Your implementation
 * could be a lot more efficient than this.
 * 
 * FROM ASS2PARTB SOL
 **/
static struct tile* find_letter(const struct tileList* theMap, const char letter) {
  int count;
  for (count = 0; count < theMap->numberOfTiles; ++count) {
    if (theMap->tiles[count].letter == letter) {
      return &theMap->tiles[count];
    }
  }
  return NULL;
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

/**
 * performs a linear search over the tile list and if it is found, return the
 * index of the location where the element is located and if it is not found,
 * return -1
 * 
 * from paul miller ass2 partb solution
 **/
int tl_find(struct tileList* tileList, int needle) {
  int count;
  for (count = 0; count < tileList->numberOfTiles; ++count) {
    if (tileList->tiles[count].letter == needle) {
      return count;
    }
  }
  return EOF;
}

/**
 * frees the tiles array for this tile list
 * FROM PAUL MILLER ASS2 PARTB SOLUTION
 **/
void tl_free(struct tileList* tileList) {
  free(tileList->tiles);
}

/**
 * removes the tile at the specified index and if retval is not NULL then
 * store the tile there.
 * FROM PAUL MILLER ASS2 PARTB SOLUTION
 **/
BOOLEAN tl_remove(struct tileList* tileList, struct tile* returnVal, int index) {
  int count;

  /* check that the specified index is within the range of a valid index */
  if (index >= tileList->numberOfTiles || index < 0) {
    return FALSE;
  }
  
  /* if returnVal is not NULL, store the value into that memory */
  if (returnVal) {
    *returnVal = tileList->tiles[index];
  }
  
  /* shuffle all the elements forward */
  for (count = index; count < tileList->numberOfTiles - 1; ++count) {
    tileList->tiles[count] = tileList->tiles[count + 1];
  }
  
  /* reducce the count of tiles */
  tileList->numberOfTiles--;
  return TRUE;
}

/**
 * in some places, the tile list pointer needs to be malloced and so we
 * allocate space for the list structure itself here
 * 
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
struct tileList* tl_make(int numberOfTiles) {
  struct tileList* newList;
  /* allocate space for the list structure */
  newList = (struct tileList*)malloc(sizeof(struct tileList));
  if (!newList) {
    error_print("malloc: %s\n", strerror(errno));
    return NULL;
  }
  /* init work already implemented in tl_init() */
  if (!tl_init(newList, numberOfTiles)) {
    return NULL;
  }
  return newList;
}

/**
 * private (as not in the header) enumeration that represents that parts of
 * a score for use with the tokenisation and processing of the tilestring
 * below
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
enum delimcount {
  DC_LETTER,
  DC_NUMBER,
  DC_COUNT,
  DC_INVALID
};

/**
 * creates a tile and count of how many of that tile should exist in the system
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
struct scoreCount new_score_count(const char tilestring[]) {
  const char* delim = ",";
  enum delimcount curdelim;
  struct scoreCount thescore = { { EOF, EOF }, EOF };
  
  /* tokenize the tilestring */
  char** parts = tokenize(tilestring, delim, NUM_TILE_TOKENS);
  char letter;
  
  /* iterate over the tokens */
  for (curdelim = 0; curdelim < DC_INVALID; ++curdelim) {
    switch (curdelim) {
      case DC_LETTER:
        /* store the letter from the string */
        if (strlen(parts[DC_LETTER]) != ONECHAR) {
          error_print("token too long: %s\n", parts[DC_LETTER]);
          free_tokens(parts, NUM_TILE_TOKENS);
          return errorScore;
        }
        
        letter = *parts[DC_LETTER];
        /* validate the the tile is an upper case letter or a space (blank) */
        if ((!isalpha(letter) || !isupper(letter)) && letter != SPACE) {
          return errorScore;
        }
        
        thescore.tile.letter = letter;
        break;
      case DC_NUMBER:
        /* convert to int the score for this tile */
        if (!strtoint(parts[DC_NUMBER], &thescore.tile.score)) {
          free_tokens(parts, NUM_TILE_TOKENS);
          return errorScore;
        }
        break;
      case DC_COUNT:
        /* extract the count of how many of this tile should exist in the system */
        if (!strtoint(parts[DC_COUNT], &thescore.count)) {
          free_tokens(parts, NUM_TILE_TOKENS);
          return errorScore;
        }
        break;
      default:
        /* any other value is an error, so we handle them */
        error_print("Error: too many delimiters\n");
        free_tokens(parts, NUM_TILE_TOKENS);
        return errorScore;
    }
  }
  
  /* free the tokens as we are done with them */
  free_tokens(parts, NUM_TILE_TOKENS);
  return thescore;
}

/**
 * adds a tile to the tile list. Please note that this function allows for
 * duplicate data to be added, such as the same tile being added twice.
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
BOOLEAN tl_add(struct tileList* tilelist, const struct tile atile) {
  if (tilelist->numberOfTiles >= tilelist->totalTiles) {
    return FALSE;
  }
  tilelist->tiles[tilelist->numberOfTiles++] = atile;
  return TRUE;
}

/**
 * searches the tile list for the tile that needs to be added and if it
 * already exists, just change the score to be what was passed in. If it does
 * not exist, add it at the end.
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
BOOLEAN tl_set(struct tileList* map, const struct tile score) {
  /* search for the tile */
  struct tile* old_val = find_letter(map, score.letter);
  /* if found, update the score for that tile */
  if (old_val != NULL) {
    old_val->score = score.score;
    return TRUE;
  }
  /* test that there is space for this tile */
  if (map->numberOfTiles == map->totalTiles) {
    return FALSE;
  }
  /* if there is space, add it at the end */
  map->tiles[map->numberOfTiles++] = score;
  return TRUE;
}

/**
 * initialises the tile list to hold the number of tiles specified.
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
struct tileList* tl_init(struct tileList* newMap, int numberOfTiles) {
  assert(numberOfTiles > 0);
  /* allocate space for the tiles */
  newMap->tiles = (struct tile*)malloc(sizeof(struct tile) * numberOfTiles);
  if (!newMap->tiles) {
    return NULL;
  }
  /* initialise the tiles to 0 and the count to 0 */
  memset(newMap->tiles, 0, sizeof(struct tile) * numberOfTiles);
  newMap->numberOfTiles = 0;
  newMap->totalTiles = numberOfTiles;
  return newMap;
}

/**
 * convenience function for swapping tiles for shuffling / sorting
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
static void swap_tiles(struct tile* first, struct tile* second) {
  struct tile temp = *first;
  *first = *first;
  *first = *second;
  *second = temp;
}

/**
 * randomises the tile list specified. This is designed to be used with
 * the tile deck
 * FROM PAUL MILLER ASS 2 PART B SOLUTION
 **/
void tl_shuffle(struct tileList* tilelist) {
  int count;
  /* iterate through the first half of the tile list and
   * randomly swap with another tile in the tile list */
  for (count = 0; count < tilelist->numberOfTiles / 2; ++count) {
    int newloc = rand() % tilelist->numberOfTiles;
    if (newloc != count) {
      swap_tiles(tilelist->tiles + count, tilelist->tiles + newloc);
    }
  }
}
