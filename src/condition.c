/*
** Check and print win and loss condition
*/

#include "main.h"
#include "lib.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int print_win(map_t *game, int *win)
{
    display_map(game);
    lib_printf("\nI won\n");
    *win = 0;
    return 1;
}

int print_loose(map_t *game, int *win)
{
    display_map(game);
    lib_printf("\nEnemy won\n");
    *win = 1;
    return 1;
}

static void count_x(char **map, int i, int *x)
{
    for (int j = 0; j < 8; j++) {
        if (map[i][j] == 'x')
            (*x)++;
    }
}

int check_enemy_boat(char **map)
{
    int x = 0;

    for (int i = 0; i < 8; i++)
        count_x(map, i, &x);
    if (x == 14)
        return 0;
    return 2;
}

int check_my_boat(char **map)
{
    int x = 0;

    for (int i = 0; i < 8; i++)
        count_x(map, i, &x);
    if (x == 14)
        return 1;
    return 2;
}
