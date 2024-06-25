/*
** Lib header for navy_battle programm
*/

#ifndef LIB_H_
    #define LIB_H_
    #define NOT_SAME 0
    #define SAME 1

void redirect_all_std(void);

void lib_putchar(char c);
void lib_putstr(char const *str);
void lib_putnbr(int nbr);
void lib_printf(const char *format, ...);
void lib_free_arr(char **arr);

int lib_strlen(char const *str);
int lib_nbrlen(int nbr);
int lib_getnbr(char const *str);
int lib_strcmp(char const *s1, char const *s2);
int lib_abs(int nbr);
int lib_arrlen(char **arr);

char *lib_strdup(char const *src);

char **lib_str_to_word_array(char *str, char *delimiters);

#endif /* LIB_H_ */
