#include "../minishell.h"

int is_builtin(char **args)
{
    if (!args || !args[0])
        return (0);
    if (ft_strcmp(args[0], "echo") == 0)
        return (1);
    if (ft_strcmp(args[0], "pwd") == 0)
        return (1);
    if (ft_strcmp(args[0], "exit") == 0)
        return (1);
        //cd, export, unset, env
    return (0);
}

int run_builtin(char **args)
{
    if (!args || !args[0])
        return (0);
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (ft_pwd());
    else if (ft_strcmp(args[0], "exit") == 0)
        return (ft_exit(args));
    // later: cd, export, unset, env
    return (0);
}
