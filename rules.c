/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 2, 2018.
 *****************************************************************************/

#include "rules.h"
#include "game.h"
#include "player.h"

/******************************************************************************
 * the rules module implements the rules for the game. This is likely to be
 * the largest module. I have provided two functions here that you need to
 * implement, being is_valid_move() , apply_move() and calculate_score(). You
 *are likely to require many helper functions however.
 *****************************************************************************/

/**
 * This is the key validation function for each move. Firstly, you'll need to
 * check that the word exists in the dictionary. Next tokenize the move string
 * and validate it - check that the column and row are valid and that placing
 * the word at this location won't overflow the board array. Finally, you'll
 * need to test that the word specified can be made on the board given the
 * starting location and the player's hand. Don't forget that there are
 * different rules when it comes to the first move of the game!
 **/
BOOLEAN is_valid_move(struct player* curplayer, char word[],
                      const char location[], struct move* themove,
                      BOOLEAN isfirst)
{
        return FALSE;
}

/**
 * applies the word specified at the coordinates and direction specified by the
 * move struct to the game board using the player's color. Don't forget to
 * account for the blank tiles.
 **/
void apply_move(struct player* player, const struct move* curmove,
                const char word[])
{
}

/**
 * iterates over the board and each letter that has the same color as the
 * player's letter is added to their score. If the letter value is negative,
 * that means that it was placed by a blank and has a score of 0.
 **/
int calculate_score(struct player* curplayer)
{
        return EOF;
}
