/*
** EPITECH PROJECT, 2024
** test_my_navy
** File description:
** Test file for my_navy
*/

#include "main.h"
#include "lib.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <unistd.h>

Test(error_handling, valid_pos, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/pos1.txt"};

    cr_assert_eq(error_handling(2, argv), 0);
}

Test(error_handling, wrong_argc, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle"};

    cr_assert_eq(error_handling(1, argv), 84);
}

Test(error_handling, no_file, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/pos.txt"};

    cr_assert_eq(error_handling(2, argv), 84);
}

Test(error_handling, file_too_small, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error1.txt"};

    cr_assert_eq(error_handling(2, argv), 84);
}

Test(error_handling, too_many_line, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error2.txt"};

    cr_assert_eq(error_handling(2, argv), 84);
}

Test(error_handling, wrong_line, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error3.txt"};

    cr_assert_eq(error_handling(2, argv), 84);
}

Test(error_handling, wrong_size, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error4.txt"};

    cr_assert_eq(error_handling(2, argv), 84);
}

Test(init_map, valid_pos, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/pos1.txt"};
    map_t *game = malloc(sizeof(map_t));

    cr_assert_eq(init_map(2, argv, game), 0);
}

Test(init_map, bunk_boat_line, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error5.txt"};
    map_t *game = malloc(sizeof(map_t));

    cr_assert_eq(init_map(2, argv, game), 84);
}

Test(init_map, bunk_boat_col, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/error/error6.txt"};
    map_t *game = malloc(sizeof(map_t));

    cr_assert_eq(init_map(2, argv, game), 84);
}

Test(display_map, display_maps, .init = redirect_all_std)
{
    char *argv[] = {"./navy_battle", "test/pos1.txt"};
    map_t *game = malloc(sizeof(map_t));

    init_map(2, argv, game);
    display_map(game);
    cr_assert_stdout_eq_str("\nmy navy:\n |A B C D E F G H\n-+---------------"
        "\n1|. . 2 . . . . .\n2|. . 2 . . . . .\n3|. . . . . . . .\n4|. . . 3"
        " 3 3 . .\n5|. 4 . . . . . .\n6|. 4 . . . . . .\n7|. 4 . 5 5 5 5 5\n8"
        "|. 4 . . . . . .\n\nenemy navy:\n |A B C D E F G H\n-+--------------"
        "-\n1|. . . . . . . .\n2|. . . . . . . .\n3|. . . . . . . .\n4|. . . "
        ". . . . .\n5|. . . . . . . .\n6|. . . . . . . .\n7|. . . . . . . .\n"
        "8|. . . . . . . .\n");
}
