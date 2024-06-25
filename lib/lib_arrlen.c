/*
** Return the arr len
*/

#include <stdlib.h>

int lib_arrlen(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return 0;
    while (arr[i] != NULL)
        i++;
    return i;
}
