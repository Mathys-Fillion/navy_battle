/*
** Mini version of printf
*/

#include "lib.h"
#include <stdarg.h>

static void find_flag(const char *format, int i, va_list list)
{
    if (format[i] == 'c')
        lib_putchar(va_arg(list, int));
    if (format[i] == 's')
        lib_putstr(va_arg(list, char *));
    if (format[i] == 'i' ||
        format[i] == 'd')
        lib_putnbr(va_arg(list, int));
    if (format[i] == '%')
        lib_putchar('%');
}

void lib_printf(const char *format, ...)
{
    va_list list;
    int i = 0;

    va_start(list, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            find_flag(format, (i + 1), list);
            i += 2;
        } else {
            lib_putchar(format[i]);
            i++;
        }
    }
    va_end(list);
}
