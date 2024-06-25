/*
** Main header for navy_battle programm
*/

#ifndef MAIN_H_
    #define MAIN_H_
    #include <sys/types.h>

typedef struct navy_s {
    int user1;
    int user2;
    int pid1;
    int pid2;
} navy_t;

typedef struct map_s {
    char **my_map;
    char **enemy_map;
} map_t;

extern navy_t navy;

int display_help(void);
int error_handling(int argc, char **argv);
int start_game(int argc, char **argv);
int init_map(int argc, char **argv, map_t *game);
void display_map(map_t *game);
void start_connexion(int argc, char **argv);
int my_attack(map_t *game);
int enemy_attack(map_t *game);
void wait_result(char *line, map_t *game);
void wait_attack(int *letter, int *map_line);
int check_case(char *line, ssize_t lineSize);
int check_hit(map_t *game);
int check_my_boat(char **map);
int check_enemy_boat(char **map);
int print_win(map_t *game, int *win);
int print_loose(map_t *game, int *win);

#endif /* MAIN_H_ */
