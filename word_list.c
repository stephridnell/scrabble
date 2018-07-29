/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "word_list.h"
#include "io.h"
/******************************************************************************
 * the word_list module simply keeps track of all the words in our
 * "dictionary". After loading from disk, the main purpose of this list will be
 * to check that a word exists in the dictionary. You will need to create the
 * functions for managing this list.
 *****************************************************************************/

BOOLEAN word_list_init(struct wordList* wordList) {
  return FALSE;
}

BOOLEAN word_list_add(struct wordList* wordList, const char word[]) {
  return FALSE;
}

BOOLEAN word_list_delete(struct wordList* wordList, const char word[]) {
  return FALSE;
}

void word_list_free(struct wordList* wordList) {}
