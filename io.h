/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "board.h"
#include "shared.h"
#include "word_list.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IO_H
#define IO_H

#define EXTRA_CHARS 2
#define LINE_LENGTH 80

#define TILE_LENGTH 6

/**
 * the possible outcomes of a request for keyboard input
 **/
enum inputResult {
  IR_FAILURE,
  IR_SUCCESS,
  IR_RTM
};

/* the color strings array used to format colours when printing the board */
extern const char *colorStrings[];

/* forwards declarations of structs so that we don't have recursive includes */
struct game;
struct player;
struct tileList;

/* strings for each of the colors in our program */
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

/* public functions implemented for this module */
void read_rest_of_line(void);

BOOLEAN load_word_list(const char[], struct wordList *);

BOOLEAN load_scores(const char[], struct tileList **, struct tileList **);

void display_board(const struct board *);

int normal_print(const char[], ...);

void print_hand(struct tileList *);

int error_print(const char[], ...);

void print_finscores(struct game *);

enum inputResult get_input(const char[], char[]);

#endif
