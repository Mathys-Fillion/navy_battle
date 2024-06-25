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

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(lib_putchar, print_char, .init = redirect_all_std)
{
    lib_putchar('@');
    cr_assert_stdout_eq_str("@");
}

Test(lib_putstr, print_str, .init = redirect_all_std)
{
    lib_putstr("Hello");
    cr_assert_stdout_eq_str("Hello");
}

Test(lib_putnbr, print_nbr, .init = redirect_all_std)
{
    lib_putnbr(42);
    cr_assert_stdout_eq_str("42");
}

Test(lib_putnbr, print_max_nbr, .init = redirect_all_std)
{
    lib_putnbr(-2147483648);
    cr_assert_stdout_eq_str("-2147483648");
}

Test(lib_printf, print_sentence, .init = redirect_all_std)
{
    lib_printf("%s world %c %i%%", "Hello", '!', 42);
    cr_assert_stdout_eq_str("Hello world ! 42%");
}

Test(lib_strlen, get_str_len, .init = redirect_all_std)
{
    cr_assert_eq(lib_strlen("Hello"), 5);
}

Test(lib_strlen, get_null_str_len, .init = redirect_all_std)
{
    cr_assert_eq(lib_strlen(NULL), 0);
}

Test(lib_nbrlen, get_nbr_len, .init = redirect_all_std)
{
    cr_assert_eq(lib_nbrlen(42), 2);
}

Test(lib_nbrlen, get_null_nbr_len, .init = redirect_all_std)
{
    cr_assert_eq(lib_nbrlen(0), 1);
}

Test(lib_getnbr, get_pos_nbr, .init = redirect_all_std)
{
    cr_assert_eq(lib_getnbr("42Hello"), 42);
}

Test(lib_getnbr, get_neg_nbr, .init = redirect_all_std)
{
    cr_assert_eq(lib_getnbr("-42"), -42);
}

Test(lib_strcmp, same_str, .init = redirect_all_std)
{
    cr_assert_eq(lib_strcmp("Hello", "Hello"), SAME);
}

Test(lib_strcmp, not_same_str, .init = redirect_all_std)
{
    cr_assert_eq(lib_strcmp("Hello", "world"), NOT_SAME);
}

Test(lib_strcmp, not_same_str_len, .init = redirect_all_std)
{
    cr_assert_eq(lib_strcmp("Hello", "42"), NOT_SAME);
}

Test(lib_abs, get_abs_nbr, .init = redirect_all_std)
{
    cr_assert_eq(lib_abs(-42), 42);
}

Test(lib_strdup, dup_str, .init = redirect_all_std)
{
    cr_assert_str_eq(lib_strdup("Hello"), "Hello");
}

Test(lib_strdup, dup_null_str, .init = redirect_all_std)
{
    cr_assert_null(lib_strdup(NULL));
}

Test(lib_arrlen, get_arr_len, .init = redirect_all_std)
{
    char *arr[] = {"Hello", "world", "42", NULL};

    cr_assert_eq(lib_arrlen(arr), 3);
}

Test(lib_arrlen, get_null_arr_len, .init = redirect_all_std)
{
    char **arr = NULL;

    cr_assert_eq(lib_arrlen(arr), 0);
}

Test(lib_free_arr, free_arr, .init = redirect_all_std)
{
    char **arr = malloc(sizeof(char *) * 2);

    arr[0] = lib_strdup("Hello");
    arr[1] = NULL;
    lib_free_arr(arr);
    arr = NULL;
    cr_assert_null(arr);
}

Test(lib_free_arr, free_null_arr, .init = redirect_all_std)
{
    char **arr = NULL;

    lib_free_arr(arr);
    cr_assert_null(arr);
}

Test(lib_str_to_word_array, get_words, .init = redirect_all_std)
{
    char **arr = lib_str_to_word_array("Hello world !", " o");

    cr_assert_str_eq(arr[0], "Hell");
    lib_free_arr(arr);
}
