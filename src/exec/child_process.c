#include "../../inc/pipex_bonus.h"

static void	setup_stdin(t_pipex *pipex, int i)
{
	int	null_fd;

	if (i == 0)
	{
		if (pipex->infile >= 0)
		{
			if (dup2(pipex->infile, STDIN_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}
		}
		else
		{
			null_fd = open("/dev/null", O_RDONLY);
			if (null_fd >= 0)
			{
				dup2(null_fd, STDIN_FILENO);
				close(null_fd);
			}
		}
	}
	else if (dup2(pipex->pipes[i - 1][0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
}

static void	setup_stdout(t_pipex *pipex, int i)
{
	int	null_fd;

	if (i == pipex->cmd_count - 1)
	{
		if (pipex->outfile >= 0)
		{
			if (dup2(pipex->outfile, STDOUT_FILENO) < 0)
			{
				perror("dup2");
				null_fd = open("/dev/null", O_WRONLY);
				if (null_fd >= 0)
				{
					dup2(null_fd, STDOUT_FILENO);
					close(null_fd);
				}
			}
		}
		else
		{
			null_fd = open("/dev/null", O_WRONLY);
			if (null_fd >= 0)
			{
				dup2(null_fd, STDOUT_FILENO);
				close(null_fd);
			}
		}
	}
	else if (dup2(pipex->pipes[i][1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
}

static void	exit_child(t_pipex *pipex, int exit_code)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	close_pipes(pipex);
	free_pipex(pipex);
		if (pipex->env_path)
			free_env_path(pipex->env_path);
	exit(exit_code);
}

void	child_process(t_pipex *pipex, int i, char **envp)
{
	setup_stdin(pipex, i);
	setup_stdout(pipex, i);
	close_pipes(pipex);
	if (!pipex->cmds[i] || !pipex->cmds[i][0] || pipex->cmds[i][0][0] == '\0')
	{
		ft_putstr_fd("Error: Empty command\n", 2);
		exit_child(pipex, 127);
	}
	if (!pipex->cmd_paths[i])
	{
		ft_putstr_fd("Command not found: ", 2);
		if (pipex->cmds[i][0])
			ft_putstr_fd(pipex->cmds[i][0], 2);
		ft_putstr_fd("\n", 2);
		exit_child(pipex, 127);
	}
	if (execve(pipex->cmd_paths[i], pipex->cmds[i], envp) < 0)
	{
		perror("execve");
		exit_child(pipex, 127);
	}
}
