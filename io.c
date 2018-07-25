/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
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
const char* color_strings[] = { COLOR_RED,   COLOR_GREEN,   COLOR_YELLOW,
                                COLOR_BLUE,  COLOR_MAGENTA, COLOR_CYAN,
                                COLOR_RESET, NULL };

/**
 *  clears the buffer when there is a buffer overflow of input
 **/
void read_rest_of_line(void)
{
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
BOOLEAN load_word_list(const char fname[], struct word_list* wordlist)
{
        return FALSE;
}

/**
 * loads the tiles and their values as well as the count of how many
 * should be created
 **/
BOOLEAN load_scores(const char fname[], struct tile_list** lettermap,
                    struct tile_list** fulllist)
{
        return FALSE;
}

/**
 * displays the board with its current contents. As the cells of the board
 * contain both a char and a color, you need to display the char in the color
 * indicated by the color element of the cell. You must use the provided
 * color_strings array to retrieve the color codes to display the strings
 * in the right color.
 **/
void display_board(const struct board* theboard)
{
}

/**
 * display the hand in a table. Please see the sample executable / the
 * assignment specification for the expected format of this output
 **/
void print_hand(struct tile_list* curhand)
{
}

/**
 * prints out text to stdout
 **/
int normal_print(const char format[], ...)
{
        int charcount;
        va_list arglist;
        /* extract the argument list */
        va_start(arglist, format);
        /* send to output */
        charcount = vprintf(format, arglist);
        /* all done */
        va_end(arglist);
        return charcount;
}

/**
 * prints output to stderr
 **/
int error_print(const char format[], ...)
{
        va_list arglist;
        int charcount = 0;
        /* grab the arguments */
        va_start(arglist, format);
        /* send them to stderr */
        charcount += vfprintf(stderr, format, arglist);
        /* all done */
        va_end(arglist);
        return charcount;
}

/**
 * prints out the final scores for each player to stdout, sorted from highest
 * scoring player to lowest scoring player
 **/
void print_finscores(struct game* thegame)
{
}
