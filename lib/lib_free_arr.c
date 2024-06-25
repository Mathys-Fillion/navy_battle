/*
** Free the allocated memory of an arr
*/

#include <stdlib.h>

void lib_free_arr(char **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    free(arr);
}
