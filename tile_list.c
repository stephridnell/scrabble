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

BOOLEAN init_tile_list(struct tileList* newTileList, int totalTiles) {
  /* create var here cause shorter to write 
  *  - need to use a arg for number of tiles because there is a diff number of tiles in tile map and fill tile list and the players hand
  */
  unsigned sizeOfTiles = totalTiles * sizeof(struct tile);

  /* malloc - return FALSE if fails */
  if (!(newTileList = malloc(sizeof(struct tileList)))) {
    return FALSE;
  }

  /* malloc tiles - return FALSE if fails */
  if (!(newTileList->tiles = malloc(sizeOfTiles))) {
    return FALSE;
  }

  /* put initial values in tile list */
  memset(newTileList->tiles, 0, sizeOfTiles);

  /* total number of tiles for the list */
  newTileList->totalTiles = totalTiles;

  /* number of tiles is 0 until we add tiles */
  newTileList->numberOfTiles = 0;

  return TRUE;
}
