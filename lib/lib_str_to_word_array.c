/*
** Split a line into multiple word according to the delimiters
*/

#include <stdlib.h>

static int check_delimiters(char letter, char *delimiters)
{
    for (int i = 0; delimiters[i] != '\0'; i++) {
        if (letter == delimiters[i])
            return 1;
    }
    return 0;
}

static void check_until_word(char *str, int *i, char *delimiters)
{
    while (check_delimiters(str[*i], delimiters) == 0 && str[*i] != '\0')
        (*i)++;
    (*i)--;
}

static int get_nb_words(char *str, char *delimiters)
{
    int words = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (check_delimiters(str[i], delimiters) == 0) {
            check_until_word(str, &i, delimiters);
            words++;
        }
    }
    return words;
}

static int get_word_len(char *str, char *delimiters, int *pointer)
{
    int len = 0;

    while (check_delimiters(str[*pointer], delimiters) == 1)
        (*pointer)++;
    for (int i = *pointer; check_delimiters(str[i], delimiters) == 0 &&
        str[i] != '\0'; i++) {
        len++;
    }
    return len;
}

static char *get_word(char *str, int *pointer, char *delimiters)
{
    int len_word = get_word_len(str, delimiters, pointer);
    char *word = malloc(sizeof(char) * (len_word + 1));
    int j = 0;

    for (int i = *pointer; i < len_word + *pointer; i++) {
        word[j] = str[i];
        j++;
    }
    *pointer += (len_word + 1);
    word[j] = '\0';
    return word;
}

char **lib_str_to_word_array(char *str, char *delimiters)
{
    int nb_words = get_nb_words(str, delimiters);
    int pointer = 0;
    char **array = malloc((sizeof(char *) * (nb_words + 1)));

    for (int i = 0; i < nb_words; i++)
        array[i] = get_word(str, &pointer, delimiters);
    array[nb_words] = NULL;
    return array;
}
