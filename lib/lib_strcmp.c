/*
** Compare two string and return 1 if identical
*/

#include "lib.h"

int lib_strcmp(char const *s1, char const *s2)
{
    int s1_len = lib_strlen(s1);
    int s2_len = lib_strlen(s2);

    if (s1_len != s2_len)
        return 0;
    for (int i = 0; i < s1_len; i++) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}
