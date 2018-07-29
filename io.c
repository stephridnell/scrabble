/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "io.h"
#include "tile_list.h"
#include "game.h"

/******************************************************************************
 * the io module should contain the logic for all io functions, both for
 * loading from a file and output to the screen / input from the keyboard. Some
 * functions have been provided here to give you a start.
 *****************************************************************************/

/**
 * array that contains the color strings for each color available in the
 * game
 **/
const char* colorStrings[] = {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_RESET,
  NULL
};

/**
 *  clears the buffer when there is a buffer overflow of input
 **/
void read_rest_of_line(void) {
  int ch;
  while (ch = getc(stdin), ch != '\n' && ch != EOF)
    ;
  clearerr(stdin);
}

/**
 * loads the word list (dictionary of allowed words) into a linked list of
 * words. You should open the file then read in each line into a node in
 * the word list. Don't forget to validate each action and remove the
 * newline characters as you load the data in. Also, don't forget to validate
 * that the whole word has been read and remove the newline at the end of
 * each line.
 **/
BOOLEAN load_word_list(const char fileName[], struct wordList* wordList) {
  FILE *file;

  /* open file */
  if (!(file = fopen(fileName, "r"))) {
    error_print("Error opening dictionary file: %s\n", strerror(errno));
    return FALSE;
  }
  
  normal_print("File open OK\n");

  /* add words to word list */
  return TRUE;
}

/**
 * loads the tiles and their values as well as the count of how many
 * should be created
 **/
BOOLEAN load_scores(const char fileName[], struct tileList** letterMap, struct tileList** fullList) {
  return FALSE;
}

/**
 * displays the board with its current contents. As the cells of the board
 * contain both a char and a color, you need to display the char in the color
 * indicated by the color element of the cell. You must use the provided
 * colorStrings array to retrieve the color codes to display the strings
 * in the right color.
 **/
void display_board(const struct board* theBoard) {
}

/**
 * display the hand in a table. Please see the sample executable / the
 * assignment specification for the expected format of this output
 **/
void print_hand(struct tileList* currentHand) {
}

/**
 * prints out text to stdout
 **/
int normal_print(const char format[], ...) {
  int charCount;
  va_list argList;
  /* extract the argument list */
  va_start(argList, format);
  /* send to output */
  charCount = vprintf(format, argList);
  /* all done */
  va_end(argList);
  return charCount;
}

/**
 * prints output to stderr
 * using error print from assignment 1 startup code by paul miller
 **/
int error_print(const char* format, ...) {
  /* the number of chars printed by this function */
  int charsPrinted;
  va_list argvec;
  /* marshall the output for sending to vprintf */
  va_start(argvec, format);
  /* change the color to red and print the Error preambe for an error
   * message */
  charsPrinted = fprintf(stderr, COLOR_RED);
  /* print the output required by the user */
  charsPrinted += vfprintf(stderr, format, argvec);
  /* reset back to the default colour */
  charsPrinted += fprintf(stderr, COLOR_RESET);
  /* stop using the stdarg library */
  va_end(argvec);
  return charsPrinted;
}

/**
 * prints out the final scores for each player to stdout, sorted from highest
 * scoring player to lowest scoring player
 **/
void print_finscores(struct game* theGame) {
}
