/*######################################
# University of Information Technology #
26
# IT007 Operating System #
# <Your name>, <your Student ID> #
# File: test_fork.c #
######################################*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
    __pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        printf("PARENTS | PID = %ld | PPID = %ld\n", (long)getpid(), (long)getppid());
        if (argc > 2)
            printf("PARENTS | There are %d arguments\n", argc - 1);
        wait(NULL);
    }
    if (pid == 0)
    {
        printf("CHILDREN | PID = %ld | PPID = %ld\n",(long)getpid(), (long)getppid());
        printf("CHILDREN | List of arguments: \n");
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }
    exit(0);
}


/*
    The program is compiled and executed with three arguments: t1, t2, and t3.

    The main() function begins execution.

    fork() is called, creating a new child process.

    In the parent process (identified by pid > 0), the printf statement prints the parent's process ID (PID) and parent's parent process ID (PPID). If there are more than two arguments, it prints the number of arguments passed to the program minus one (because the first argument is the program name itself). The wait(NULL) function call ensures that the parent process waits for the child process to complete before continuing execution.

    In the child process (identified by pid == 0), the printf statement prints the child's PID and its parent's PID (which is the PID of the parent process). Then, it prints each argument passed to the program.

    Both the parent and child processes exit with exit(0) after printing their respective information.

    Finally, the shell prompt is displayed, indicating that the program execution has completed.
*/