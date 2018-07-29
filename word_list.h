/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "shared.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WORD_LIST_H
#define WORD_LIST_H

/* the longest word supported by this program */
#define MAX_WORD_LEN 15

/**
 * linked node that points to the next node and holds the char pointer for
 * the word
 **/
struct wordNode {
  char* word;
  struct wordNode* next;
};

/**
 * list header structure. holds a pointer to the head node and the length
 * of the list, in case we need that.
 **/
struct wordList {
  struct wordNode* head;
  int len;
};

BOOLEAN word_list_init(struct wordList*);

BOOLEAN word_list_add(struct wordList*, const char[]);

BOOLEAN word_list_delete(struct wordList*, const char[]);

void word_list_free(struct wordList*);

/* publicly callable functions from this module */
#endif
