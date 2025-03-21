#include "../../inc/pipex_bonus.h"

void	create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = (int **)malloc(sizeof(int *) * pipex->pipe_count);
	if (!pipex->pipes)
		return ;
	i = 0;
	while (i < pipex->pipe_count)
	{
		pipex->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->pipes[i] || pipe(pipex->pipes[i]) < 0)
		{
			while (--i >= 0)
				free(pipex->pipes[i]);
			free(pipex->pipes);
			pipex->pipes = NULL;
			return ;
		}
		i++;
	}
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipe_count)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

void	free_cmds(char ***cmds, int cmd_count)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (i < cmd_count)
	{
		if (cmds[i])
		{
			j = 0;
			while (cmds[i][j])
			{
				free(cmds[i][j]);
				j++;
			}
			free(cmds[i]);
		}
		i++;
	}
	free(cmds);
}

void	free_env_path(char **env_path)
{
	int	i;

	if (!env_path)
		return ;
	i = 0;
	while (env_path[i])
	{
		free(env_path[i]);
		i++;
	}
	free(env_path);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->cmds)
		free_cmds(pipex->cmds, pipex->cmd_count);
	if (pipex->cmd_paths)
	{
		i = 0;
		while (i < pipex->cmd_count)
		{
			if (pipex->cmd_paths[i])
				free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->pipe_count)
		{
			if (pipex->pipes[i])
				free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
	if (pipex->pids)
		free(pipex->pids);
}
