/*
** Send signal to attack me
*/

#include "main.h"
#include "lib.h"
#include <sys/types.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void wait_attack(int *letter, int *map_line)
{
    int attack = 0;

    while (attack == 0) {
        if (navy.user2 == 1) {
            navy.user2 = 0;
            attack = 1;
        }
    }
    if (navy.user1 % 8 == 0)
        *letter = 72;
    else
        *letter = (navy.user1 % 8) + 64;
    *map_line = ((navy.user1 - 1) / 8) + 49;
}

void wait_result(char *line, map_t *game)
{
    int result = 0;

    while (result == 0) {
        if (navy.user1 == 1) {
            result = 1;
            navy.user1 = 0;
            game->enemy_map[line[1] - 49][line[0] - 65] = 'o';
            lib_printf("\nresult: %c%c:missed\n", line[0], line[1]);
        }
        if (navy.user2 == 1) {
            result = 1;
            navy.user2 = 0;
            game->enemy_map[line[1] - 49][line[0] - 65] = 'x';
            lib_printf("\nresult: %c%c:hit\n", line[0], line[1]);
        }
    }
}

static void send_enemy_attack(char *line)
{
    for (int i = 0; i < ((line[0] - 64) + ((line[1] - 49) * 8)); i++) {
        kill(navy.pid1, SIGUSR1);
        usleep(100);
    }
    kill(navy.pid1, SIGUSR2);
}

static void input_enemy_case(char **line, map_t *game)
{
    size_t len = 0;
    ssize_t lineSize = 0;

    lib_printf("\nattack: \x1B[3m");
    lineSize = getline(line, &len, stdin);
    lib_printf("\x1B[m");
    if (check_case(*line, lineSize) == 0)
        send_enemy_attack(*line);
    else {
        lib_printf("\nwrong position\n");
        input_enemy_case(line, game);
    }
}

int enemy_attack(map_t *game)
{
    int letter = 0;
    int map_line = 0;
    char *line = NULL;

    lib_printf("\nwaiting for enemy's attack...\n");
    wait_attack(&letter, &map_line);
    if (check_hit(game) == 1) {
        kill(navy.pid1, SIGUSR2);
        lib_printf("\nresult: %c%c:hit\n", letter, map_line);
    } else {
        kill(navy.pid1, SIGUSR1);
        lib_printf("\nresult: %c%c:missed\n", letter, map_line);
    }
    navy.user1 = 0;
    if (check_my_boat(game->my_map) == 1)
        return 1;
    input_enemy_case(&line, game);
    wait_result(line, game);
    return check_enemy_boat(game->enemy_map);
}
