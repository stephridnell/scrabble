/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "shared.h"
#include <limits.h>
#include <ctype.h>
#include <assert.h>

#ifndef HELPERS_H
#define HELPERS_H

#define DECIMAL 10

BOOLEAN str_to_int(const char str[], int* ptrResult);
void str_to_upper(char* stringPointer);
int count_char(const char[], char);
char** tokenize(const char[], const char[], int);
void free_tokens(char**, int);
BOOLEAN strtoint(const char input[], int* output);

#endif
