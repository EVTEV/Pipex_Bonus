#include "../../inc/pipex_bonus.h"

static void	setup_stdin_first_cmd(t_pipex *pipex)
{
	if (pipex->infile >= 0)
	{
		if (dup2(pipex->infile, STDIN_FILENO) < 0)
			msg_error("dup2");
	}
	else
		close(STDIN_FILENO);
}

void	setup_stdin(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		setup_stdin_first_cmd(pipex);
	}
	else if (dup2(pipex->pipes[i - 1][0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
}
static void	setup_stdout_last_cmd(t_pipex *pipex)
{
	if (pipex->outfile >= 0)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
		dup2(pipex->pipes[pipex->cmd_count - 1][1], STDOUT_FILENO);
}

void	setup_stdout(t_pipex *pipex, int i)
{
	if (i == pipex->cmd_count - 1)
	{
		setup_stdout_last_cmd(pipex);
	}
	else if (dup2(pipex->pipes[i][1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
}