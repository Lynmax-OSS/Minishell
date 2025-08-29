int run_external(char **args, char **envp)
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid < 0)
        return (perror("fork"), -1);
    if (pid == 0)
    {
        if (execve(args[0], args, envp) == -1)
        {
            perror("execve");
            exit(127);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (0);
}
