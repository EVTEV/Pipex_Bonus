#include "../../inc/pipex_bonus.h"

static int	fork_process(t_pipex *pipex, int i, char **envp)
{
	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
		return (1);
	if (pipex->pids[i] == 0)
		child_process(pipex, i, envp);
	return (0);
}

static int	handle_fork_error(t_pipex *pipex, int i)
{
	perror("fork");
	while (--i >= 0)
		waitpid(pipex->pids[i], NULL, 0);
	free(pipex->pids);
	pipex->pids = NULL;
	close_pipes(pipex);
	return (1);
}

static int	create_child_processes(t_pipex *pipex, char **envp)
{
	int	i;

	pipex->pids = (pid_t *)malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipex->pids)
		return (1);
	i = 0;
	while (i < pipex->cmd_count)
	{
		if (fork_process(pipex, i, envp) != 0)
			return (handle_fork_error(pipex, i));
		i++;
	}
	return (0);
}

static int	wait_for_child_processes(t_pipex *pipex)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	i = 0;
	while (i < pipex->cmd_count)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (i == pipex->cmd_count - 1)
			last_status = get_exit_status(status);
		i++;
	}
	return (last_status);
}

int	exec_command(t_pipex *pipex, char **envp)
{
	int	last_status;

	if (create_child_processes(pipex, envp) != 0)
		return (1);
	close_pipes(pipex);
	last_status = wait_for_child_processes(pipex);
	free(pipex->pids);
	pipex->pids = NULL;
	return (last_status);
}
