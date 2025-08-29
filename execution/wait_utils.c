#include "../minishell.h"

/*
Wait for all child processes
*/

void    wait_all_children(int *status)
{
    pid_t   pid;
    
    while ((pid = waitpid(-1, status, 0)) > 0)
        continue ;
}
