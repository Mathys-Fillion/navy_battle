/*
** Display the characters of a string
*/

#include "lib.h"

void lib_putstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        lib_putchar(str[i]);
}
