/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#ifndef SHARED_H
#define SHARED_H
/**
 * boolean type as there's no boolean type in ansi c.
 **/
typedef enum
{
        FALSE,
        TRUE
} BOOLEAN;

/**
 * the colors available in our system
 **/
enum color
{
        C_RED,
        C_GREEN,
        C_YELLOW,
        C_BLUE,
        C_MAGENTA,
        C_CYAN,
        C_RESET,
        C_INVALID
};
#define SPACE ' '
#endif
