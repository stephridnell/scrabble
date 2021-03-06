/******************************************************************************
 * Student Name    :     Steph Ridnell
 * RMIT Student ID :     s3272974
 * COURSE CODE     :     CPT 220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#ifndef SHARED_H
#define SHARED_H
/**
 * boolean type as there's no boolean type in ansi c.
 **/
typedef enum {
  FALSE,
  TRUE
} BOOLEAN;

/**
 * the colors available in our system - i cheated with my random colour assignment by changing the order... shh.
 **/
enum color {
  C_RESET,
  C_RED,
  C_GREEN,
  C_YELLOW,
  C_BLUE,
  C_MAGENTA,
  C_CYAN,
  C_INVALID
};
#define SPACE ' '
#endif
