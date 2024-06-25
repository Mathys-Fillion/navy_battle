/*
** Return the str len
*/

#include <stddef.h>

int lib_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i] != '\0')
        i++;
    return i;
}
