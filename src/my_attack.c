/*
** Send signal to attack the enne
*/

#include "main.h"
#include "lib.h"
#include <sys/types.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int check_hit(map_t *game)
{
    int x = (navy.user1 - 1) / 8;
    int y = (navy.user1 - 1) - (x * 8);

    if (game->my_map[x][y] == '.') {
        game->my_map[x][y] = 'o';
        return 0;
    }
    if (game->my_map[x][y] == 'o' ||
        game->my_map[x][y] == 'x')
        return 0;
    game->my_map[x][y] = 'x';
    return 1;
}

int check_case(char *line, ssize_t lineSize)
{
    if (lineSize != 3)
        return 84;
    if (line[0] < 'A' || line[0] > 'H')
        return 84;
    if (line[1] < '1' || line[1] > '8')
        return 84;
    return 0;
}

static void send_my_attack(char *line)
{
    for (int i = 0; i < ((line[0] - 64) + ((line[1] - 49) * 8)); i++) {
        kill(navy.pid2, SIGUSR1);
        usleep(100);
    }
    kill(navy.pid2, SIGUSR2);
}

static void input_my_case(char **line, map_t *game)
{
    size_t len = 0;
    ssize_t lineSize = 0;

    lib_printf("\nattack: \x1B[3m");
    lineSize = getline(line, &len, stdin);
    lib_printf("\x1B[m");
    if (check_case(*line, lineSize) == 0)
        send_my_attack(*line);
    else {
        lib_printf("\nwrong position\n");
        input_my_case(line, game);
    }
}

int my_attack(map_t *game)
{
    int letter = 0;
    int map_line = 0;
    char *line = NULL;

    input_my_case(&line, game);
    wait_result(line, game);
    if (check_enemy_boat(game->enemy_map) == 0)
        return 0;
    lib_printf("\nwaiting for enemy's attack...\n");
    wait_attack(&letter, &map_line);
    if (check_hit(game) == 1) {
        kill(navy.pid2, SIGUSR2);
        lib_printf("\nresult: %c%c:hit\n", letter, map_line);
    } else {
        kill(navy.pid2, SIGUSR1);
        lib_printf("\nresult: %c%c:missed\n", letter, map_line);
    }
    navy.user1 = 0;
    return check_my_boat(game->my_map);
}
