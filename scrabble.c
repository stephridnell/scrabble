/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "scrabble.h"

/******************************************************************************
 * the scrabble module contains the main function and any helper functions to
 * kick start the program and clean up at the end.
 *****************************************************************************/
int main(int argc, char* argv[]) {
  struct wordList wordList;
  unsigned seed;
  char *wordFile, *tileFile;
  int words;
  BOOLEAN fileLoaded;

  /* validate command line argments */
  if (argc < 3 || argc > 4) {
    normal_print("Invalid args\n");
    return EXIT_FAILURE;
  }
  /* display a welcome message */
  normal_print("Welcome to 'Scrabble'\n");
  normal_print("-------------------\n");
  /* extract the seed */
  if (argc == 4) {
    /* if the seed has been provided by the user, extract the
     * number from the string provided - please note that I am not
     * using strtoint as we need a long int */
    char *seedArg = argv[3];
    char *ptr;

    seed = strtol(seedArg, &ptr, 10);

    /* check if there is any string - if there is return exit failure */
    if (*ptr) {
      return EXIT_FAILURE;
    }

  } else {
    /* if the seed is not provided, generate the seed for the 
     * current second */
    seed = time(NULL);
  }

  /* start the random number generator */
  srand(seed);
  /* output the seed being used */
  normal_print("Using seed: %u\n", seed);

  /* load the dictionary file */
  normal_print("Please wait while we load the dictionary...\n");
  word_list_init(&wordList);
  wordFile = argv[1];
  fileLoaded = load_word_list(wordFile, &wordList);

  if (!fileLoaded) {
    return EXIT_FAILURE;
  }

  /* output number of words loaded */
  words = wordList.len;
  normal_print("%d words have been loaded.\n", words);

  /* play the game :) */
  tileFile = argv[2];
  play_game(&wordList, tileFile);

  /* free memory */
  word_list_free(&wordList);
  return EXIT_SUCCESS;
}

