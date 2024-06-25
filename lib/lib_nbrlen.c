/*
** Return the nbr len
*/

int lib_nbrlen(int nbr)
{
    int len = 0;

    if (nbr == 0)
        return 1;
    while (nbr != 0) {
        nbr /= 10;
        len++;
    }
    return len;
}
