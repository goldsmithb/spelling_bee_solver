#ifndef SPELLING_BEE_SOLVER
#define SPELLING_BEE_SOLVER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

/*                                              */
/*                  MACROS                      */
/*                                              */
/* Assume that at most 500 anagrams will be found */
#define MAX_GRAMS 500
/* Assume the game is played with 7 letters */
#define NUM_LETTERS 7


/*                                              */
/*                   STRCUTS                    */
/*                                              */
/* game_t struct 
 *
 * letters : char array of letters forming the 'hive'
 * 
 * score : integer total score for getting all the anagrams
 * */
typedef struct game
{
    char letters[7];
    int score;
} game_t;


/*                                              */
/*                FUNCTIONS                     */
/*                                              */
/*
 * contains_letter : helper function that checks if a word contains a letter.
 * 
 * l : letter we are looking for
 * 
 * word : word we are looking in
 * 
 * len : integer length of the string
 * 
 * return : true if the target letter is in the target word. False otherwise.
 * */
bool contains_letter(char l, char *word, int len);

/*
 * is_valid_word : helper function that evaluates if a word is valid i.e.
 *                 is made up only of 'hive' letters AND includes the center
 *                 letter.
 * 
 * l : letter we are looking for
 * 
 * word : word we are looking in
 * 
 * len : integer length of the string
 * 
 * return : integer score of the word if it is indeed valid. 0 otherwise.
 * */
int check_word(char *ls, char *word, int len);

/*
 * find_anagrams : iterate over the dictionary file and check for anagrams,
 *                 calculating the score for the game.
 * 
 * game : current game struct we are playing.
 * 
 * f : dictionary txt file we are searching for anagrams in.
 * 
 * return : array of strings representing all the found anagrams.
 * */
char **find_anagrams(game_t *game, FILE *f);

#endif