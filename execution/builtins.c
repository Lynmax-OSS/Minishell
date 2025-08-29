#include "../minishell.h"

/*chdir, getcwd, write, printf, malloc, free, perror
Builtin commands (cd, echo, exit, pwd)*/

int ft_echo(char **args)
{
    int i;
    int newline;
    int j;

    i = 1;
    newline = 1;
    if (args[i] && args[1][0] == '-' && args[i][1] == 'n' && args[1][2] == '\0')
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline == 1)
        write(1, "\n", 1);
    return (0);
}

int ft_exit(char **args)
{
    int status;

    status = 0;
    write (1, "exit\n", 5);
    if (args[1])
    {
        status = ft_atoi(args[1]);
        if (args[2])
        {
            fprintf(stderr, "minishell: exit: too many arguments\n");
            return (1);
        }
    }
    exit(status);
}

int ft_pwd(void)
{
    char    buffer[1024];

    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        printf("%s\n", buffer);
        return (0);
    }
    perror("pwd");
    return (1);
}
