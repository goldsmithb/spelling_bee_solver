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
        fprintf(stderr, "ERROR: Malloc erro\n");
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

char **find_anagrams(game_t *game, FILE *f)
{
    char *word = NULL;
    /* This value is arbitary; getline will allocate as much 
       space as needed to store the line as long as word is NULL */
    int n = 0;
    char *ls = game->letters; // For ease of acces
    char *grams[MAX_GRAMS]; // TODO: free
    int j = 0; // For indexing grams 

    while (getline(&word, &n, f) > 0)
    {
        /* Check for anagram by checking if dictionary entry includes
           only letters from game->letters, and that it contains the
           center letter, game-letters[0] */
        /* First, check for center letter */
        int len = strlen(word) - 1; // word ends '\n'

        if (check_word(ls, word, len))
        {
            /* Anagram found! Append it to the list of grams */
            grams[j++] = strdup(word);
        }
        /* Set word NULL again for getline*/
        word = NULL;
    }

    free(word);    
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
        default :
            fprintf(stderr, "ERROR: unknown option");
        }
    }

    if (letters_str == NULL)
    {
        fprintf(stderr, "ERROR: No letters given");
        return -1;
    }

    FILE *f;
    if ((f = fopen("../data/spellfind_anagramsing_bee_dict.txt", "r")) == NULL)
    {
        fprintf(stderr, "ERROR: spelling_bee_dict.txt not detected. Please \
                         run the script make_dict.py and try again.");
        return -1;
    }

    /* Initialize game data */
    int len = strlen(letters_str);
    game_t *game = init_game(letters_str, len);

    game->score = find_anagrams(game, f);

    return 0;
}