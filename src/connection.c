/*
** Connect the two terminal together
*/

#include "main.h"
#include "lib.h"
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void launch_connexion(char *pid)
{
    int connected = 0;

    navy.pid1 = lib_getnbr(pid);
    navy.pid2 = getpid();
    lib_printf("my_pid: %i\n\n", navy.pid2);
    kill(navy.pid1, SIGUSR2);
    while (connected == 0) {
        if (navy.user2 == 1) {
            connected = 1;
            navy.user2 = 0;
        }
    }
    lib_printf("successfully connected\n");
}

static void wait_connexion(void)
{
    int connected = 0;

    navy.pid1 = getpid();
    lib_printf("my_pid: %i\n\n", navy.pid1);
    lib_printf("waiting for enemy connection...\n\n");
    while (connected == 0) {
        if (navy.user2 == 1) {
            connected = 1;
            navy.user2 = 0;
        }
    }
    kill(navy.pid2, SIGUSR2);
    lib_printf("enemy connected\n");
}

void handler(int sig, siginfo_t *info, void *context)
{
    context = context;
    if (sig == 10)
        navy.user1++;
    if (sig == 12) {
        navy.user2++;
        if (navy.user2 == 1 && navy.pid2 == 0)
            navy.pid2 = info->si_pid;
    }
}

void start_connexion(int argc, char **argv)
{
    struct sigaction act = { 0 };

    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = &handler;
    sigaction(10, &act, NULL);
    sigaction(12, &act, NULL);
    if (argc == 2)
        wait_connexion();
    else
        launch_connexion(argv[1]);
}
