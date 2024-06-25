/*
** Loop of the game
*/

#include "main.h"
#include "lib.h"
#include <stdlib.h>
#include <unistd.h>

navy_t navy = {0};

static int loop(map_t *game, int argc, int *value)
{
    display_map(game);
    if (argc == 2)
        *value = my_attack(game);
    else
        *value = enemy_attack(game);
    if (*value == 0)
        return print_win(game, value);
    if (*value == 1)
        return print_loose(game, value);
    return 0;
}

int start_game(int argc, char **argv)
{
    map_t *game = malloc(sizeof(map_t));
    int value = 0;

    if (game == NULL || init_map(argc, argv, game) == 84)
        return 84;
    start_connexion(argc, argv);
    while (loop(game, argc, &value) == 0);
    lib_free_arr(game->my_map);
    lib_free_arr(game->enemy_map);
    free(game);
    return value;
}
