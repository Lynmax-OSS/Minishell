/*open, close, read, write, dup, dup2, unlink, malloc, free, perror, strerror
Handle input/output redirection (>, <, >>, heredoc)*/

static int  open_infile(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (perror(file), -1);
    return (fd);
}

static int  open_outfile(char *file, int append)
{
    int fd;

    if (append)
        fd = open (file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open (file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (perror(file), -1);
    return (fd);    
}

int apply_redirections(t_redir *redir)
{
    int fd;

    while(redir)
    {
        fd = -1;
        if (ft_strcmp(redir->type, "<") == 0)
            fd = open_infile(redir->target);
        else if (ft_strcmp(redir->type, ">") == 0)
            fd = open_outfile(redir->target, 0);
        else if (ft_strcmp(redir->type, ">>") == 0)
            fd = open_outfile(redir->target, 1);
        else if (ft_strcmp(redir->type, "<<") == 0)
            fd = open(redir->target, O_RDONLY);
        if (fd < 0)
            return (-1);
        if (ft_strcmp(redir->type, "<") == 0
            || ft_strcmp(redir->type, "<<") == 0)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        redir = redir->next;
    }
    return (0);
}
