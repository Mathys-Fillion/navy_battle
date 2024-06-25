/*
** Navy_battle
** Terminal version of battleship game
*/

#include "./include/main.h"
#include "./include/lib.h"

int display_help(void)
{
    lib_printf("USAGE\n\t./navy_battle [first_player_pid] navy_positions\nDESC"
        "RIPTION\n\tfirst_player_pid: only for the 2nd player, pid of the firs"
        "t player.\n\tnavy_positions: file representing the positions of the s"
        "hips.\n");
    return 0;
}

int main(int argc, char **argv)
{
    if (lib_strcmp(argv[1], "-h") == SAME)
        return display_help();
    if (error_handling(argc, argv) == 84)
        return 84;
    return start_game(argc, argv);
}
