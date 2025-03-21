#include "../../inc/pipex_bonus.h"

int	exec_command(t_pipex *pipex, char **envp)
{
	int	i;
	int	status;
	int	last_status;

	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		return (1);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] < 0)
		{
			perror("fork");
			while (--i >= 0)
				waitpid(pipex->pids[i], NULL, 0);
			free(pipex->pids);
			pipex->pids = NULL;
			close_pipes(pipex);
			return (1);
		}
		if (pipex->pids[i] == 0)
			child_process(pipex, i, envp);
		i++;
	}
	close_pipes(pipex);
	last_status = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (i == pipex->cmd_count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNAL(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pipex->pids);
	pipex->pids = NULL;
	return (last_status);
}
