#include "../../inc/pipex_bonus.h"

static int	setup_here_doc(t_pipex *pipex, char **av)
{
	pipex->here_doc = 1;
	pipex->limiter = av[2];
	if (handle_here_doc(pipex, pipex->limiter) != 0)
		return (1);
	pipex->outfile = open(av[pipex->cmd_count + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (pipex->outfile < 0)
	{
		perror(av[pipex->cmd_count + 3]);
		return (1);
	}
	return (0);
}

static int	setup_files(t_pipex *pipex, char **av)
{
	if (pipex->here_doc)
		return (setup_here_doc(pipex, av));
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(av[1]);
	pipex->outfile = open(av[pipex->cmd_count + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (pipex->outfile < 0)
	{
		perror(av[pipex->cmd_count + 2]);
		return (1);
	}
	return (0);
}

static int	parse_commands(t_pipex *pipex, char **av)
{
	int	i;
	int	start_idx;

	pipex->cmds = (char ***)malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmds)
		return (1);
	pipex->cmd_paths = (char **)malloc(sizeof(char *) * pipex->cmd_count);
	if (!pipex->cmd_paths)
	{
		free(pipex->cmds);
		return (1);
	}
	start_idx = pipex->here_doc ? 3 : 2;
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i] = ft_split(av[i + start_idx], ' ');
		if (!pipex->cmds[i])
			return (1);
		if (pipex->cmds[i][0] && pipex->cmds[i][0][0] != '\0')
			pipex->cmd_paths[i] = find_cmd_path(pipex->cmds[i][0], pipex->env_path);
		else
			pipex->cmd_paths[i] = NULL;
		i++;
	}
	return (0);
}

int	init_command(t_pipex *pipex, int ac, char **av)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->here_doc = 0;
	if (ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
	{
		if (ac < 6)
			return (p_error("Error: Not enough arguments for here_doc"));
		pipex->cmd_count = ac - 4;
		pipex->here_doc = 1;
	}
	else
		pipex->cmd_count = ac - 3;
	pipex->pipe_count = pipex->cmd_count - 1;
	if (setup_files(pipex, av) != 0)
		return (1);
	create_pipes(pipex);
	if (parse_commands(pipex, av) != 0)
		return (1);
	return (0);
}
