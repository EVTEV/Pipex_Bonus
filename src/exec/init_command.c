/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:44:54 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:44:54 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

static void	initialize_pipex_values(t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->outfile_error = 0;
	pipex->pipes = NULL;
	pipex->cmds = NULL;
	pipex->cmd_paths = NULL;
	pipex->pids = NULL;
	pipex->here_doc = 0;
}

static int	check_here_doc_mode(t_pipex *pipex, int ac, char **av)
{
	if (av[1] && ft_strncmp(av[1], HERE_DOC, ft_strlen(HERE_DOC)) == 0)
	{
		if (ac < 6)
			return (p_error("Error: Not enough arguments for here_doc"));
		pipex->cmd_count = ac - 4;
		pipex->here_doc = 1;
	}
	else
		pipex->cmd_count = ac - 3;
	return (0);
}

static void	cleanup_files(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
}

static int	create_and_parse(t_pipex *pipex, char **av)
{
	create_pipes(pipex);
	if (!pipex->pipes && pipex->pipe_count > 0)
	{
		cleanup_files(pipex);
		return (p_error("Error: Failed to create pipes"));
	}
	if (parse_commands(pipex, av) != 0)
	{
		cleanup_files(pipex);
		close_pipes(pipex);
		free_pipex(pipex);
		return (1);
	}
	return (0);
}

int	init_command(t_pipex *pipex, int ac, char **av)
{
	initialize_pipex_values(pipex);
	if (ac > 1 && (!av[1] || av[1][0] == '\0'))
	{
		ft_putstr_fd("Error: First argument cannot be empty\n", 2);
		return (1);
	}
	if (check_here_doc_mode(pipex, ac, av) != 0)
		return (1);
	pipex->pipe_count = pipex->cmd_count - 1;
	if (setup_files(pipex, av) != 0)
		return (1);
	if (create_and_parse(pipex, av) != 0)
		return (1);
	return (0);
}
