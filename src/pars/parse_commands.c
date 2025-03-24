/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:46:45 by acaes             #+#    #+#             */
/*   Updated: 2025/03/24 15:46:45 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

static int	allocate_command_arrays(t_pipex *pipex)
{
	pipex->cmds = (char ***)malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmds)
		return (1);
	ft_memset(pipex->cmds, 0, sizeof(char **) * pipex->cmd_count);
	pipex->cmd_paths = (char **)malloc(sizeof(char *) * pipex->cmd_count);
	if (!pipex->cmd_paths)
	{
		free(pipex->cmds);
		pipex->cmds = NULL;
		return (1);
	}
	ft_memset(pipex->cmd_paths, 0, sizeof(char *) * pipex->cmd_count);
	return (0);
}

static int	process_single_command(t_pipex *pipex, char **av, int start_idx,
		int i)
{
	if (!av[i + start_idx] || av[i + start_idx][0] == '\0')
	{
		ft_putstr_fd("Error: Empty command not allowed\n", 2);
		return (1);
	}
	pipex->cmds[i] = ft_split(av[i + start_idx], ' ');
	if (!pipex->cmds[i])
		return (1);
	if (pipex->cmds[i][0] && pipex->cmds[i][0][0] != '\0')
		pipex->cmd_paths[i] = find_cmd_path(pipex->cmds[i][0], pipex->env_path);
	else
		pipex->cmd_paths[i] = NULL;
	return (0);
}

static int	process_all_commands(t_pipex *pipex, char **av, int start_idx)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (process_single_command(pipex, av, start_idx, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	cleanup_parse_commands(t_pipex *pipex, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (pipex->cmd_paths[j])
			free(pipex->cmd_paths[j]);
		j++;
	}
	free(pipex->cmd_paths);
	pipex->cmd_paths = NULL;
	j = 0;
	while (j < i)
	{
		if (pipex->cmds[j])
			free_tab(pipex->cmds[j]);
		j++;
	}
	free(pipex->cmds);
	pipex->cmds = NULL;
}

int	parse_commands(t_pipex *pipex, char **av)
{
	int	start_idx;

	if (allocate_command_arrays(pipex) != 0)
		return (1);
	if (pipex->here_doc)
		start_idx = 3;
	else
		start_idx = 2;
	if (process_all_commands(pipex, av, start_idx) != 0)
	{
		cleanup_parse_commands(pipex, pipex->cmd_count);
		return (1);
	}
	return (0);
}
