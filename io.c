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
  COLOR_RESET,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
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
  int words = 0;
  char currentLine[MAX_WORD_LEN + EXTRA_CHARS];

  /* open file */
  if (!(file = fopen(fileName, "r"))) {
    error_print("Error opening dictionary file: %s\n", strerror(errno));
    return FALSE;
  }

  /* read file and add words to word list */
  while (fgets(currentLine, MAX_WORD_LEN + EXTRA_CHARS, file)) {

    /* check for buffer overflow */
    if (currentLine[strlen(currentLine) - 1] != '\n') {
      read_rest_of_line();
      error_print("Buffer overflow");
      return FALSE;
    }

    /* remove newline char */
    currentLine[strlen(currentLine) - 1] = 0;
    
    /* TODO convert currentLine to uppercase */
    word_list_add(wordList, currentLine);
    words++;
  }

  return TRUE;
}

/**
 * loads the tiles and their values as well as the count of how many
 * should be created
 **/
BOOLEAN load_scores(const char fileName[], struct tileList** letterMap, struct tileList** fullList) {
  int runningTileCount = 0;
  char currentLine[TILE_LENGTH + EXTRA_CHARS];
  FILE* file;

  /* open file */
  if (!(file = fopen(fileName, "r"))) {
    error_print("Error opening tile file: %s\n", strerror(errno));
    return FALSE;
  }

  /* INIT LETTER MAP */
  if (!(*letterMap = init_tile_list(AL_NUM_LETTERS))) {
    error_print("Error initialising the letter map\n");
    return FALSE;
  }

  /* INIT LETTER FULL LIST */
  if (!(*fullList = init_tile_list(NUM_LETTERS))) {
    error_print("Error initialising the letter full list\n");
    return FALSE;
  }

  /* read file and add tuiles to tiles lists */
  while (fgets(currentLine, TILE_LENGTH + EXTRA_CHARS, file)) {
    struct tile newTile;
    int newTileCount, inserted;
    /* check for buffer overflow */
    if (currentLine[strlen(currentLine) - 1] != '\n') {
      read_rest_of_line();
      error_print("Buffer overflow");
      return FALSE;
    }

    /* remove newline char */
    currentLine[strlen(currentLine) - 1] = 0;

    /* create new tile and get the counr of how many times to put it in deck of tiles */
    newTileCount = new_tile(&newTile, currentLine);
    if (newTileCount < 0) {
      error_print("Error creating new tile. Format probably wrong.\n");
      return FALSE;
    }

    runningTileCount = runningTileCount + newTileCount;

    if (runningTileCount > NUM_LETTERS) {
      error_print("Too many tiles yo.\n");
      return FALSE;
    }

    /* insert one copy into letter map */
    if (!add_to_tile_list(newTile, *letterMap)) {
      error_print("Error adding to tile map.\n");
      return FALSE;
    }
    
    /* insert newTileCount number of copies of the tile into the deck */
    for (inserted = 0; inserted < newTileCount; inserted++) {
      if (!add_to_tile_list(newTile, *fullList)) {
        error_print("Error adding to tile list.\n");
        return FALSE;
      }
    }
  }

  /* shuffle */
  shuffle_tiles(*fullList);
  return TRUE;
}

/**
 * displays the board with its current contents. As the cells of the board
 * contain both a char and a color, you need to display the char in the color
 * indicated by the color element of the cell. You must use the provided
 * colorStrings array to retrieve the color codes to display the strings
 * in the right color.
 **/
void display_board(const struct board* theBoard) {
  int y, x, count, cellSize = 6;
  int countStart = theBoard->boardSize - cellSize;

  /* print header */
  
  normal_print("%3c |", ' ');

  for (count = 1; count <= theBoard->boardSize; ++count) {
    normal_print("%3d |", count);
  }

  print_divider("-", countStart, theBoard->boardSize * cellSize);

  /* print body */

  for (y = 0; y < theBoard->boardSize; y++) {
    normal_print("%3d |", y + 1);

    for (x = 0; x < theBoard->boardSize; x++) {
      struct cell* cell = theBoard->matrix[y] + x;
      int letter = abs(cell->letter);

      normal_print("%s%3c%s |", colorStrings[cell->color], letter, colorStrings[C_RESET]);
    }

    print_divider("-", countStart, theBoard->boardSize * cellSize);
  }

}

void print_divider(const char symbol[], int start, int max) {
  int count;
  print_line();
  for (count = start; count < max; count++) {
    normal_print(symbol);
  }
  print_line();
}

void print_line(void) {
  normal_print("\n");
}

/**
 * display the hand in a table. Please see the sample executable / the
 * assignment specification for the expected format of this output
 **/
void print_hand(struct tileList* currentHand) {
  int x;

  print_divider("=", 0, 4 * currentHand->numberOfTiles + 1);

  for (x = 0; x < currentHand->numberOfTiles; x++) {
    normal_print("|%2c ", currentHand->tiles[x].letter);
  }

  normal_print("|");

  print_divider("=", 0, 4 * currentHand->numberOfTiles + 1);
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
  int i;
  struct player* players = theGame->players;

  for (i = 0; i < theGame->numberOfPlayers; i++) {
    players[i].score = calculate_score(players + i);
  }

  /* TODO sort players according to score */

  print_line();

  normal_print("Scrabble - Final Scores");

  print_divider("=", 0, NAME_LENGTH + 10);

  normal_print("%-*s | %s", NAME_LENGTH, "Player Name", "Score");

  print_divider("-", 0, NAME_LENGTH + 10);

  for (i = 0; i < theGame->numberOfPlayers; i++) {
    normal_print("%-*s | %5d\n", NAME_LENGTH, players[i].name, players[i].score);
  }
}

enum inputResult get_input(const char prompt[], char line[], int size) {
  /* display prompt */
  normal_print("%s", prompt);

  /* if user presses enter or ctrl-D 'return to menu' */
  if (fgets(line, size + EXTRA_CHARS, stdin) == NULL || *line == '\n') {
    return IR_RTM;
  }

  /* check for buffer overflow */
  if (line[strlen(line) - 1] != '\n') {
    read_rest_of_line();
    error_print("Too many chars. Please try again.\n");
    return IR_FAILURE;
  }

  /* remove new line */
  line[strlen(line) - 1] = 0;

  return IR_SUCCESS;
}
