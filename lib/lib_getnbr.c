/*
** Return a number from a string
*/

static int add_operator(int operator, int nbr)
{
    if ((operator % 2) == 1)
        nbr = -nbr;
    return nbr;
}

int lib_getnbr(char const *str)
{
    int i = 0;
    int nbr = 0;
    int operator = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            operator++;
        i++;
    }
    while (str[i] != '\0') {
        if (str[i] < 48 || str[i] > 57)
            return add_operator(operator, nbr);
        nbr = nbr * 10 + (str[i] - 48);
        i++;
    }
    return add_operator(operator, nbr);
}
