/*
** Initialization and display of the maps
*/

#include "main.h"
#include "lib.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void display_map(map_t *game)
{
    lib_printf("\nmy navy:\n |A B C D E F G H\n-+---------------\n");
    for (int i = 0; i < 8; i++) {
        lib_printf("%i|%c", i + 1, game->my_map[i][0]);
        for (int j = 1; j < 8; j++)
            lib_printf(" %c", game->my_map[i][j]);
        lib_putchar('\n');
    }
    lib_printf("\nenemy navy:\n |A B C D E F G H\n-+---------------\n");
    for (int i = 0; i < 8; i++) {
        lib_printf("%i|%c", i + 1, game->enemy_map[i][0]);
        for (int j = 1; j < 8; j++)
            lib_printf(" %c", game->enemy_map[i][j]);
        lib_putchar('\n');
    }
}

static char **get_empty_map(void)
{
    char **map = malloc(sizeof(char *) * 9);

    for (int i = 0; i < 8; i++)
        map[i] = malloc(sizeof(char) * 9);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            map[i][j] = '.';
        map[i][8] = '\0';
    }
    map[8] = NULL;
    return map;
}

static int place_horizontal(char *content, char **map, int line)
{
    for (int i = 0; i < (content[0] - 48); i++) {
        if (map[line - 1][i + (content[2] - 65)] == '.')
            map[line - 1][i + (content[2] - 65)] = content[0];
        else
            return 84;
    }
    return 0;
}

static int place_vertical(char *content, char **map, int col)
{
    for (int i = 0; i < (content[0] - 48); i++) {
        if (map[i + ((content[3] - 48) - 1)][col] == '.')
            map[i + ((content[3] - 48) - 1)][col] = content[0];
        else
            return 84;
    }
    return 0;
}

static int put_boat(char *content, char **map)
{
    char **lines = lib_str_to_word_array(content, "\n");
    int error = 0;

    free(content);
    for (int i = 0; lines[i] != NULL; i++) {
        if (lines[i][3] == lines[i][6])
            error = place_horizontal(lines[i], map, (lines[i][3] - 48));
        else
            error = place_vertical(lines[i], map, (lines[i][2] - 65));
        if (error == 84) {
            lib_free_arr(lines);
            return 84;
        }
    }
    lib_free_arr(lines);
    return 0;
}

static int put_boats(char *argv, char **map)
{
    int fd = open(argv, O_RDONLY);
    char *content = malloc(sizeof(char) * 32 + 1);

    read(fd, content, 32 + 1);
    content[32] = '\0';
    close(fd);
    return put_boat(content, map);
}

int init_map(int argc, char **argv, map_t *game)
{
    game->my_map = get_empty_map();
    game->enemy_map = get_empty_map();
    return put_boats(argv[argc - 1], game->my_map);
}
