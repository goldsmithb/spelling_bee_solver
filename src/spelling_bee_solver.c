/*
 * A program that can solve the NYT anagram game "spelling bee"
 * 
 * Rules of the game:
 *      Create words using letters from the hive.

            * Words must contain at least 4 letters.
            * Words must include the center letter.
            * Our word list does not include words that are obscure, 
              hyphenated, or proper nouns.
            * No cussing either, sorry.
            * Letters can be used more than once.

        Score points to increase your rating.
            * 4-letter words are worth 1 point each.
            * Longer words earn 1 point per letter.
            * Each puzzle includes at least one “pangram” which uses 
              every letter. These are worth 7 extra points!
 * 
 * words_alpha.txt dictionary from https://github.com/dwyl/english-words/.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* game_t struct */
typedef struct game
{
    char letters[7];
    int score;
} game_t;


/* Init game wrapper */
game_t *init_game(char *letters, int len)
{
    game_t *game = malloc(sizeof(game_t));
    if (!game)
    {
        fprintf(stderr, "ERROR: Malloc erro\n");
        exit(-1); // TODO: Quit the game
    }




    return game;
}


int main(int argc, char **argv)
{
    /* command line options:
     * -l,letters abcdefg -- the seven letters in the
     *                             spelling bee game. The first
     *                             letter must be the center letter.
     */

    /* Initialize variables */    
    char letters[7];

    /* Parse command line options */
    char *letters_str = NULL;
    int opt;
    
    while ((opt = getopt(argc, argv, "l:")) != -1)
    {
        switch (opt)
        {
        case 'l' :
            letters_str = strdup(optarg); // TODO: free
        default :
            fprintf(stderr, "ERROR: unknown option");
        }
    }

    if (letters_str == NULL)
    {
        fprintf(stderr, "ERROR: No letters given");
        return -1;
    }

    int fd;
    if ((fd = open("../data/spelling_bee_dict.txt", O_RDONLY)) < 0)
    {
        fprintf(stderr, "ERROR: spelling_bee_dict.txt not detected. Please \
                         run the script <><><>.py and try again");
        return -1;
    }

    /* Initialize game data */
    int len = strlen(letters_str);
    game_t *game = init_game(letters_str, len);

    return 0;
}