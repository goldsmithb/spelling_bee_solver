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

#include "spelling_bee_solver.h"


/* Init game wrapper */
game_t *init_game(char *in_letters, int len)
{
    game_t *game = malloc(sizeof(game_t));
    if (!game)
    {
        fprintf(stderr, "ERROR: Malloc error\n");
        exit(-1); // TODO: Quit the game
    }

    /* Copy the letters from input, disregard '\0' */
    for (int i = 0; i < len; i++)
        game->letters[i] = in_letters[i];

    game->score = 0;

    return game;
}

bool contains_letter(char l, char *word, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (word[i] == l)
            return true;
    }
    return false;
}

int check_word(char *ls, char *word, int len)
{
    /* First, check for center letter */
    if (!contains_letter(ls[0], word, len))
        return 0;

    /* Good. Now check for the other letters */
    for (int i = 0; i < len; i++)
    {
        if (!contains_letter(word[i], ls, NUM_LETTERS))
            return 0;
    }

    int score = 1;

    return score;
}

int find_anagrams(game_t *game, FILE *f)
{
    char *word = NULL;
    /* The n value is arbitary; getline will allocate as much 
       space as needed to store the line as long as word is NULL */
    size_t n = 0;
    char *ls = game->letters; // For ease of access
    /* Return value grams is a pointer to an array of strings, 
       meaning it is a (char ***), pointer to an array of char *'s. */
    char *grams[MAX_GRAMS]; // TODO: free each string
    int j = 0; // For indexing grams
    int score;

    while (getline(&word, &n, f) > 0)
    {
        /* Check for anagram by checking if dictionary entry includes
           only letters from game->letters, AND that it contains the
           center letter, game-letters[0] */
        int len = strlen(word) - 1; // word ends '\n'

        if ((score = check_word(ls, word, len)) > 0)
        {
            /* Anagram found! Append it to the list of grams */
            fprintf(stdout, "%dpts\t%s\n", score, word);
            grams[j++] = strdup(word);
            game->score += score;
        }

        /* Set word NULL again for getline*/
        word = NULL;
    }

    free(word);

    return 0;
}

int main(int argc, char **argv)
{
    /* command line options:
     * -l,letters abcdefg -- the seven letters in the
     *                       spelling bee game. The first
     *                       letter must be the center letter.
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
            break;
        default :
            fprintf(stderr, "ERROR: unknown option\n");
        }
    }

    if (letters_str == NULL)
    {
        fprintf(stderr, "ERROR: No letters given\n");
        return -1;
    }

    /* Open the dictionary */
    FILE *f;
    if ((f = fopen("../data/spelling_bee_dict.txt", "r")) == NULL)
    {
        fprintf(stderr, "ERROR: spelling_bee_dict.txt not detected. Please run the script make_dict.py and try again.\n");
        return -1;
    }

    /* Initialize game data */
    int len = strlen(letters_str);
    game_t *game = init_game(letters_str, len);

    /* "Play"! */
    find_anagrams(game, f);

    /* Free data */
    free(letters_str);

    return 0;
}

/* TODO (one day...) :
 find a way to return an array of strings from find_anagrams().
 For now, it does not seem feasible (too confusing and unnecessary). */