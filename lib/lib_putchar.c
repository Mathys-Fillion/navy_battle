/*
** Write a character
*/

#include <unistd.h>

void lib_putchar(char c)
{
    write(1, &c, 1);
}
