#include "../../inc/pipex_bonus.h"

static void	free_pipe_array(t_pipex *pipex)
{
	int	i;

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
}

static void	free_cmd_paths(t_pipex *pipex)
{
	int	i;

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
	if (!pipex)
		return ;
	if (pipex->infile >= 0)
	{
		close(pipex->infile);
		pipex->infile = -1;
	}
	if (pipex->outfile >= 0)
	{
		close(pipex->outfile);
		pipex->outfile = -1;
	}
	if (pipex->cmds)
		free_cmds(pipex->cmds, pipex->cmd_count);
	free_cmd_paths(pipex);
	free_pipe_array(pipex);
	if (pipex->pids)
		free(pipex->pids);
}