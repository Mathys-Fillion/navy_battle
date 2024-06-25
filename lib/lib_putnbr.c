/*
** Display all the possible values of an int
*/

#include "lib.h"

void lib_putnbr(int nbr)
{
    int divided = 1;
    int result = 0;

    if (nbr < 0) {
        if (nbr == -2147483648) {
            lib_putnbr(-214748364);
            lib_putchar('8');
            return;
        }
        nbr = -nbr;
        lib_putchar('-');
    }
    for (int i = 0; i < (lib_nbrlen(nbr) - 1); i++)
        divided = divided * 10;
    for (int j = 0; j < lib_nbrlen(nbr); j++) {
        result = (nbr / divided) % 10;
        divided = divided / 10;
        lib_putchar(result + 48);
    }
}
