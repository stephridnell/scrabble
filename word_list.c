/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "word_list.h"
#include "helpers.h"
#include "io.h"
/******************************************************************************
 * the word_list module simply keeps track of all the words in our
 * "dictionary". After loading from disk, the main purpose of this list will be
 * to check that a word exists in the dictionary. You will need to create the
 * functions for managing this list.
 *****************************************************************************/

/* 
 * initialiase word linked list
 * (linked list methods from weekly chat recording 18/7/18 w/ paul miller)
*/
void word_list_init(struct wordList* wordList) {
  wordList->head = NULL;
  wordList->len = 0;
}

/* 
 * new word node - static because it is only called from in here
 * (linked list methods from weekly chat recording 18/7/18 w/ paul miller)
*/
static struct wordNode* new_word_node(const char word[]) {
  char* mallocWord;
  struct wordNode *new = (struct wordNode*)malloc(sizeof(struct wordNode));
  if (!new) {
    error_print("malloc");
    return NULL;
  }

  mallocWord = malloc((strlen(word) + 1) * sizeof(char));
  if (!mallocWord) {
    free(new);
    return NULL;
  }

  strcpy(mallocWord, word);

  new->word = mallocWord;
  new->next = NULL;
  return new;
}

/* 
 * add new word to linked list
 * (linked list methods from weekly chat recording 18/7/18 w/ paul miller)
*/
BOOLEAN word_list_add(struct wordList* wordList, const char word[]) {
  struct wordNode *current, *previous = NULL;
  struct wordNode *new = new_word_node(word);

  /* if new word node failed (returned null), return false */
  if (!new) {
    return FALSE;
  }

  /* if the head is null, list is empty */
  if (wordList->head == NULL) {
    wordList->head = new;
    return TRUE;
  }

  /* find correct point to insert word using strcmp */
  current = wordList->head;
  while(current && strcmp(current->word, word) < 0) {
    previous = current;
    current = current->next;
  }
  
  /* if previous is null, we are at the start of the list */
  if (!previous) {
    new->next = wordList->head;
    wordList->head = new;
  } else {
    new->next = current;
    previous->next = new;
  }

  wordList->len += 1;

  return TRUE;
}

/* 
 * free word linked list
 * (linked list methods from weekly chat recording 18/7/18 w/ paul miller)
*/
void word_list_free(struct wordList* wordList) {
  struct wordNode *current, *next;
   current = wordList->head;
   while (current) {
     next = current->next;
     free(current->word);
     free(current);
     current = next;
   }
}

/*
FROM https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
*/
BOOLEAN lookup_word(struct wordList* wordList, char word[]) {
  /* 2) Initialize a node pointer, current = head. */
  struct wordNode* current = wordList->head;
  
  /* 3) Do following while current is not NULL */
  while (current != NULL) {
    /* convert word to uppercase */
    str_to_upper(word);

    /* a) current->key is equal to the key being searched return true. */
    if (strcmp(current->word, word) == 0) {
      return TRUE;
    }
    
    /* b) current = current->next */
    current = current->next;
  }

  /* 4) Return false  */
  return FALSE;
}
