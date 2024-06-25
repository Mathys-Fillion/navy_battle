/*
** Duplicate src to str and return it
*/

#include "lib.h"
#include <unistd.h>
#include <stdlib.h>

char *lib_strdup(char const *src)
{
    char *str;
    int i = 0;

    if (src == NULL)
        return NULL;
    str = malloc(sizeof(char) * (lib_strlen(src) + 1));
    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return str;
}
