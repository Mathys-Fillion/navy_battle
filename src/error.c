/*
** Error handling of navy_battle
*/

#include "lib.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

static int check_length(char *line, int index)
{
    int length = 0;

    if (line[2] != line[5])
        length = lib_abs(line[5] - line[2]) + 1;
    if (line[3] != line[6])
        length = lib_abs(line[6] - line[3]) + 1;
    if (length != index)
        return 84;
    return 0;
}

static int check_line(char *line, int index)
{
    if (line[0] - '0' != index ||
        line[1] != ':' ||
        (line[2] < 'A' || line[2] > 'H') ||
        (line[3] < '1' || line[3] > '8') ||
        line[4] != ':' ||
        (line[5] < 'A' || line[5] > 'H') ||
        (line[6] < '1' || line[6] > '8'))
        return 84;
    return 0;
}

static int check_lines(char *content)
{
    char **lines = lib_str_to_word_array(content, "\n");

    free(content);
    if (lib_arrlen(lines) != 4) {
        lib_free_arr(lines);
        return 84;
    }
    for (int i = 0; lines[i] != NULL; i++) {
        if (check_line(lines[i], i + 2) == 84 ||
            check_length(lines[i], i + 2) == 84) {
            lib_free_arr(lines);
            return 84;
        }
    }
    lib_free_arr(lines);
    return 0;
}

static int check_file(char *argv)
{
    int fd = open(argv, O_RDONLY);
    struct stat file_info;
    char *content;

    if (fd == -1 || stat(argv, &file_info) == -1)
        return 84;
    content = malloc(sizeof(char) * file_info.st_size + 1);
    if (content == NULL || file_info.st_size != 32 ||
        read(fd, content, file_info.st_size + 1) == -1)
        return 84;
    content[file_info.st_size] = '\0';
    close(fd);
    return check_lines(content);
}

int error_handling(int argc, char **argv)
{
    if (argc != 2 && argc != 3)
        return 84;
    return check_file(argv[argc - 1]);
}
