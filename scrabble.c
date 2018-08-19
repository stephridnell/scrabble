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
    display_usage();
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
      error_print("Error: Invalid seed provided.\n");
      display_usage();
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

/**
 * display instructions to the user of the program in how to use it.
 * FROM PAUL MILLER ASS2 PARTB SOL
 **/
void display_usage(void) {
  error_print("Error: invalid command-line arguments provided.\n");
  error_print("You need to call this program as: \n");
  error_print("\n\t./scrabble <dictionary> <scorefile> [<seed>]\n\n");
  error_print("the dictionary file and the scorefile may have any name. \n");
  error_print("We only validate for the position of the argument and its contents.\n");
  error_print("We do not validate the file name or its location.\n");
  error_print("The seed is optional but if used should be the seed from a previous run of the program.\n");
}