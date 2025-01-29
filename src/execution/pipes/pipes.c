#include "../../../include/minishell.h"

void free_pipes(int **pipes, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

// CLOSE PIPES 🔐
void	close_pipes(int **pipes, int n)
{
	int i;

	i = 0;
    while (i < n)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
		i++;
    }
}

void	wait_pids(pid_t *pids, int n_pids)
{
	int i;

	i = 0;
	while (i < n_pids)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

// pid_t	*init_pids (int n_pids)
// {
// 	printf("%s\n", __func__);
// 	pid_t *pids;

// 	pids = malloc(sizeof(pid_t) * n_pids);
// 	if (pids == NULL)
// 		return (NULL);
// 	return (pids);
// }

int **pipe_init(int n_pipes)
{
	int **pipes;
	int i;

	if (n_pipes == 0)
		return (NULL);
	i = 0;
    pipes = malloc(sizeof(int *) * (n_pipes));
    if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < n_pipes)
    {
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL || pipe(pipes[i]) == -1)
		{
			perror("pipe failed");
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	ft_dprintf("pipes initialized\n");
	return (pipes);
}

void	set_pipe_ends(int **pipes, int position, int n_pipe) 
{
	int i;
    if (pipes)
	{
        if (position == 0) {
            dup2(pipes[position][1], STDOUT_FILENO);
        } else if (position == n_pipe) {
             dup2(pipes[position - 1][0], STDIN_FILENO);
        } else {
            dup2(pipes[position - 1][0], STDIN_FILENO);
            dup2(pipes[position][1], STDOUT_FILENO);
        }
		i = 0;
        while (i < n_pipe) 
		{
            close(pipes[i][0]);
            close(pipes[i][1]);
			i ++;
        }
	}
}


/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
// void	here_doc(char *limiter, int argc)
// {
// 	pid_t	reader;
// 	int		fd[2];
// 	char	*line;

// 	if (argc < 6)
// 		error();
// 	if (pipe(fd) == -1)
// 		error();
// 	reader = fork();
// 	if (reader == 0)
// 	{
// 		close(fd[0]);
// 		while (get_next_line(&line))
// 		{
// 			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 				exit(EXIT_SUCCESS);
// 			write(fd[1], line, ft_strlen(line));
// 		}
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		wait(NULL);
// 	}
// }