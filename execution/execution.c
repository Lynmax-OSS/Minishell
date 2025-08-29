#include "../minishell.h"

/*fork, execve, wait, waitpid, wait3, wait4, kill, malloc, free, perror, strerror
Execute external commands, manage child processes*/

int execute_commands(t_cmd *head, char **envp)
{
    t_cmd   *cmd;
    int     status;

    status = 0;
    cmd = head;
    while (cmd)
    {
        if (is_builtin(cmd->args))
        {
            if (apply_redirections(cmd->redir) == 0)
                run_builtin(cmd->args);
        }
        else
        {
            if (apply_redirections(cmd->redir) == 0)
                run_external(cmd->args, envp);
        }
        cmd = cmd->next;
    }
    wait_all_children(&status);
    return (0);
}
